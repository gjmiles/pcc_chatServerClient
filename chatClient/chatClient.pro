#-------------------------------------------------
#
# Project created by QtCreator 2013-04-23T19:05:48
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chatClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    projdialog.cpp \
    client.cpp

HEADERS  += mainwindow.h \
    projdialog.h \
    client.h

FORMS    += mainwindow.ui \
    projdialog.ui
