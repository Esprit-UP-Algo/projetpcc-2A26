QT       += core gui \
    quick
QT += sql
QT += core gui widgets printsupport
QT += core gui network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    StatisticsWidgetProduit.cpp \
    apiremises.cpp \
    connection.cpp \
    gestion_client.cpp \
    gestion_fournisseur.cpp \
    gestion_personnel.cpp \
    gestion_locaux.cpp \
    gestion_produit.cpp \
    main.cpp \
    mainwindow.cpp \
    sms_client.cpp \
    statisticswidget.cpp

HEADERS += \
    StatisticsWidgetProduit.h \
    apiremises.h \
    connection.h \
    gestion_client.h \
    gestion_personnel.h \
    gestion_locaux.h \
    gestion_fournisseur.h \
    gestion_produit.h \
    mainwindow.h \
    sms_client.h \
    statisticswidget.h
FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    M.qrc \
    Mpower.qrc \
    amg.qrc \
    img.qrc \
    img.qrc \
    img2.qrc \
    mm.qrc \
    resources.qrc
