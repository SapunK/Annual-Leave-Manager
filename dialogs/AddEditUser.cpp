#include "AddEditUser.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QSqlQuery>

#include "util/HelperFunctions.h"

namespace AddEditUser_NS {
static const char* USERNAME = "Username";
static const char* PASSWORD = "Password";

static const char* INSERT_USER_QUERY = "INSERT INTO users (username, password) VALUES (:username, :password);";

}

using namespace AddEditUser_NS;

AddEditUser::AddEditUser(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Add user");
    setMinimumSize(HelperFunctions::desktopWidth() * 0.4, HelperFunctions::desktopWidth() * 0.4);
    setupUi();
}

void AddEditUser::setupUi()
{
    QFormLayout *mainLayout = new QFormLayout(this);

    QLabel *lbUsername = new QLabel(USERNAME, this);
    m_leUsername = new QLineEdit(this);

    QLabel *lbPassword = new QLabel(PASSWORD, this);
    m_lePassword = new QLineEdit(this);

    mainLayout->addRow(lbUsername, m_leUsername);
    mainLayout->addRow(lbPassword, m_lePassword);
}

bool AddEditUser::addUser()
{
    QSqlQuery q;

    q.prepare(INSERT_USER_QUERY);
    q.bindValue(":username", m_leUsername->text());
    q.bindValue(":password", m_lePassword->text());

    if(!q.exec())
        return false;

    return true;
}
