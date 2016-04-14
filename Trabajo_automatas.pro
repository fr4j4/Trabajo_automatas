#-------------------------------------------------
#
# Project created by QtCreator 2016-03-29T16:15:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Trabajo_automatas
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pilapalabra.cpp \
    listatransiciones.cpp \
    listaestadosfinales.cpp

HEADERS  += mainwindow.h \
    pilapalabra.h \
    listatransiciones.h \
    listaestadosfinales.h

FORMS    += mainwindow.ui
RC_FILE = myapp.rc
