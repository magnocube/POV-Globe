#-------------------------------------------------
#
# Project created by QtCreator 2018-03-24T12:46:00
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PovGlobe1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    homepage.cpp \
    slidecontrol.cpp \
    pixeleditor.cpp \
    slide.cpp \
    myudp.cpp \
    customellipse.cpp \
    customrect.cpp \
    customtext.cpp \
    customrect_editor.cpp \
    customellipse_editor.cpp

HEADERS += \
        mainwindow.h \
    homepage.h \
    slidecontrol.h \
    pixeleditor.h \
    slide.h \
    myudp.h \
    customellipse.h \
    customrect.h \
    customtext.h \
    customrect_editor.h \
    customellipse_editor.h

FORMS += \
        mainwindow.ui \
    homepage.ui \
    slidecontrol.ui \
    pixeleditor.ui \
    customrect_editor.ui \
    customellipse_editor.ui

RESOURCES += \
    files.qrc
