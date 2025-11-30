QT       += core gui \
    quick
QT += sql
QT += core gui widgets printsupport
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# ==================== OPENCV POUR MINGW ====================
win32 {
    # Chemin vers OpenCV MinGW (CORRIGÉ)
    OPENCV_PATH = C:/opencv-mingw/OpenCV-MinGW-Build-OpenCV-4.5.5-x64

    # Dossiers d'inclusion
    INCLUDEPATH += $$OPENCV_PATH/include

    # Bibliothèques
    LIBS += -L$$OPENCV_PATH/x64/mingw/lib \
            -llibopencv_core455 \
            -llibopencv_imgproc455 \
            -llibopencv_imgcodecs455 \
            -llibopencv_objdetect455 \
            -llibopencv_highgui455

    # Copier automatiquement les DLLs
    QMAKE_POST_LINK += $$quote(cmd /c xcopy /Y /I \"$$shell_path($$OPENCV_PATH/x64/mingw/bin/*.dll)\" \"$$shell_path($$OUT_PWD)\" 2>nul)
    # Copier le fichier haarcascade automatiquement
    QMAKE_POST_LINK += $$quote(& cmd /c copy /Y \"$$shell_path($$PWD/haarcascade_frontalface_default.xml)\" \"$$shell_path($$OUT_PWD)\" 2>nul)
}

SOURCES += \
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

RESOURCES += \
    M.qrc \
    Mpower.qrc \
    amg.qrc \
    img.qrc \
    img2.qrc \
    mm.qrc \
    resources.qrc
