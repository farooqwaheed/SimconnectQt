#-------------------------------------------------
#
# Project created by QtCreator 2017-02-22T12:20:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimConnect
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    definations.h

FORMS    += mainwindow.ui
INCLUDEPATH += "C:\Program Files (x86)\Lockheed Martin\Prepar3D v3 SDK 3.4.22.19868\Utilities\SimConnect SDK\Inc"
#LIBS += "C:\Program Files (x86)\Lockheed Martin\Prepar3D v3 SDK 3.4.22.19868\Utilities\SimConnect SDK\lib\SimConnect.lib"
LIBS += kernel32.lib kernel32.lib user32.lib winspool.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib
#LIBS += "-LC:\QT SampleProjects\build-SimConnect-Desktop_Qt_5_8_0_MSVC2015_32bit-Debug\debug -lSimConnect


#win32: LIBS += -L$$PWD/'../../Program Files (x86)/Lockheed Martin/Prepar3D v3 SDK 3.4.22.19868/Utilities/SimConnect SDK/lib/' -lSimConnect

#INCLUDEPATH += $$PWD/'../../Program Files (x86)/Lockheed Martin/Prepar3D v3 SDK 3.4.22.19868/Utilities/SimConnect SDK'
#DEPENDPATH += $$PWD/'../../Program Files (x86)/Lockheed Martin/Prepar3D v3 SDK 3.4.22.19868/Utilities/SimConnect SDK'

win32: LIBS += -L$$PWD/../lib/ -lSimConnect

INCLUDEPATH += $$PWD/../inc
DEPENDPATH += $$PWD/../inc

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../lib/SimConnect.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../lib/libSimConnect.a
