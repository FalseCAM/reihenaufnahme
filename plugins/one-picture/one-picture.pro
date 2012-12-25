TEMPLATE = lib
CONFIG += qt plugin
TARGET          = one-picture
QT              += core widgets

INCLUDEPATH	+= ../../reihenaufnahme
HEADERS         = one-picture.h \
    widget.h \
    ../../reihenaufnahme/image.h
SOURCES         = one-picture.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp
FORMS += \
    widget.ui
RESOURCES += \
    one-picture.qrc
OTHER_FILES += \
    one-picture.json

TRANSLATIONS += ../../i18n/one-picture_de.ts \
                ../../i18n/one-picture_en.ts \
                ../../i18n/one-picture_fr.ts \
                ../../i18n/one-picture_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2
