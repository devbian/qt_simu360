#-------------------------------------------------
#
# Project created by QtCreator 2013-05-29T09:45:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Simu360
TEMPLATE = app


SOURCES += main.cpp\
    titlebar.cpp \
    toolbar.cpp \
    contentwidget.cpp \
    statusbar.cpp \
    mainframe.cpp \
    mybtn.cpp

HEADERS  += \
    titlebar.h \
    toolbar.h \
    contentwidget.h \
    statusbar.h \
    mainframe.h \
    mybtn.h

FORMS    += \
    mainframe.ui

RESOURCES += \
    res.qrc
