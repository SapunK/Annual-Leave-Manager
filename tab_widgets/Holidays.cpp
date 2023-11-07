#include "Holidays.h"

#include <QPushButton>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSpinBox>
#include <QToolBar>
#include <QDate>

#include "custom_widgets/CustomTableView.h"
#include "dialogs/AddModifyHoliday.h"
#include "models/HolidaySqlQModel.h"

namespace Holiday_NS {
    static const char* DESCRIPTION = "Description";
    static const char* DATE = "Date";

    static const char* MODEL_QUERY = "SELECT id, date, description FROM holidays WHERE EXTRACT(YEAR FROM date) = :year;";
    static const char* DELETE_QUERY = "DELETE FROM holidays WHERE id = :holidayId";

    static const char* DELETE_TITLE = "Delete";
    static const char* DELETE_MESSAGE = "Are you sure you want to delete this holiday?";
}

using namespace Holiday_NS;

Holidays::Holidays(QWidget *parent)
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

void Holidays::setupModelView()
{
    m_model = new HolidaySqlQModel(this);
    setModelQuery();
    m_table->setModel(m_model);
    m_table->resizeColumnsToContents();
    m_table->hideColumn(id);

    connect(m_table->selectionModel(), &QItemSelectionModel::selectionChanged , this, [this]{
        m_pbModify->setEnabled(m_table->currentIndex().isValid());
        m_pbDelete->setEnabled(m_table->currentIndex().isValid());
    });

    m_model->setHeaderData(date, Qt::Horizontal, DATE);
    m_model->setHeaderData(description, Qt::Horizontal, DESCRIPTION);

}

void Holidays::setModelQuery()
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

void Holidays::addClicked(){
    AddModifyHoliday *dlg = new AddModifyHoliday(this, -1, m_sbYear->value());
    connect(dlg, &QDialog::accepted, this, [this]{
        setModelQuery();
    });
    dlg->exec();
}

void Holidays::modifyClicked(){
    AddModifyHoliday *dlg = new AddModifyHoliday(this, m_model->index(m_table->currentIndex().row(),
                                                                      Holiday_NS::id).data().toInt(),
                                                                      m_sbYear->value());
    connect(dlg, &QDialog::accepted, this, [this]{
       setModelQuery();
    });

    dlg->exec();
}

void Holidays::deleteClicked(){
    if(QMessageBox::question(this, DELETE_TITLE, DELETE_MESSAGE) ==  QMessageBox::Yes)
    {
        QSqlQuery q;
        q.prepare(DELETE_QUERY);
        q.bindValue(":holidayId", m_model->index(m_table->currentIndex().row(), Holiday_NS::id).data().toInt());
        q.exec();

        setModelQuery();
    }
}





















