#include "VacationDays.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>

#include "dialogs/AddModifyVacDays.h"
#include "custom_widgets/CustomTableView.h"


namespace VacationDays_NS {
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
    m_model->setQuery(MODEL_QUERY);
    m_table->setModel(m_model);
    //m_table.

    m_model->setHeaderData(user, Qt::Horizontal, USER);
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

//da se implementiraat metoive modify i delete
void VacationDays::modifyClicked()
{
    AddModifyVacDays *dlg = new AddModifyVacDays(this, m_model->index(m_table->currentIndex().row(), VacationDays_NS::user).data().toInt());
    connect(dlg, &QDialog::accepted, this, [this]{
        m_model->setQuery(MODEL_QUERY);
    });
    dlg->exec();
}

void VacationDays::deleteClicked()
{
    if(QMessageBox::question(this, "TITLE", "BLABLA") == QMessageBox::Yes){
    QSqlQuery q;
    q.prepare(DELETE_VD_QUERY);
    q.bindValue(":vdId", m_model->index(m_table->currentIndex().row(), VacationDays_NS::user).data().toInt());
    q.exec();

    m_model->setQuery(MODEL_QUERY);
    }
}
