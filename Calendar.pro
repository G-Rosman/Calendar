#-------------------------------------------------
#
# Project created by QtCreator 2016-01-23T00:17:24
#

QT       += core gui sql

CONFIG  += qaxcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PopupWindow
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    popup.cpp

HEADERS  += mainwindow.h \
    popup.h

FORMS    += mainwindow.ui
