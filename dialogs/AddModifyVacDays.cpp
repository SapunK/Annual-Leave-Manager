#include "AddModifyVacDays.h"

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

#include "util/HelperFunctions.h"


namespace AddModifyVacDays_NS {
const char* USER = "User";
const char* YEAR = "Year";
const char* DAYS = "Days";

static const char* SAVE = "Save";
static const char* CANCEL = "Cancel";

static const char* VACATION_TITLE = "Vacation days";

static const char* SELECT_ROWS = "SELECT * FROM vacation_days WHERE user_id = :userId AND year = :year";
static const char* SELECT_VD = "SELECT user_id, year, days FROM vacation_days WHERE id = :vdId;";
static const char* INSERT_VD_QUERY = "INSERT INTO vacation_days (user_id, year, days) "
                                     "VALUES (:user_id, :year, :days)";
static const char* USER_QUERY = "SELECT concat(first_name, ' ' ,last_name) AS name, id FROM users;";
}

using namespace AddModifyVacDays_NS;

AddModifyVacDays::AddModifyVacDays(QWidget *parent, int vdId)
    : QDialog(parent),
      m_vdId(vdId)
{
    setWindowTitle(VACATION_TITLE);
    setMinimumSize(HelperFunctions::desktopWidth() * 0.15, HelperFunctions::desktopWidth() * 0.08);
    setupUi();

    if(vdId > 0 )
        fillVdInfo();
}

void AddModifyVacDays::setupUi()
{
    QFormLayout *mainLayout = new QFormLayout(this);

    QLabel *lbUser = new QLabel(USER, this);
    m_cbUser = new QComboBox(this);

    QSqlQueryModel *userModel = new QSqlQueryModel(this);
    userModel->setQuery(USER_QUERY);
    m_cbUser->setModel(userModel);

    QLabel *lbYear = new QLabel(YEAR, this);
    m_sbYear = new QSpinBox(this);
    m_sbYear->setMinimum(2000);
    m_sbYear->setMaximum(9999);
    m_sbYear->setValue(QDate::currentDate().year());

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

//TODO mozhe da ima validacija dali vo baza vekje ima record za toj user i godina
void AddModifyVacDays::saveVacDays()
{

    QSqlQuery q;

    q.prepare(INSERT_VD_QUERY);
    q.bindValue(":days", m_sbDays->value());
    q.bindValue(":year", m_sbYear->value());
    q.bindValue(":user_id", m_cbUser->model()->index(m_cbUser->currentIndex(), EUserColumns::id).data().toInt());

    if(!q.exec()) {
        qCritical()<<"Query not executed, error: " << q.lastError();
        return;
    }

    QDialog::accept();
}


















