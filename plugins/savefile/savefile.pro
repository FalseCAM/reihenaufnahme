TEMPLATE = lib
CONFIG += qt plugin
TARGET          = savefile
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
                ../../i18n/savefile_fr.ts \
                ../../i18n/savefile_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2
