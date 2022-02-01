#include "AddHoliday.h"

#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QDateEdit>
#include <QLineEdit>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

#include "util/HelperFunctions.h"

namespace AddHoliday_NS {
    static const char* TITLE = "Holidays";

    static const char* DESCRTIPTION = "Description";
    static const char* DATE = "Date";
    static const char* SAVE = "Save";
    static const char* CANCEL = "Cancel";

    static const char* SELECT_HOLIDAY = "SELECT id, date, description FROM holidays WHERE id = :holidayId;";
    static const char* INSERT_HOLIDAY_QUERY = "INSERT INTO holidays ( date, description) "
                                              "VALUES (:date, :description);";

}

using namespace AddHoliday_NS;

AddHoliday::AddHoliday(QWidget *parent, int holidayId) :
    QDialog(parent),
    m_holidayId(holidayId)
{
    setWindowTitle(TITLE);
    setMinimumSize(HelperFunctions::desktopWidth() * 0.25, HelperFunctions::desktopWidth() * 0.08);
    setupUi();

    if(holidayId >= 0)
        fillHolidayInfo();
}

void AddHoliday::setupUi()
{
    QFormLayout *mainLayout = new QFormLayout(this);

    QLabel *lbDescription = new QLabel(DESCRTIPTION, this);
    m_leDescription = new QLineEdit(this);

    QLabel *lbDate = new QLabel(DATE, this);
    m_deDate = new QDateEdit(this);
    m_deDate->setDisplayFormat("dd.MM.yyyy");

    m_pbSave = new QPushButton(SAVE, this);
    m_pbCancel = new QPushButton(CANCEL, this);

    mainLayout->addRow(lbDescription, m_leDescription);
    mainLayout->addRow(lbDate, m_deDate);
    mainLayout->addRow(m_pbSave);
    mainLayout->addRow(m_pbCancel);

    connect(m_pbSave, &QPushButton::clicked, this, &AddHoliday::addHoliday);
    connect(m_pbCancel, &QPushButton::clicked, this, &QDialog::reject);
};

void AddHoliday::fillHolidayInfo()
{
    QSqlQuery q;

    q.prepare(SELECT_HOLIDAY);
    q.bindValue(":holidayId", m_holidayId);
    q.exec();
    q.next();

    m_leDescription->setText(q.value(EHolidayColumns::description).toString());
    m_deDate->setDate(q.value(EHolidayColumns::date).toDate());
}

void AddHoliday::addHoliday()
{
    QSqlQuery q;

    q.prepare(INSERT_HOLIDAY_QUERY);
    q.bindValue(":date", m_deDate->date());
    q.bindValue(":description", m_leDescription->text());

    if(!q.exec()){
        qDebug()<<"Query not executed, error: " << q.lastError();
        return;
    }

    QDialog::accept();
}















