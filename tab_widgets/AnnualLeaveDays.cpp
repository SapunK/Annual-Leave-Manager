#include "AnnualLeaveDays.h"

#include <QPushButton>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSpinBox>
#include <QToolBar>
#include <QDate>

#include "custom_widgets/CustomTableView.h"
#include "dialogs/AddModifyALDays.h"

namespace ALDays_NS {
static const char* MODEL_QUERY = "SELECT ald.id, u.first_name || ' ' || u.last_name, "
                                 "ald.date_from, ald.date_to, ald.used_days "
                                 "FROM annual_leave_days ald "
                                 "INNER JOIN users u on u.id = ald.user_id "
                                 "WHERE EXTRACT(YEAR FROM date_from) = :year "
                                 "OR EXTRACT(YEAR FROM date_to) = :year;";
static const char* DELETE_TITLE = "Delete";
static const char* DELETE_MSG = "Are you sure you want to delete this record?";
static const char* DELETE_ALD_QUERY = "DELETE FROM annual_leave_days WHERE id = :aldId";
static const char* USED_DAYS = "Used days";
}

using namespace ALDays_NS;
using namespace AddModifyALDays_NS;

AnnualLeaveDays::AnnualLeaveDays(QWidget *parent)
    : CustomTabWidget(parent)
{
    m_sbYear = new QSpinBox(this);
    m_sbYear->setMaximum(QDate::currentDate().year() + 100);
    m_sbYear->setValue(QDate::currentDate().year());

    connect(m_sbYear, QOverload<int>::of(&QSpinBox::valueChanged), this, [this]{
        setModelQuery();
    });

    m_tb->addWidget(m_sbYear);

    setupModelView();
}

void AnnualLeaveDays::setupModelView()
{
    setModelQuery();
    m_table->setModel(m_model);
    m_table->resizeColumnsToContents();
    m_table->hideColumn(id);

    connect(m_table->selectionModel(), &QItemSelectionModel::selectionChanged , this, [this]{
        m_pbModify->setEnabled(m_table->currentIndex().isValid());
        m_pbDelete->setEnabled(m_table->currentIndex().isValid());
    });

    m_model->setHeaderData(user, Qt::Horizontal, USER);
    m_model->setHeaderData(dateFrom, Qt::Horizontal, DATE_FROM);
    m_model->setHeaderData(dateTo, Qt::Horizontal, DATE_TO);
    m_model->setHeaderData(usedDays, Qt::Horizontal, USED_DAYS);
}

void AnnualLeaveDays::setModelQuery()
{
    QSqlQuery q;
    q.prepare(MODEL_QUERY);
    q.bindValue(":year", m_sbYear->value());
    q.exec();

    m_model->setQuery(std::move(q));
    m_table->resizeColumnsToContents();
    m_pbModify->setEnabled(m_table->currentIndex().isValid());
    m_pbDelete->setEnabled(m_table->currentIndex().isValid());
}

void AnnualLeaveDays::addClicked()
{
    AddModifyALDays *dlg = new AddModifyALDays(this, -1);
    connect(dlg, &QDialog::accepted, this, [this]{
        setModelQuery();
    });
    dlg->exec();
}

void AnnualLeaveDays::modifyClicked()
{
    AddModifyALDays *dlg = new AddModifyALDays(this, m_model->index(m_table->currentIndex().row(), id).data().toInt());
    connect(dlg, &QDialog::accepted, this, [this]{
        setModelQuery();
    });
    dlg->exec();
}

void AnnualLeaveDays::deleteClicked()
{
    if(QMessageBox::question(this, DELETE_TITLE, DELETE_MSG) == QMessageBox::Yes){
        QSqlQuery q;
        q.prepare(DELETE_ALD_QUERY);
        q.bindValue(":aldId", m_model->index(m_table->currentIndex().row(), id).data().toInt());
        q.exec();

        setModelQuery();
    }
}
