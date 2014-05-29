#-------------------------------------------------
#
# Project created by QtCreator 2014-05-20T23:08:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SearchCSV
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qdsvtablemodel/qdsvtablemodel.cpp \
    qcolumnsearchmodel.cpp

HEADERS  += mainwindow.h \
    qdsvtablemodel/qdsvtablemodel.h \
    qcolumnsearchmodel.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    test.csv
