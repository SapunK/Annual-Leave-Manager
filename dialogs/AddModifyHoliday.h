#ifndef ADDMODIFYHOLIDAY_H
#define ADDMODIFYHOLIDAY_H

#include <QDialog>
#include <QDate>

namespace AddModifyHoliday_NS {
enum EHolidayColumns{
    date,
    description
};
}

class QLineEdit;
class QDateEdit;
class QPushButton;

class AddModifyHoliday : public QDialog
{

public:
    explicit AddModifyHoliday(QWidget *parent = nullptr, int holidayId = -1,
                              int year = QDate::currentDate().year());

private:
    void setupUi(int year);
    void fillHolidayInfo();
    void saveHoliday();

    int m_holidayId;

    QDateEdit *m_deDate;

    QLineEdit *m_leDescription;

    QPushButton *m_pbSave;
    QPushButton *m_pbCancel;
};

#endif // ADDMODIFYHOLIDAY_H
