TEMPLATE = lib
CONFIG += qt plugin
TARGET          = filechooser
QT              += core widgets gui
INCLUDEPATH	+= ../../reihenaufnahme

HEADERS         = filechooser.h \
    widget.h \
    ../../reihenaufnahme/image.h
SOURCES         = filechooser.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp
FORMS += \
    widget.ui
OTHER_FILES += \
    filechooser.json

TRANSLATIONS += ../../i18n/filechooser_de.ts \
                ../../i18n/filechooser_en.ts \
                ../../i18n/filechooser_fr.ts \
                ../../i18n/filechooser_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2
