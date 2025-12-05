QT += core gui sql network printsupport quick widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# ==================== OPENCV POUR MINGW ====================
win32 {

    # Chemin vers OpenCV MinGW
    #OPENCV_PATH = C:/opencv-mingw/OpenCV-MinGW-Build-OpenCV-4.5.5-x64

    # Dossiers d'inclusion
    #INCLUDEPATH += $$OPENCV_PATH/include

    # ⭐ CORRECTION : Enlever le préfixe "lib" devant les noms
    #LIBS += -L$$OPENCV_PATH/x64/mingw/lib \
            #-lopencv_core455 \
            #-lopencv_imgproc455 \
            #-lopencv_imgcodecs455 \
            #-lopencv_objdetect455 \
            #-lopencv_highgui455

    # Copier automatiquement les DLLs
    #QMAKE_POST_LINK += $$quote(cmd /c xcopy /Y /I \"$$shell_path($$OPENCV_PATH/x64/mingw/bin/*.dll)\" \"$$shell_path($$OUT_PWD)\" 2>nul)

    # Copier le fichier haarcascade automatiquement
    #QMAKE_POST_LINK += $$quote(& cmd /c copy /Y \"$$shell_path($$PWD/haarcascade_frontalface_default.xml)\" \"$$shell_path($$OUT_PWD)\" 2>nul)
}

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

# ⭐ CORRECTION : Supprimer le doublon "img.qrc"
RESOURCES += \
    M.qrc \
    Mpower.qrc \
    amg.qrc \
    img.qrc \
    img2.qrc \
    mm.qrc \
    resources.qrc
