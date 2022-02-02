#include "Holidays.h"

#include <QPushButton>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

#include "custom_widgets/CustomTableView.h"
#include "dialogs/AddHoliday.h"

namespace Holiday_NS {
    static const char* DESCRIPTION = "Description";
    static const char* DATE = "Date";

    static const char* MODEL_QUERY = "SELECT id, date, description FROM holidays";
    static const char* DELETE_QUERY = "DELETE FROM holidays WHERE id = :holidayId";
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
    m_table->hideColumn(id);

    connect(m_table->selectionModel(), &QItemSelectionModel::selectionChanged , this, [this]{
       m_pbModify->setDisabled(true);
       m_pbDelete->setDisabled(true);
    });

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

void Holidays::modifyClicked(){
    AddHoliday *dlg = new AddHoliday(this, m_model->index(m_table->currentIndex().row(), Holiday_NS::id).data().toInt());
    connect(dlg, &QDialog::accepted, this, [this]{
       m_model->setQuery(MODEL_QUERY);
       m_pbDelete->setEnabled(m_table->currentIndex().isValid());
       m_pbModify->setEnabled(m_table->currentIndex().isValid());
    });
}

void Holidays::deleteClicked(){
    if(QMessageBox::question(this, "DELETE TITLE", "DELETE MESSAGE") ==  QMessageBox::Yes)
    {
        QSqlQuery q;
        q.prepare(DELETE_QUERY);
        q.bindValue(":holidayId", m_model->index(m_table->currentIndex().row(), Holiday_NS::id).data().toInt());
        q.exec();

        m_model->setQuery(MODEL_QUERY);
        m_pbDelete->setEnabled(m_table->currentIndex().isValid());
        m_pbModify->setEnabled(m_table->currentIndex().isValid());
    }
}





















