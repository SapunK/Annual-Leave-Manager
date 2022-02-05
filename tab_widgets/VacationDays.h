#ifndef VACATIONDAYS_H
#define VACATIONDAYS_H

#include "custom_widgets/CustomTabWidget.h"

namespace VacationDays_NS {
enum EVacDays{
    name,
    year,
    days,
    id
};
}

class QSpinBox;

class VacationDays : public CustomTabWidget
{
    Q_OBJECT
public:
    explicit VacationDays(QWidget *parent = nullptr);

private:
    void setupModelView();
    void setModelQuery();

    QSpinBox *m_sbYear;

private slots:
    void addClicked();
    void modifyClicked();
    void deleteClicked();

};

#endif // VACATIONDAYS_H
