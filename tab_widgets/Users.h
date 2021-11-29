#ifndef USERS_H
#define USERS_H

#include <QWidget>

class QPushButton;
class QSqlQueryModel;
class CustomTableView;

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

class Users : public QWidget
{
    Q_OBJECT
public:
    explicit Users(QWidget *parent = nullptr);

private:
    void setupUi();

    QPushButton *m_pbAdd;
    QPushButton *m_pbModify;
    QPushButton *m_pbDelete;

    QSqlQueryModel *m_model;
    CustomTableView *m_table;

signals:

};

#endif // USERS_H
