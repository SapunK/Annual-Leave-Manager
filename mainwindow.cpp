#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QDebug>

#include "util/HelperFunctions.h"
#include "tab_widgets/Users.h"
#include "tab_widgets/UserDays.h"
#include "tab_widgets/Holidays.h"

//TODO rename project to annual leave manager and classes VacationDays to ALDays
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    HelperFunctions::setDesktopSize();
    setWindowState(Qt::WindowMaximized);
    setMinimumSize(HelperFunctions::desktopWidth() * 0.5, HelperFunctions::desktopWidth() * 0.3);

    dbConnect();
    setupUi();
}

void MainWindow::setupUi()
{
    QWidget *mainWidget = new QWidget(this);
    QTabWidget *tabWidget = new QTabWidget(mainWidget);
    QVBoxLayout *layout = new QVBoxLayout(mainWidget);

    Users *usersWidget = new Users(this);
    UserDays *alDays = new UserDays(this);
    Holidays *holidays = new Holidays(this);
    tabWidget->addTab(usersWidget, "Users");
    tabWidget->addTab(alDays, "User Days");
    tabWidget->addTab(holidays, "Holidays");

    layout->addWidget(tabWidget);

    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);
    mainWidget->show();
}

void MainWindow::dbConnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    //TODO rename db
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
