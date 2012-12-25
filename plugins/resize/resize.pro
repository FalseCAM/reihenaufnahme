TEMPLATE = lib
CONFIG += qt plugin
TARGET          = resize
QT              += core widgets

INCLUDEPATH	+= ../../reihenaufnahme
HEADERS         = resize.h \
    widget.h \
    ../../reihenaufnahme/image.h
SOURCES         = resize.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp
FORMS += \
    widget.ui
RESOURCES += \
    resize.qrc
OTHER_FILES += \
    resize.json

TRANSLATIONS += ../../i18n/resize_de.ts \
                ../../i18n/resize_en.ts \
                ../../i18n/resize_fr.ts \
                ../../i18n/resize_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2
