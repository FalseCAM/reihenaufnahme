TARGET = reihenaufnahme
QT       += core widgets

TEMPLATE = app

INCLUDEPATH += C:\Dev\Qt5.0.0beta1\Desktop\Qt\5.0.0-beta1\msvc2010\include

SOURCES += main.cpp\
    mainwindow.cpp \
    tipsdialog.cpp \
    reihenaufnahme.cpp \
    translation.cpp \
    aboutdialog.cpp \
    plugins/pluginsconfigdialog.cpp \
    plugins/pluginloader.cpp \
    plugins/pcpluginwidget.cpp \
    image.cpp \
    process.cpp \
    imgedit.cpp

HEADERS  += mainwindow.h \
    tipsdialog.h \
    reihenaufnahme.h \
    translation.h \
    aboutdialog.h \
    plugins/pluginsconfigdialog.h \
    plugins/inputplugin.h \
    plugins/outputplugin.h \
    plugins/pluginloader.h \
    plugins/plugin.h \
    plugins/pcpluginwidget.h \
    plugins/editplugin.h \
    image.h \
    process.h \
    imgedit.h

FORMS    += mainwindow.ui \
    tipsdialog.ui \
    aboutdialog.ui \
    plugins/pluginsconfigdialog.ui \
    plugins/pcpluginwidget.ui

TRANSLATIONS += ../i18n/reihenaufnahme_de.ts \
                ../i18n/reihenaufnahme_en.ts \

RESOURCES += \
    reihenaufnahme.qrc

DESTDIR     = ../

LIBS += -lexiv2
