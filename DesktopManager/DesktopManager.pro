# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = DesktopManager
DESTDIR = ../Win32/Debug
QT += core network webkit widgets gui webkitwidgets
CONFIG += debug
DEFINES += WIN64 QT_DLL QT_NETWORK_LIB QT_WEBKITWIDGETS_LIB QT_WIDGETS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(DesktopManager.pri)
