#ifndef VACATIONDAYS_H
#define VACATIONDAYS_H

#include "custom_widgets/CustomTabWidget.h"

namespace VacationDays_NS {
enum EColumns {
    user,
    year,
    days
};

}

class VacationDays : public CustomTabWidget
{
    Q_OBJECT
public:
    explicit VacationDays(QWidget *parent = nullptr);

private:
    void setupModelView();

private slots:
    void addClicked();
    void modifyClicked();
    void deleteClicked();

};

#endif // VACATIONDAYS_H
