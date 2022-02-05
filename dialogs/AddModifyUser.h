#ifndef ADDMODIFYUSER_H
#define ADDMODIFYUSER_H

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

class AddModifyUser : public QDialog
{
public:
    explicit AddModifyUser(QWidget *parent, int userId = -1);

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
    QPushButton *m_pbCancel;

private slots:

    void saveUser();
};

#endif // ADDMODIFYUSER_H
