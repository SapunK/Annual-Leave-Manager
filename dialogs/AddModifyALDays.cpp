#include "AddModifyALDays.h"

#include <QComboBox>
#include <QDateEdit>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

#include "util/HelperFunctions.h"
#include "util/EALDTableColumns.h"

namespace AddModifyALDays_NS {
static const char* ALD_TITLE = "Annual Leave Days";

const char* USER = "User";
const char* DATE_FROM = "Date From";
const char* DATE_TO = "Date To";
static const char* DATE_FORMAT = "dd.MM.yyyy";

static const char* SAVE = "Save";
static const char* CANCEL = "Cancel";

static const char* USER_QUERY = "SELECT concat(first_name, ' ' ,last_name) AS name, id FROM users;";
static const char* SELECT_ALD = "SELECT id, user_id, date_from, date_to FROM annual_leave_days WHERE id = :aldId;";
static const char* UPDATE_ALD = "UPDATE annual_leave_days SET date_from = :dateFrom, date_to = :dateTo, used_days = :usedDays WHERE id = :aldId;";
static const char* INSERT_ALD = "INSERT INTO annual_leave_days (user_id, date_from, date_to, used_days) "
                                "VALUES (:userId, :dateFrom, :dateTo, :usedDays);";
static const char* SELECT_HOLIDAYS = "SELECT date FROM holidays WHERE EXTRACT(year FROM date) = :year;";
}

using namespace AddModifyALDays_NS;

AddModifyALDays::AddModifyALDays(QWidget *parent, int aldId)
    : QDialog(parent),
      m_aldId(aldId)
{
    setWindowTitle(ALD_TITLE);
    setMinimumSize(HelperFunctions::desktopWidth() * 0.15, HelperFunctions::desktopWidth() * 0.08);
    setupUi();

    if(aldId > 0 )
        fillALDInfo();
}

void AddModifyALDays::setupUi()
{
    QFormLayout *mainLayout = new QFormLayout(this);

    QLabel *lbUser = new QLabel(USER, this);
    m_cbUser = new QComboBox(this);
    m_cbUser->setDisabled(m_aldId > 0);

    QSqlQueryModel *userModel = new QSqlQueryModel(this);
    userModel->setQuery(USER_QUERY);
    m_cbUser->setModel(userModel);

    QLabel *lbDateFrom = new QLabel(DATE_FROM, this);
    m_deDateFrom = new QDateEdit(this);
    m_deDateFrom->setCalendarPopup(true);
    m_deDateFrom->setDisplayFormat(DATE_FORMAT);
    m_deDateFrom->setDate(QDate::currentDate());

    QLabel *lbDateTo = new QLabel(DATE_TO, this);
    m_deDateTo = new QDateEdit(this);
    m_deDateTo->setCalendarPopup(true);
    m_deDateTo->setDisplayFormat(DATE_FORMAT);
    m_deDateTo->setDate(QDate::currentDate());

    m_pbSave = new QPushButton(SAVE, this);
    m_pbCancel = new QPushButton(CANCEL, this);

    mainLayout->addRow(lbUser, m_cbUser);
    mainLayout->addRow(lbDateFrom, m_deDateFrom);
    mainLayout->addRow(lbDateTo, m_deDateTo);
    mainLayout->addRow(m_pbCancel);
    mainLayout->addRow(m_pbSave);
    connect(m_pbSave, &QPushButton::clicked, this, &AddModifyALDays::saveALDays);
    connect(m_pbCancel, &QPushButton::clicked, this, &QDialog::reject);
}

void AddModifyALDays::fillALDInfo()
{
    QSqlQuery q;

    q.prepare(SELECT_ALD);
    q.bindValue(":aldId", m_aldId);
    q.exec();
    q.next();

    m_deDateFrom->setDate(q.value(EALDTableColumns::dateFrom).toDate());
    m_deDateTo->setDate(q.value(EALDTableColumns::dateTo).toDate());

    for(int i = 0 ; i < m_cbUser->model()->rowCount() ; i++){
        if(m_cbUser->model()->index(i, EUserColumns::userId).data().toInt() == q.value(EALDTableColumns::user).toInt())
            m_cbUser->setCurrentIndex(i);
    }
}

void AddModifyALDays::saveALDays()
{
    QSqlQuery q;

    q.prepare(SELECT_HOLIDAYS);
    q.bindValue(":year", m_deDateFrom->date().year());
    q.exec();

    QList<QDate> holidays;

    while(q.next())
        holidays.append(q.value(0).toDate());


    int userId = m_cbUser->model()->index(m_cbUser->currentIndex(), EUserColumns::userId).data().toInt();

    QDate dateFrom = m_deDateFrom->date();
    QDate dateTo = m_deDateTo->date();

    int usedDays = 0;

    for(int i = 0 ; i <= dateFrom.daysTo(dateTo) ; i++) {
        QDate checkDay = dateFrom.addDays(i);
        if(checkDay.dayOfWeek() != Qt::Saturday &&
                checkDay.dayOfWeek() != Qt::Sunday &&
                !holidays.contains(checkDay)) {
            usedDays++;
        }
    }

    if(m_aldId > 0) {
        q.prepare(UPDATE_ALD);
        q.bindValue(":aldId", m_aldId);
    } else {
        q.prepare(INSERT_ALD);
        q.bindValue(":userId", userId);
    }

    q.bindValue(":dateFrom", dateFrom);
    q.bindValue(":dateTo", dateTo);
    q.bindValue(":usedDays", usedDays);


    if(!q.exec()) {
        qCritical()<<"Query not executed, error: " << q.lastError();
        return;
    }

    QDialog::accept();
}
