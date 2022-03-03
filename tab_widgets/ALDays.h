#ifndef ALDAYS_H
#define ALDAYS_H

#include "custom_widgets/CustomTabWidget.h"

namespace AnnualLeaveDays_NS {
enum EALDays{
    name,
    year,
    days,
    id
};
}

class QSpinBox;

class ALDays : public CustomTabWidget
{
    Q_OBJECT
public:
    explicit ALDays(QWidget *parent = nullptr);

private:
    void setupModelView();
    void setModelQuery();

    QSpinBox *m_sbYear;

private slots:
    void addClicked();
    void modifyClicked();
    void deleteClicked();

};

#endif // ALDAYS_H
