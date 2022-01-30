#ifndef ADDHOLIDAY_H
#define ADDHOLIDAY_H

#include <QDialog>

namespace AddHoliday_NS {
enum EHolidayColumn{
    date,
    description
};
}

class QLineEdit;
class QDateEdit;
class QPushButton;

class AddHoliday : public QDialog
{

public:
    explicit AddHoliday(QWidget *parent = nullptr, int holidayId = -1);

private:
    void setupUi();
    void fillHolidayInfo();
    void addHoliday();

    int m_holidayId;

    QDateEdit *m_deDate;

    QLineEdit *m_leDescription;

    QPushButton *m_pbSave;
    QPushButton *m_pbCancel;
};

#endif // ADDHOLIDAY_H
