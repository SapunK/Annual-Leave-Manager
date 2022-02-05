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

class QSpinBox;

class Holidays : public CustomTabWidget
{
    Q_OBJECT
public:
    explicit Holidays(QWidget *parent = nullptr);

private:
    void setupModelView();
    void setModelQuery();
    QSpinBox *m_sbYear;

private slots:
    void addClicked();
    void modifyClicked();
    void deleteClicked();

};

#endif // HOLIDAYS_H
