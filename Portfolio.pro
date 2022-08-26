QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Utilities/account.cpp \
    Widgets/accountwidgetcontainer.cpp \
    Utilities/transaction.cpp \
    Dialogs/accountdialog.cpp \
    Widgets/accountwidget.cpp \
    main.cpp \
    mw.cpp \
    Widgets/overallwidget.cpp \
    Dialogs/transactiondialog.cpp \
    Widgets/transactionwidget.cpp

HEADERS += \
    Utilities/account.h \
    Widgets/accountwidgetcontainer.h \
    Utilities/bank.h \
    Utilities/transaction.h \
    Dialogs/accountdialog.h \
    Widgets/accountwidget.h \
    mw.h \
    Widgets/overallwidget.h \
    Dialogs/transactiondialog.h \
    Widgets/transactionwidget.h

FORMS += \
    Widgets/accountwidgetcontainer.ui \
    Dialogs/accountdialog.ui \
    Widgets/accountwidget.ui \
    mw.ui \
    Widgets/overallwidget.ui \
    Dialogs/transactiondialog.ui \
    Widgets/transactionwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
