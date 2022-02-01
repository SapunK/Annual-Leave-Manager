#ifndef HOLIDAYS_H
#define HOLIDAYS_H

#include "custom_widgets/CustomTabWidget.h"

namespace Holiday_NS {
enum EHolidayColumns{
    id,
    date,
    description
};
}

class Holidays : public CustomTabWidget
{
    Q_OBJECT
public:
    explicit Holidays(QWidget *parent = nullptr);

private:
    void setupModelView();

private slots:
    void addClicked();
    void modifyClicked();
    void deleteClicked();

};

#endif // HOLIDAYS_H
