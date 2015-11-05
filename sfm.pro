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
    src/ui/widgets/cvimagewidget.h \
    src/ui/mainwindow/featurematchingtab.cpp \
    src/ui/mainwindow/matrixfindingtab.cpp

HEADERS  += src/ui/mainwindow/mainwindow.h \
    src/ui/mainwindow/featuredetectiontab.h \
    src/ui/mainwindow/featurematchingtab.h \
    src/ui/mainwindow/matrixfindingtab.h


FORMS    += src/ui/mainwindow/mainwindow.ui \
    src/ui/mainwindow/featuredetectiontab.ui \
    src/ui/mainwindow/featurematchingtab.ui \
    src/ui/mainwindow/matrixfindingtab.ui
