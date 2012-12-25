TEMPLATE = lib
CONFIG += qt plugin
TARGET          = rename-album
QT              += core widgets

INCLUDEPATH	+= ../../reihenaufnahme
HEADERS         = rename-album.h \
    widget.h \
    ../../reihenaufnahme/image.h
SOURCES         = rename-album.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp
FORMS += \
    widget.ui
RESOURCES += \
    rename-album.qrc
OTHER_FILES += \
    rename-album.json

TRANSLATIONS += ../../i18n/rename-album_de.ts \
                ../../i18n/rename-album_en.ts \
                ../../i18n/rename-album_fr.ts \
                ../../i18n/rename-album_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2
