#ifndef ADDEDITUSER_H
#define ADDEDITUSER_H

#include <QDialog>

class QLineEdit;

class AddEditUser : public QDialog
{
public:
    explicit AddEditUser(QWidget *parent);

private:
    void setupUi();

    bool addUser();

    QLineEdit *m_leUsername;
    QLineEdit *m_lePassword;
};

#endif // ADDEDITUSER_H
