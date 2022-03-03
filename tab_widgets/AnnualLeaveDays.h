#ifndef ANNUALLEAVEDAYS_H
#define ANNUALLEAVEDAYS_H

#include "custom_widgets/CustomTabWidget.h"

class QSpinBox;

class AnnualLeaveDays : public CustomTabWidget
{
    Q_OBJECT
public:
    explicit AnnualLeaveDays(QWidget *parent = nullptr);

private:
    void setupModelView();
    void setModelQuery();
    QSpinBox *m_sbYear;

private slots:
    void addClicked();
    void modifyClicked();
    void deleteClicked();
};

#endif // ANNUALLEAVEDAYS_H
