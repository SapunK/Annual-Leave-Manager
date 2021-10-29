#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QDebug>

#include "util/HelperFunctions.h"
#include "tab_widgets/Users.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    HelperFunctions::setDesktopSize();
    setWindowState(Qt::WindowMaximized);

    dbConnect();
    setupUi();
}

void MainWindow::setupUi()
{
    QWidget *mainWidget = new QWidget(this);
    QTabWidget *tabWidget = new QTabWidget(mainWidget);
    QVBoxLayout *layout = new QVBoxLayout(mainWidget);

    Users *usersWidget = new Users(this);
    tabWidget->addTab(usersWidget, "Users");

    layout->addWidget(tabWidget);

    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);
    mainWidget->show();
}

void MainWindow::dbConnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("vacation_days_manager");
    db.setUserName("postgres");
    db.setPassword("postgres");
    db.setPort(5432);

    bool bSuccessfulConn = db.open();

    if(bSuccessfulConn != true)
    {
        qDebug()<<"DB Connect fail";
    }
    else {
        qDebug()<<"Successful DB connection";
    }
}

MainWindow::~MainWindow()
{
}
