#-------------------------------------------------
#
# Project created by QtCreator 2016-04-21T10:49:22
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = book
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    insertdialog.cpp \
    searchcondialog.cpp \
    qsearchtablemodel.cpp \
    databasedialog.cpp

HEADERS  += mainwindow.h \
    insertdialog.h \
    searchcondialog.h \
    qsearchtablemodel.h \
    databasedialog.h

FORMS    += mainwindow.ui \
    insertdialog.ui \
    searchcondialog.ui \
    databasedialog.ui
