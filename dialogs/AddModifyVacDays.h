#ifndef ADDMODIFYVACDAYS_H
#define ADDMODIFYVACDAYS_H

#include <QDialog>

namespace AddEditVacDays{
enum EVDTableColumn{
    user,
    year,
    days
};
}
namespace AddModifyVacDays_NS {
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
    explicit AddModifyVacDays(QWidget *parent, int vdId = -1);

private:
    void setupUi();
    void fillVdInfo();
    void saveVacDays();

    int m_vdId;

    QComboBox *m_cbUser;
    QSpinBox *m_sbYear;
    QSpinBox *m_sbDays;

    QPushButton *m_pbSave;
    QPushButton *m_pbCancel;


};

#endif // ADDMODIFYVACDAYS_H
