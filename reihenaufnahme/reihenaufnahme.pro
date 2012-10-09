TARGET = reihenaufnahme
QT       += core widgets network

TEMPLATE = app

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
                ../i18n/reihenaufnahme_fr.ts \
                ../i18n/reihenaufnahme_ru.ts \

RESOURCES += \
    reihenaufnahme.qrc

win32 {
    RC_FILE += reihenaufnahme.rc
}

DESTDIR     = ../

LIBS += -lexiv2

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../message/release/ -lmessage
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../message/debug/ -lmessage
else:unix: LIBS += -L$$OUT_PWD/../message/ -lmessage

INCLUDEPATH += $$PWD/../message
DEPENDPATH += $$PWD/../message
