#ifndef ADDMODIFYVACDAYS_H
#define ADDMODIFYVACDAYS_H

#include <QDialog>

class QComboBox;
class QSpinBox;

class AddModifyVacDays : public QDialog
{
public:
    explicit AddModifyVacDays(QWidget *parent, int vdId = -1);

private:
    void setupUi();
    void fillVdInfo();

    int m_vdId;

    QComboBox *m_cbUser;
    QSpinBox *m_sbYear;
    QSpinBox *m_sbDays;

};

#endif // ADDMODIFYVACDAYS_H
