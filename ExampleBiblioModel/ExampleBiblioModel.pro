#-------------------------------------------------
#
# Project created by QtCreator 2018-05-31T19:42:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ExampleBiblioModel
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
        application.cpp \
        itemeditdialog.cpp \
        itemeditframe.cpp \
        helpers1.cpp \
        main.cpp \
        mainwindow.cpp \
    table.cpp \
    edit.cpp \
    bibliomodel.cpp \
    example1.cpp


TRANSLATIONS += biblio_rus.ts biblio_far.ts biblio_epo.ts


HEADERS += \
        application.h \
        itemeditdialog.h \
        itemeditframe.h \
        helpers.h \
        mainwindow.h \
        items.h \
    data.h \
    table.h \
    edit.h \
    bibliomodel.h \
    example1.h

RESOURCES += \
    biblio.qrc

FORMS += \
    example1.ui




