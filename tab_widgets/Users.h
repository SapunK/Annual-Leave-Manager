#ifndef USERS_H
#define USERS_H

#include "custom_widgets/CustomTabWidget.h"

namespace Users_NS {
enum EUserColumns {
    firstName,
    lastName,
    personalEmail,
    workEmail,
    dateBirth,
    dateEmployment,
    gender,
    roleName,
    id
};
}

class Users : public CustomTabWidget
{
    Q_OBJECT
public:
    explicit Users(QWidget *parent = nullptr);

private:
    void setupModelView();

private slots:
    void addClicked();
    void modifyClicked();
    void deleteClicked();

};

#endif // USERS_H
