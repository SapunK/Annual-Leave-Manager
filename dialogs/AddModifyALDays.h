#ifndef ADDMODIFYALDAYS_H
#define ADDMODIFYALDAYS_H

#include <QDialog>

namespace AddModifyALDays_NS {

enum EUserColumns{
    userNameLastname,
    userId
};

extern const char* USER;
extern const char* DATE_FROM;
extern const char* DATE_TO;
}

class QComboBox;
class QDateEdit;

class AddModifyALDays : public QDialog
{
public:
    explicit AddModifyALDays(QWidget *parent, int aldId = -1);
private:
    void setupUi();
    void fillALDInfo();
    void saveALDays();

    int m_aldId;

    QComboBox *m_cbUser;
    QDateEdit *m_deDateFrom;
    QDateEdit *m_deDateTo;

    QPushButton *m_pbSave;
    QPushButton *m_pbCancel;
};

#endif // ADDMODIFYALDAYS_H
