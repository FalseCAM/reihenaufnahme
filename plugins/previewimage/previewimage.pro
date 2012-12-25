TEMPLATE = lib
CONFIG += qt plugin
TARGET          = previewimage
QT              += core widgets

INCLUDEPATH	+= ../../reihenaufnahme
HEADERS         = previewimage.h \
    widget.h \
    ../../reihenaufnahme/image.h
SOURCES         = previewimage.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp
FORMS += \
    widget.ui
RESOURCES += \
    previewimage.qrc
OTHER_FILES += \
    previewimage.json

TRANSLATIONS += ../../i18n/previewimage_de.ts \
                ../../i18n/previewimage_en.ts \
                ../../i18n/previewimage_fr.ts \
                ../../i18n/previewimage_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2
