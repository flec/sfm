#-------------------------------------------------
#
# Project created by QtCreator 2015-10-19T11:57:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sfm
TEMPLATE = app


SOURCES += src/ui/mainwindow/mainwindow.cpp \
    src/ui/mainwindow/featuredetectiontab.cpp \
    src/ui/widgets/cvimagewidget.h

HEADERS  += src/ui/mainwindow/mainwindow.h \
    src/ui/mainwindow/featuredetectiontab.h


FORMS    += src/ui/mainwindow/mainwindow.ui \
    src/ui/mainwindow/featuredetectiontab.ui
