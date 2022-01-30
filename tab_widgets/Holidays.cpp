#include "Holidays.h"

#include <QPushButton>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include "custom_widgets/CustomTableView.h"
#include "dialogs/AddHoliday.h"

namespace Holiday_NS {
    static const char* MODEL_QUERY = "SELECT id, date, description FROM holidays";
    static const char* DESCRIPTION = "Description";
    static const char* DATE = "Date";
}

using namespace Holiday_NS;

Holidays::Holidays(QWidget *parent)
    : CustomTabWidget(parent)
{
    setupModelView();
}

void Holidays::setupModelView()
{
    m_model->setQuery(MODEL_QUERY);
    m_table->setModel(m_model);
    m_table->resizeColumnsToContents();

    m_model->setHeaderData(date, Qt::Horizontal, DATE);
    m_model->setHeaderData(description, Qt::Horizontal, DESCRIPTION);

}

void Holidays::addClicked(){
    AddHoliday *dlg = new AddHoliday(this);
    connect(dlg, &QDialog::accepted, this, [this]{
        m_model->setQuery(MODEL_QUERY);
    });
    dlg->exec();
}

void Holidays::modifyClicked(){}

void Holidays::deleteClicked(){}
