#ifndef USERS_H
#define USERS_H

#include "custom_widgets/CustomTabWidget.h"

class Users : public CustomTabWidget
{
    Q_OBJECT
public:
    explicit Users(QWidget *parent = nullptr);

private:
    void setupModelView();
    void setModelQuery();

private slots:
    void addClicked();
    void modifyClicked();
    void deleteClicked();

};

#endif // USERS_H
