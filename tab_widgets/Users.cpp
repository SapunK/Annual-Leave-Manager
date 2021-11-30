#include "Users.h"

#include <QSqlQuery>
#include <QSqlQueryModel>

#include "custom_widgets/CustomTableView.h"
#include "dialogs/AddModifyUser.h"

namespace Users_NS {
static const char* FIRST_NAME = "First name";
static const char* LAST_NAME = "Last name";
static const char* PERSONAL_EMAIL ="Personal email";
static const char* WORK_EMAIL = "Work email";
static const char* DATE_BIRTH = "Date birth";
static const char* DATE_EMPLOYMENT = "Date employment";
static const char* GENDER = "Gender";
static const char* ROLE_NAME = "Role Name";

static const char* MODEL_QUERY = "SELECT u.first_name, u.last_name, u.personal_email, u.work_email, u.date_birth, "
                                 "u.date_employment, g.name, ur.role_name, u.id "
                                 "FROM users u "
                                 "INNER JOIN genders g on u.gender_id = g.id "
                                 "INNER JOIN user_roles ur on u.user_role_id = ur.id;";
static const char* DELETE_USER_QUERY = "DELETE FROM users WHERE id = :userId";

}

using namespace Users_NS;

Users::Users(QWidget *parent)
    : CustomTabWidget(parent)
{
    setupModelView();
}

void Users::setupModelView()
{
    m_model->setQuery(MODEL_QUERY);

    m_model->setHeaderData(firstName, Qt::Horizontal, FIRST_NAME);
    m_model->setHeaderData(lastName, Qt::Horizontal, LAST_NAME);
    m_model->setHeaderData(personalEmail, Qt::Horizontal, PERSONAL_EMAIL);
    m_model->setHeaderData(workEmail, Qt::Horizontal, WORK_EMAIL);
    m_model->setHeaderData(dateBirth, Qt::Horizontal, DATE_BIRTH);
    m_model->setHeaderData(dateEmployment, Qt::Horizontal, DATE_EMPLOYMENT);
    m_model->setHeaderData(gender, Qt::Horizontal, GENDER);
    m_model->setHeaderData(roleName, Qt::Horizontal, ROLE_NAME);
}

void Users::addClicked()
{
    AddModifyUser *dlg = new AddModifyUser(this);
    connect(dlg, &QDialog::accepted, this, [this] {
        m_model->setQuery(MODEL_QUERY);
    });
    dlg->exec();
}

void Users::modifyClicked()
{
    AddModifyUser *dlg = new AddModifyUser(this, m_model->index(m_table->currentIndex().row(), Users_NS::id).data().toInt());
    connect(dlg, &QDialog::accepted, this, [this] {
        m_model->setQuery(MODEL_QUERY);
    });

    dlg->exec();
}

void Users::deleteClicked()
{
    QSqlQuery q;
    q.prepare(DELETE_USER_QUERY);
    q.bindValue(":userId", m_model->index(m_table->currentIndex().row(), Users_NS::id).data().toInt());
    q.exec();

    m_model->setQuery(MODEL_QUERY);
}


