#-------------------------------------------------
#
# Project created by QtCreator 2013-04-23T19:05:48
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chatServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chatserver.cpp \
    chatrunnable.cpp \
    chatthreads.cpp

HEADERS  += mainwindow.h \
    chatserver.h \
    chatrunnable.h \
    chatthreads.h

FORMS    += mainwindow.ui \

