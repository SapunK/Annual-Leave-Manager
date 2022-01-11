#include "AddModifyVacDays.h"

#include <QComboBox>
#include <QLabel>
#include <QSqlQuery>
#include <QFormLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QSqlQueryModel>
#include <QDate>
#include <QPushButton>

#include "util/HelperFunctions.h"


namespace AddModifyVacDays_NS {
const char* USER = "User";
const char* YEAR = "Year";
const char* DAYS = "Days";

static const char* SAVE = "Save";
static const char* CANCEL = "Cancel";

static const char* VACATION_TITLE = "Vacation days";

static const char* SELECT_VD = "SELECT user_id, year, days FROM vacation_days WHERE id = :vdId";
static const char* INSERT_VD_QUERY = "INSERT INTO vacation_days (user_id, year, days)"
                                       " VALUES (:user_id, :year, :days)";
static const char* USER_QUERY = "SELECT concat(first_name, ' ' ,last_name), id AS name FROM users";
}

using namespace AddModifyVacDays_NS;
using namespace AddEditVacDays;

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
    m_sbYear->setValue(QDate::currentDate().year());

    QLabel *lbDays = new QLabel(DAYS, this);
    m_sbDays = new QSpinBox(this);
    m_sbDays->setValue(0);

    m_pbSave = new QPushButton(SAVE, this);
    m_pbCancel = new QPushButton(CANCEL, this);

    mainLayout->addRow(lbUser, m_cbUser);
    mainLayout->addRow(lbYear, m_sbYear);
    mainLayout->addRow(lbDays, m_sbDays);
    mainLayout->addRow(m_pbCancel);
    mainLayout->addRow(m_pbSave);
    //connect(m_pbSave, &QPushButton::clicked, this, AddModifyVacDays::Accepted);
    connect(m_pbCancel, &QPushButton::clicked, this, &QDialog::reject);

}

//vo ovaa metoda gi polnime polinjata so vrednosti od baza (ova se povikuva na modify)
//ne treba bindValue, kje vidish vo addModifyUser kako e (tuka treba da vadish data od query i da gi napolnish polinjata so taa data)
void AddModifyVacDays::fillVdInfo()
{
    QSqlQuery q;

    q.prepare(SELECT_VD);
    q.bindValue(":vdId", m_vdId);
    q.exec();
    q.next();

    m_sbDays->setValue(q.value(EVDTableColumn::days).toInt());
    m_sbYear->setValue(q.value(EVDTableColumn::year).toInt());

    for(int i = 0; i < m_cbUser->model()->rowCount(); i++){

    }

}

//TODO da se dodade meoda saveVacDays() za insert vo baza (mozhe da ima validacija dali vo baza vekje ima record za toj user i godina)
void AddModifyVacDays::saveVacDays()
{
    QSqlQuery q;

    q.prepare(INSERT_VD_QUERY);
}


















