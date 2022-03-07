#ifndef USERDAYS_H
#define USERDAYS_H

#include "custom_widgets/CustomTabWidget.h"

namespace UserDays_NS {
enum EALDays{
    name,
    year,
    days,
    id,
    remainingDays
};
}

class QSpinBox;

class UserDays : public CustomTabWidget
{
    Q_OBJECT
public:
    explicit UserDays(QWidget *parent = nullptr);

private:
    void setupModelView();
    void setModelQuery();

    QSpinBox *m_sbYear;

private slots:
    void addClicked();
    void modifyClicked();
    void deleteClicked();

};

#endif // USERDAYS_H
