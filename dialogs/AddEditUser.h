#ifndef ADDEDITUSER_H
#define ADDEDITUSER_H

#include <QDialog>

namespace UserRoles_NS {
enum EUserColumns {
    roleName,
    id
};
}

namespace Genders_NS {
enum EGenderColumns {
    name,
    id
};
}

namespace AddEditUser_NS {
enum EUserTableColumns{
    userName,
    password,
    firstName,
    lastName,
    personalEmail,
    workEmail,
    dateBirth,
    dateEmployment,
    userRoleId,
    genderId
};
}

class QLineEdit;
class QDateEdit;
class QComboBox;

class AddEditUser : public QDialog
{
public:
    explicit AddEditUser(QWidget *parent, int userId = -1);

private:
    void setupUi();
    void fillUserInfo();

    int m_userId;

    QLineEdit *m_leUsername;
    QLineEdit *m_lePassword;
    QLineEdit *m_leFirstName;
    QLineEdit *m_leLastName;
    QLineEdit *m_lePersonalEmail;
    QLineEdit *m_leWorkEmail;

    QDateEdit *m_deDateBirth;
    QDateEdit *m_deDateEmployment;

    QComboBox *m_cbUserRole;
    QComboBox *m_cbGender;

    QPushButton *m_pbSave;

private slots:

    void addUser();
};

#endif // ADDEDITUSER_H
