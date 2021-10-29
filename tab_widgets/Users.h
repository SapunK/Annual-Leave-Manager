#ifndef USERS_H
#define USERS_H

#include <QWidget>

class QPushButton;
class QSqlQueryModel;
class CustomTableView;

class Users : public QWidget
{
    Q_OBJECT
public:
    explicit Users(QWidget *parent = nullptr);

private:
    void setupUi();

    QPushButton *m_pbAdd;
    QSqlQueryModel *m_model;
    CustomTableView *m_table;

signals:

};

#endif // USERS_H
