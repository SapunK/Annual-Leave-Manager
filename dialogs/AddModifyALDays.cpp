#include "AddModifyALDays.h"

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


namespace AddModifyVacDays_NS {
const char* USER = "User";
const char* YEAR = "Year";
const char* DAYS = "Days";

static const char* SAVE = "Save";
static const char* CANCEL = "Cancel";

static const char* VACATION_TITLE = "Vacation days";
static const char* ERROR = "Error";
static const char* ERROR_STRING = "There is already a record for user %1 for year %2";
static const char* SELECT_ROWS = "SELECT * FROM vacation_days WHERE user_id = :userId AND year = :year";
static const char* SELECT_VD = "SELECT user_id, year, days FROM vacation_days WHERE id = :vdId;";
static const char* INSERT_VD_QUERY = "INSERT INTO vacation_days (user_id, year, days) "
                                     "VALUES (:user_id, :year, :days)";
static const char* USER_QUERY = "SELECT concat(first_name, ' ' ,last_name) AS name, id FROM users;";
static const char* UPDATE_VD = "UPDATE vacation_days SET year = :year, days = :days WHERE id = :vdId;";

}

using namespace AddModifyVacDays_NS;

AddModifyVacDays::AddModifyVacDays(QWidget *parent, int vdId, int year)
    : QDialog(parent),
      m_vdId(vdId),
      m_year(year)
{
    setWindowTitle(VACATION_TITLE);
    setMinimumSize(HelperFunctions::desktopWidth() * 0.15, HelperFunctions::desktopWidth() * 0.08);
    setupUi(year);

    if(vdId > 0 )
        fillVdInfo();
}

void AddModifyVacDays::setupUi(int year)
{
    QFormLayout *mainLayout = new QFormLayout(this);

    QLabel *lbUser = new QLabel(USER, this);
    m_cbUser = new QComboBox(this);
    m_cbUser->setDisabled(m_vdId > 0);

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
    connect(m_pbSave, &QPushButton::clicked, this, &AddModifyVacDays::saveVacDays);
    connect(m_pbCancel, &QPushButton::clicked, this, &QDialog::reject);

}

void AddModifyVacDays::fillVdInfo()
{
    QSqlQuery q;

    q.prepare(SELECT_VD);
    q.bindValue(":vdId", m_vdId);
    q.exec();
    q.next();

    m_sbDays->setValue(q.value(EVDTableColumn::days).toInt());
    m_sbYear->setValue(q.value(EVDTableColumn::year).toInt());

    for(int i = 0 ; i < m_cbUser->model()->rowCount() ; i++){
        if(m_cbUser->model()->index(i, EUserColumns::id).data().toInt() == q.value(EVDTableColumn::userId).toInt())
            m_cbUser->setCurrentIndex(m_cbUser->findText(m_cbUser->model()->index(i, EUserColumns::user).data().toString()));
    }

}

void AddModifyVacDays::saveVacDays()
{
    QSqlQuery q;

    q.prepare(SELECT_ROWS);
    q.bindValue(":year", m_sbYear->value());
    q.bindValue(":userId", m_cbUser->model()->index(m_cbUser->currentIndex(), EUserColumns::id).data().toInt());

    if(q.exec() && q.numRowsAffected() > 0 &&
            ((m_vdId > 0 && m_sbYear->value() != m_year) || m_vdId == -1)) {

        QMessageBox::critical(this, ERROR, QString(ERROR_STRING)
                                   .arg(m_cbUser->model()->index(m_cbUser->currentIndex(),
                                   EUserColumns::user).data().toString(),
                                   QString::number(m_sbYear->value())));
        return;
    }

    if(m_vdId > 0) {
        q.prepare(UPDATE_VD);
        q.bindValue(":vdId", m_vdId);
    } else {
        q.prepare(INSERT_VD_QUERY);
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


















