#include "AddModifyUserDays.h"

#include <QComboBox>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QFormLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QSqlQueryModel>
#include <QDate>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

#include "util/HelperFunctions.h"


namespace AddModifyUserDays_NS {
const char* USER = "User";
const char* YEAR = "Year";
const char* DAYS = "Days";

static const char* SAVE = "Save";
static const char* CANCEL = "Cancel";

static const char* AL_TITLE = "Annual Leave Days";
static const char* ERROR = "Error";
static const char* ERROR_STRING = "There is already a record for user %1 for year %2";
static const char* SELECT_ROWS = "SELECT * FROM user_days WHERE user_id = :userId AND year = :year";
static const char* SELECT_UD = "SELECT user_id, year, days FROM user_days WHERE id = :udId;";
static const char* INSERT_UD_QUERY = "INSERT INTO user_days (user_id, year, days) "
                                     "VALUES (:user_id, :year, :days)";
static const char* USER_QUERY = "SELECT concat(first_name, ' ' ,last_name) AS name, id FROM users;";
static const char* UPDATE_UD = "UPDATE user_days SET year = :year, days = :days WHERE id = :udId;";

}

using namespace AddModifyUserDays_NS;

AddModifyUserDays::AddModifyUserDays(QWidget *parent, int udId, int year)
    : QDialog(parent),
      m_udId(udId),
      m_year(year)
{
    setWindowTitle(AL_TITLE);
    setMinimumSize(HelperFunctions::desktopWidth() * 0.15, HelperFunctions::desktopWidth() * 0.08);
    setupUi(year);

    if(udId > 0 )
        fillUdInfo();
}

void AddModifyUserDays::setupUi(int year)
{
    QFormLayout *mainLayout = new QFormLayout(this);

    QLabel *lbUser = new QLabel(USER, this);
    m_cbUser = new QComboBox(this);
    m_cbUser->setDisabled(m_udId > 0);

    QSqlQueryModel *userModel = new QSqlQueryModel(this);
    userModel->setQuery(USER_QUERY);
    m_cbUser->setModel(userModel);

    QLabel *lbYear = new QLabel(YEAR, this);
    m_sbYear = new QSpinBox(this);
    m_sbYear->setMinimum(2000);
    m_sbYear->setMaximum(9999);
    m_sbYear->setValue(year);

    QLabel *lbDays = new QLabel(DAYS, this);
    m_sbDays = new QSpinBox(this);
    m_sbDays->setMinimum(0);
    m_sbDays->setMaximum(365);
    m_sbDays->setValue(0);

    m_pbSave = new QPushButton(SAVE, this);
    m_pbCancel = new QPushButton(CANCEL, this);

    mainLayout->addRow(lbUser, m_cbUser);
    mainLayout->addRow(lbYear, m_sbYear);
    mainLayout->addRow(lbDays, m_sbDays);
    mainLayout->addRow(m_pbCancel);
    mainLayout->addRow(m_pbSave);
    connect(m_pbSave, &QPushButton::clicked, this, &AddModifyUserDays::saveUserDays);
    connect(m_pbCancel, &QPushButton::clicked, this, &QDialog::reject);

}

void AddModifyUserDays::fillUdInfo()
{
    QSqlQuery q;

    q.prepare(SELECT_UD);
    q.bindValue(":udId", m_udId);
    q.exec();
    q.next();

    qDebug()<<"last query: " << q.lastQuery()<<" last error: " <<q.lastError()<<" days val: "<<q.value(EUDTableColumn::days).toInt();

    m_sbDays->setValue(q.value(EUDTableColumn::days).toInt());
    m_sbYear->setValue(q.value(EUDTableColumn::year).toInt());

    for(int i = 0 ; i < m_cbUser->model()->rowCount() ; i++){
        if(m_cbUser->model()->index(i, EUserColumns::id).data().toInt() == q.value(EUDTableColumn::userId).toInt())
            m_cbUser->setCurrentIndex(m_cbUser->findText(m_cbUser->model()->index(i, EUserColumns::user).data().toString()));
    }

}

void AddModifyUserDays::saveUserDays()
{
    QSqlQuery q;

    q.prepare(SELECT_ROWS);
    q.bindValue(":year", m_sbYear->value());
    q.bindValue(":userId", m_cbUser->model()->index(m_cbUser->currentIndex(), EUserColumns::id).data().toInt());

    if(q.exec() && q.numRowsAffected() > 0 &&
            ((m_udId > 0 && m_sbYear->value() != m_year) || m_udId == -1)) {

        QMessageBox::critical(this, ERROR, QString(ERROR_STRING)
                                   .arg(m_cbUser->model()->index(m_cbUser->currentIndex(),
                                   EUserColumns::user).data().toString(),
                                   QString::number(m_sbYear->value())));
        return;
    }

    if(m_udId > 0) {
        q.prepare(UPDATE_UD);
        q.bindValue(":udId", m_udId);
    } else {
        q.prepare(INSERT_UD_QUERY);
        q.bindValue(":user_id", m_cbUser->model()->index(m_cbUser->currentIndex(), EUserColumns::id).data().toInt());
    }

    q.bindValue(":days", m_sbDays->value());
    q.bindValue(":year", m_sbYear->value());


    if(!q.exec()) {
        qCritical()<<"Query not executed, error: " << q.lastError();
        return;
    }

    QDialog::accept();
}


















