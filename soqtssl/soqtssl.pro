#-------------------------------------------------
#
# Project created by QtCreator 2012-11-02T10:40:00
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = soqtssl
CONFIG   += console
#CONFIG   -= app_bundle
CONFIG += x86 x86_64

TEMPLATE = app

HEADERS += \
listerrs.h

SOURCES += main.cpp \
listerrs.cpp

RESOURCES += \
    cert.qrc
