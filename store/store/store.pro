#-------------------------------------------------
#
# Project created by QtCreator 2018-07-20T20:03:23
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = store
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
    application.cpp \
    catitemedit.cpp \
    dialogtpl.cpp \
    catalogue.cpp \
    posaction.cpp \
    books.cpp \
    filter.cpp

HEADERS += \
        mainwindow.h \
    application.h \
    catitemedit.h \
    dialogtpl.h \
    catalogue.h \
    posaction.h \
    books.h \
    filter.h

FORMS += \
buttonsframe.ui \
catitemframe.ui \
    filter.ui
