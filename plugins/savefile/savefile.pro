TARGET          = savefile
load(qt_plugin)
QT              += core widgets

INCLUDEPATH	+= ../../reihenaufnahme
HEADERS         = savefile.h \
    widget.h \
    ../../reihenaufnahme/image.h
SOURCES         = savefile.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp
FORMS += \
    widget.ui
OTHER_FILES += \
    savefile.json

TRANSLATIONS += ../../i18n/savefile_de.ts \
                ../../i18n/savefile_en.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2
