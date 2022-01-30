#include "VacationDays.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDate>
#include <QPushButton>

#include "dialogs/AddModifyVacDays.h"
#include "custom_widgets/CustomTableView.h"


namespace VacationDays_NS {
static const char* DELETE_TITLE = "Delete";
static const char* DELETE_MSG = "Are you sure you want to delete";
static const char* MODEL_QUERY = "SELECT u.first_name || ' ' || u.last_name, vd.year, vd.days "
                                 "FROM vacation_days vd "
                                 "INNER JOIN users u on u.id = vd.user_id "
                                 "WHERE vd.year = :year;";

static const char* DELETE_VD_QUERY = "DELETE FROM vacation_days WHERE id = :vdId";

}

using namespace AddModifyVacDays_NS;
using namespace VacationDays_NS;

VacationDays::VacationDays(QWidget *parent)
    : CustomTabWidget(parent)
{
    setupModelView();
}

void VacationDays::setupModelView()
{
    QSqlQuery q;
    q.prepare(MODEL_QUERY);
    q.bindValue(":year", QDate::currentDate().year());
    q.exec();

    m_model->setQuery(std::move(q));
    m_table->setModel(m_model);
    m_table->resizeColumnsToContents();
    connect(m_table->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]{
        m_pbModify->setEnabled(true);
        m_pbDelete->setEnabled(true);
    });

    m_model->setHeaderData(userId, Qt::Horizontal, USER);
    m_model->setHeaderData(year, Qt::Horizontal, YEAR);
    m_model->setHeaderData(days, Qt::Horizontal, DAYS);
}

void VacationDays::addClicked()
{
    AddModifyVacDays *dlg = new AddModifyVacDays(this);
    connect(dlg, &QDialog::accepted, this, [this]{
        m_model->setQuery(MODEL_QUERY);
    });
    dlg->exec();
}

//FIXME vacation days gi barame po vacation day id, a ne po user id
void VacationDays::modifyClicked()
{
    AddModifyVacDays *dlg = new AddModifyVacDays(this, m_model->index(m_table->currentIndex().row(), EVDTableColumn::userId).data().toInt());
    connect(dlg, &QDialog::accepted, this, [this]{
        m_model->setQuery(MODEL_QUERY);
    });
    dlg->exec();
}

//FIXME brisheme po va
void VacationDays::deleteClicked()
{
    if(QMessageBox::question(this, DELETE_TITLE, DELETE_MSG) == QMessageBox::Yes){
        QSqlQuery q;
        q.prepare(DELETE_VD_QUERY);
        q.bindValue(":vdId", m_model->index(m_table->currentIndex().row(), EVDTableColumn::userId).data().toInt());
        q.exec();

        m_model->setQuery(MODEL_QUERY);
    }
}
