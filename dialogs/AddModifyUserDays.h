#ifndef ADDMODIFYUSERDAYS_H
#define ADDMODIFYUSERDAYS_H

#include <QDialog>
#include <QDate>

namespace AddModifyUserDays_NS {

enum EUDTableColumn{
    userId,
    year,
    days
};

enum EUserColumns{
    user,
    id
};

extern const char* USER;
extern const char* YEAR;
extern const char* DAYS;
}

class QComboBox;
class QSpinBox;
class QLineEdit;

class AddModifyUserDays : public QDialog
{
public:
    explicit AddModifyUserDays(QWidget *parent, int udId = -1, int year = QDate::currentDate().year());

private:
    void setupUi(int year);
    void fillUdInfo();
    void saveUserDays();

    int m_udId;
    int m_year;

    QComboBox *m_cbUser;
    QSpinBox *m_sbYear;
    QSpinBox *m_sbDays;

    QPushButton *m_pbSave;
    QPushButton *m_pbCancel;


};

#endif // ADDMODIFYUSERDAYS_H
