TEMPLATE = lib
CONFIG += qt plugin
TARGET          = overlay-text
QT              += core widgets

INCLUDEPATH	+= ../../reihenaufnahme
HEADERS         = overlay-text.h \
    widget.h \
    ../../reihenaufnahme/image.h
SOURCES         = overlay-text.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp
FORMS += \
    widget.ui
RESOURCES += \
    overlay-text.qrc
OTHER_FILES += \
    overlay-text.json

TRANSLATIONS += ../../i18n/overlay-text_de.ts \
                ../../i18n/overlay-text_en.ts \
                ../../i18n/overlay-text_fr.ts \
                ../../i18n/overlay-text_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2
