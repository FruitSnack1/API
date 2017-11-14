#-------------------------------------------------
#
# Project created by QtCreator 2017-11-13T14:52:39
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tumblr
TEMPLATE = app

CONFIG += openssl-linked

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
