#-------------------------------------------------
#
# Project created by QtCreator 2018-12-03T15:34:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = radio_net_simulatior
TEMPLATE = app


SOURCES += main.cpp\
        mainform.cpp \
    radioitem.cpp \
    mgraphicscene.cpp \
    mtablemodel.cpp \
    connectionmanager.cpp \
    radioitemlinker.cpp \
    simulatorradiopath.cpp \
    message.cpp

HEADERS  += mainform.h \
    radioitem.h \
    mgraphicscene.h \
    mtablemodel.h \
    connectionmanager.h \
    radioitemlinker.h \
    halinterfaces/include/radiopath.h \
    simulatorradiopath.h \
    message.h \
    ui_mainform.h

FORMS    += mainform.ui

DEFINES += DEBUG_MESSAGE_SEND

