TEMPLATE = lib
CONFIG += qt plugin
TARGET          = rotate
QT              += core widgets

INCLUDEPATH	+= ../../reihenaufnahme
HEADERS         = rotate.h \
    widget.h \
    ../../reihenaufnahme/image.h
SOURCES         = rotate.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp
FORMS += \
    widget.ui
RESOURCES += \
    rotate.qrc
OTHER_FILES += \
    rotate.json

TRANSLATIONS += ../../i18n/rotate_de.ts \
                ../../i18n/rotate_en.ts \
                ../../i18n/rotate_fr.ts \
                ../../i18n/rotate_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2
