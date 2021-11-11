#-------------------------------------------------
#
# Project created by QtCreator 2016-11-25T20:28:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KreuzungsSimulator
TEMPLATE = app


SOURCES += main.cpp\
        simulationgui.cpp \
    kreuzungsview.cpp \
    konfiguration.cpp \
    statistikdaten.cpp \
    kreuzung.cpp \
    fahrzeugszenariogui.cpp \
    fussgaengerszenariogui.cpp \
    phasendauergui.cpp \
    statistikgui.cpp \
    fahrzeugampel.cpp \
    fussgaengerueberweg.cpp \
    fahrzeugspur.cpp \
    fahrzeug.cpp \
    fussgaenger.cpp \
    spurstatistik.cpp \
    fahrzeugszenario.cpp \
    fussgaengerszenario.cpp \
    fussgaengerampel.cpp

HEADERS  += simulationgui.h \
    kreuzungsview.h \
    konfiguration.h \
    statistikdaten.h \
    kreuzung.h \
    fahrzeugszenariogui.h \
    fussgaengerszenariogui.h \
    phasendauergui.h \
    statistikgui.h \
    fahrzeugampel.h \
    fussgaengerueberweg.h \
    fahrzeugspur.h \
    fahrzeug.h \
    fussgaenger.h \
    spurstatistik.h \
    fahrzeugszenario.h \
    fussgaengerszenario.h \
    fussgaengerampel.h

FORMS    += simulationgui.ui \
    fahrzeugszenariogui.ui \
    fussgaengerszenariogui.ui \
    phasendauergui.ui \
    statistikgui.ui

DISTFILES +=

RESOURCES += \
    images.qrc
