#include "AddEditUser.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>

#include "util/HelperFunctions.h"

namespace AddEditUser_NS {
static const char* ADD_TITLE = "Add user";
static const char* MODIFY_TITLE = "Modify user";

static const char* USERNAME = "Username";
static const char* PASSWORD = "Password";
static const char* FIRST_NAME = "First name";
static const char* LAST_NAME = "Last Name";
static const char* PERSONAL_EMAIL = "Personal email";
static const char* WORK_EMAIL = "Work email";
static const char* DATE_BIRTH = "Date birth";
static const char* DATE_EMPLOYMENT = "Date employment";
static const char* USER_ROLE = "User Role";
static const char* GENDER_ID = "Gender";
static const char* ERROR = "Error";
static const char* SAVE = "Save";
static const char* USERNAME_VALIDATION = "Username can't be empty";
static const char* FIRST_NAME_VALIDATION = "First name can't be empty";
static const char* LAST_NAME_VALIDATION = "Last name can't be empty";
static const char* PASSWORD_VALIDATION = "Password can't be empty";
static const char* WORK_EMAIL_VALIDATION = "Working email can't be empty";

static const char* DATE_FORMAT = "dd.MM.yyyy";


static const char* INSERT_USER_QUERY = "INSERT INTO users (username, password, first_name, last_name, personal_email, work_email, date_birth, "
                                       "                   date_employment, user_role_id, gender_id)"
                                       " VALUES (:username, :password, :firstName, :lastName, :personalEmail, :workEmail,"
                                       "         :dateBirth, :dateEmployment, :userRoleId, :genderId);";
static const char* USER_ROLES_QUERY = "SELECT role_name, id FROM user_roles;";
static const char* GENDER_QUERY = "SELECT name, id FROM genders";

static const char* SELECT_USER = "SELECT username, password, first_name, last_name, personal_email, work_email, "
                                 "date_birth, date_employment, user_role_id, gender_id "
                                 "FROM users "
                                 "WHERE id = :userId;";
static const char* UPDATE_USER_QUERY = "UPDATE users SET username = :username, password = :password, first_name = :firstName, last_name = :lastName, "
                                       "personal_email = :personalEmail, work_email = :workEmail, user_role_id = :userRoleId "
                                       "WHERE id = :userId;";
}

using namespace AddEditUser_NS;
using namespace UserRoles_NS;
using namespace Genders_NS;

AddEditUser::AddEditUser(QWidget *parent, int userId) :
    QDialog(parent),
    m_userId(userId)
{
    setWindowTitle(m_userId > 0 ? MODIFY_TITLE : ADD_TITLE);
    setMinimumSize(HelperFunctions::desktopWidth() * 0.25, HelperFunctions::desktopWidth() * 0.15);
    setupUi();

    if(userId >= 0)
        fillUserInfo();
}

void AddEditUser::setupUi()
{
    QFormLayout *mainLayout = new QFormLayout(this);

    QLabel *lbUsername = new QLabel(USERNAME, this);
    m_leUsername = new QLineEdit(this);

    QLabel *lbPassword = new QLabel(PASSWORD, this);
    m_lePassword = new QLineEdit(this);
    m_lePassword->setEchoMode(QLineEdit::Password);

    QLabel *lbFirstName = new QLabel(FIRST_NAME, this);
    m_leFirstName = new QLineEdit(this);

    QLabel *lbLastName = new QLabel(LAST_NAME, this);
    m_leLastName = new QLineEdit(this);

    QLabel *lbPersonalEmail = new QLabel(PERSONAL_EMAIL, this);
    m_lePersonalEmail = new QLineEdit(this);

    QLabel *lbWorkEmail = new QLabel(WORK_EMAIL, this);
    m_leWorkEmail = new QLineEdit(this);

    QLabel *lbDateBirth = new QLabel(DATE_BIRTH, this);
    m_deDateBirth = new QDateEdit(this);
    m_deDateBirth->setCalendarPopup(true);
    m_deDateBirth->setDisplayFormat(DATE_FORMAT);
    if(m_userId > 0)
        m_deDateBirth->setDisabled(true);

    QLabel *lbDateEmployment = new QLabel(DATE_EMPLOYMENT ,this);
    m_deDateEmployment = new QDateEdit(this);
    m_deDateEmployment->setCalendarPopup(true);
    m_deDateEmployment->setDisplayFormat(DATE_FORMAT);
    if(m_userId > 0)
        m_deDateEmployment->setDisabled(true);

    QLabel *lbUserRole = new QLabel(USER_ROLE, this);
    m_cbUserRole = new QComboBox(this);

    QSqlQueryModel *userRoleModel = new QSqlQueryModel(this);
    userRoleModel->setQuery(USER_ROLES_QUERY);
    m_cbUserRole->setModel(userRoleModel);

    QLabel *lbGender = new QLabel(GENDER_ID, this);
    m_cbGender = new QComboBox(this);
    if(m_userId > 0)
        m_cbGender->setDisabled(true);

    QSqlQueryModel *gendersModel =  new QSqlQueryModel(this);
    gendersModel->setQuery(GENDER_QUERY);
    m_cbGender->setModel(gendersModel);


    m_pbSave = new QPushButton(SAVE, this);

    mainLayout->addRow(lbUsername, m_leUsername);
    mainLayout->addRow(lbPassword, m_lePassword);
    mainLayout->addRow(lbFirstName, m_leFirstName);
    mainLayout->addRow(lbLastName, m_leLastName);
    mainLayout->addRow(lbPersonalEmail, m_lePersonalEmail);
    mainLayout->addRow(lbWorkEmail, m_leWorkEmail);
    mainLayout->addRow(lbDateBirth, m_deDateBirth);
    mainLayout->addRow(lbDateEmployment, m_deDateEmployment);
    mainLayout->addRow(lbUserRole, m_cbUserRole);
    mainLayout->addRow(lbGender, m_cbGender);
    mainLayout->addRow(m_pbSave);

    connect(m_pbSave, &QPushButton::clicked, this, &AddEditUser::addUser);
}

void AddEditUser::fillUserInfo()
{
   // setWindowTitle(MODIFY_TITLE);

    QSqlQuery q;
    q.prepare(SELECT_USER);
    q.bindValue(":userId", m_userId);
    q.exec();
    q.next();

    m_leUsername->setText(q.value(EUserTableColumns::userName).toString());
    m_lePassword->setText(q.value(EUserTableColumns::password).toString());
    m_leFirstName->setText(q.value(EUserTableColumns::firstName).toString());
    m_leLastName->setText(q.value(EUserTableColumns::lastName).toString());
    m_lePersonalEmail->setText(q.value(EUserTableColumns::personalEmail).toString());
    m_leWorkEmail->setText(q.value(EUserTableColumns::workEmail).toString());
    m_deDateBirth->setDate(q.value(EUserTableColumns::dateBirth).toDate());

    for(int i = 0 ; i < m_cbUserRole->model()->rowCount() ; i++) {
        if(m_cbUserRole->model()->index(i, UserRoles_NS::id).data().toInt() == q.value(EUserTableColumns::userRoleId).toInt())
            m_cbUserRole->setCurrentIndex(m_cbUserRole->findText(m_cbUserRole->model()->index(i, UserRoles_NS::roleName).data().toString()));
    }
    for(int i = 0 ; i <m_cbGender->model()->rowCount() ; i++){
        if(m_cbGender->model()->index(i, Genders_NS::id).data().toInt() == q.value(EUserTableColumns::genderId).toInt())
            m_cbGender->setCurrentIndex(m_cbGender->findText(m_cbGender->model()->index(i, Genders_NS::name).data().toString()));
    }



}

void AddEditUser::addUser()
{
    if(m_leUsername->text().isEmpty()) {
        QMessageBox::critical(this, ERROR, USERNAME_VALIDATION);
        return;
    }

    if(m_leFirstName->text().isEmpty()){
        QMessageBox::critical(this, ERROR, FIRST_NAME_VALIDATION);
        return;
    }

    if(m_leLastName->text().isEmpty()){
        QMessageBox::critical(this, ERROR, LAST_NAME_VALIDATION);
        return;
    }

    if(m_lePassword->text().isEmpty()){
        QMessageBox::critical(this, ERROR, PASSWORD_VALIDATION);
        return;
    }

    if(m_leWorkEmail->text().isEmpty()){
        QMessageBox::critical(this, ERROR, WORK_EMAIL_VALIDATION);
        return;
    }


    QSqlQuery q;

    if(m_userId > 0) {
        q.prepare(UPDATE_USER_QUERY);
        q.bindValue(":userId", m_userId);
    }
    else {
        q.prepare(INSERT_USER_QUERY);
        q.bindValue(":dateBirth", m_deDateBirth->date());
        q.bindValue(":dateEmployment", m_deDateEmployment->date());
        q.bindValue(":genderId", m_cbGender->model()->index(m_cbGender->currentIndex(), Genders_NS::id).data().toInt());
    }

    q.bindValue(":username", m_leUsername->text());
    q.bindValue(":password", m_lePassword->text());
    q.bindValue(":firstName", m_leFirstName->text());
    q.bindValue(":lastName", m_leLastName->text());
    q.bindValue(":personalEmail", m_lePersonalEmail->text());
    q.bindValue(":workEmail", m_leWorkEmail->text());
    q.bindValue(":userRoleId", m_cbUserRole->model()->index(m_cbUserRole->currentIndex(), UserRoles_NS::id).data().toInt());


    if(!q.exec()) {
        qCritical()<<"Add user query error: "<<q.lastError()<<" last query: "<<q.lastQuery();
        //QMessageBox
    } else {
        QDialog::accept();
    }
}
