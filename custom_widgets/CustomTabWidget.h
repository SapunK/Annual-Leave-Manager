#ifndef CUSTOMTABWIDGET_H
#define CUSTOMTABWIDGET_H

#include <QWidget>

class QPushButton;
class QSqlQueryModel;
class CustomTableView;

class CustomTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomTabWidget(QWidget *parent = nullptr);

protected:

    QPushButton *m_pbAdd;
    QPushButton *m_pbModify;
    QPushButton *m_pbDelete;

    QSqlQueryModel *m_model;
    CustomTableView *m_table;

private:
    void setupUi();

protected slots:
    virtual void addClicked() = 0;
    virtual void modifyClicked() = 0;
    virtual void deleteClicked() = 0;

};

#endif // CUSTOMTABWIDGET_H
