TEMPLATE = lib
CONFIG += qt plugin
TARGET          = overlay
QT              += core widgets
INCLUDEPATH	+= ../../reihenaufnahme
HEADERS         = overlay.h \
    widget.h \
    ../../reihenaufnahme/image.h
SOURCES         = overlay.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp
FORMS += \
    widget.ui

RESOURCES += \
    overlay.qrc

OTHER_FILES += \
    overlay.json

TRANSLATIONS += ../../i18n/overlay_de.ts \
                ../../i18n/overlay_en.ts \
                ../../i18n/overlay_fr.ts \
                ../../i18n/overlay_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2
