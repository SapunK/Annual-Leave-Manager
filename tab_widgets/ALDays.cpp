#include "ALDays.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDate>
#include <QPushButton>
#include <QToolBar>
#include <QSpinBox>

#include "dialogs/AddModifyALDays.h"
#include "custom_widgets/CustomTableView.h"


namespace AnnualLeaveDays_NS {
static const char* USER = "User";
static const char* DAYS = "Days";
static const char* YEAR = "Year";
static const char* NAME = "Name";


static const char* DELETE_TITLE = "Delete";
static const char* DELETE_MSG = "Are you sure you want to delete this record?";
static const char* MODEL_QUERY = "SELECT u.first_name || ' ' || u.last_name, ald.year, ald.days, ald.id "
                                 "FROM annual_leave_days ald "
                                 "INNER JOIN users u on u.id = ald.user_id "
                                 "WHERE ald.year = :year;";

static const char* DELETE_VD_QUERY = "DELETE FROM annual_leave_days WHERE id = :aldId";

}

using namespace AnnualLeaveDays_NS;

ALDays::ALDays(QWidget *parent)
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

void ALDays::setupModelView()
{
    setModelQuery();
    m_table->setModel(m_model);
    m_table->resizeColumnsToContents();
    connect(m_table->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]{
        m_pbModify->setEnabled(m_table->currentIndex().isValid());
        m_pbDelete->setEnabled(m_table->currentIndex().isValid());
    });
    m_table->hideColumn(id);


    m_model->setHeaderData(name, Qt::Horizontal, NAME);
    m_model->setHeaderData(year, Qt::Horizontal, YEAR);
    m_model->setHeaderData(days, Qt::Horizontal, DAYS);
    m_model->setHeaderData(id, Qt::Horizontal, USER);
}

void ALDays::setModelQuery()
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

void ALDays::addClicked()
{
    AddModifyVacDays *dlg = new AddModifyVacDays(this, -1, m_sbYear->value());
    connect(dlg, &QDialog::accepted, this, [this]{
        setModelQuery();
    });
    dlg->exec();
}

void ALDays::modifyClicked()
{
    AddModifyVacDays *dlg = new AddModifyVacDays(this, m_model->index(m_table->currentIndex().row(), AnnualLeaveDays_NS::id).data().toInt(), m_sbYear->value());
    connect(dlg, &QDialog::accepted, this, [this]{
        setModelQuery();
    });
    dlg->exec();
}

void ALDays::deleteClicked()
{
    if(QMessageBox::question(this, DELETE_TITLE, DELETE_MSG) == QMessageBox::Yes){
        QSqlQuery q;
        q.prepare(DELETE_VD_QUERY);
        q.bindValue(":vdId", m_model->index(m_table->currentIndex().row(), AnnualLeaveDays_NS::id).data().toInt());
        q.exec();

        setModelQuery();
    }
}
