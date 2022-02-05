#ifndef ADDMODIFYVACDAYS_H
#define ADDMODIFYVACDAYS_H

#include <QDialog>
#include <QDate>

namespace AddModifyVacDays_NS {

enum EVDTableColumn{
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

class AddModifyVacDays : public QDialog
{
public:
    explicit AddModifyVacDays(QWidget *parent, int vdId = -1, int year = QDate::currentDate().year());

private:
    void setupUi(int year);
    void fillVdInfo();
    void saveVacDays();

    int m_vdId;
    int m_year;

    QComboBox *m_cbUser;
    QSpinBox *m_sbYear;
    QSpinBox *m_sbDays;

    QPushButton *m_pbSave;
    QPushButton *m_pbCancel;


};

#endif // ADDMODIFYVACDAYS_H
