QT       += core gui sql

DEFINES += QT_DEPRECATED_WARNINGS

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    custom_widgets/CustomTabWidget.cpp \
    custom_widgets/CustomTableView.cpp \
    dialogs/AddModifyALDays.cpp \
    dialogs/AddModifyHoliday.cpp \
    dialogs/AddModifyUser.cpp \
    main.cpp \
    mainwindow.cpp \
    models/test.cpp \
    tab_widgets/ALDays.cpp \
    tab_widgets/Holidays.cpp \
    tab_widgets/Users.cpp \
    util/DB_Functions.cpp \
    util/HelperFunctions.cpp \
    util/appconsts.cpp

HEADERS += \
    custom_widgets/CustomTabWidget.h \
    custom_widgets/CustomTableView.h \
    dialogs/AddModifyALDays.h \
    dialogs/AddModifyHoliday.h \
    dialogs/AddModifyUser.h \
    mainwindow.h \
    tab_widgets/ALDays.h \
    tab_widgets/Holidays.h \
    tab_widgets/Users.h \
    util/DB_Functions.h \
    util/HelperFunctions.h \
    util/appconsts.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L$$PWD/lib