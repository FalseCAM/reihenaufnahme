TEMPLATE = lib
CONFIG += qt plugin
TARGET          = picasa-download
QT              += core widgets network
INCLUDEPATH	+= ../../reihenaufnahme

HEADERS         = picasa-download.h \
    widget.h \
    ../../reihenaufnahme/image.h \
    photo.h \
    picasa.h \
    album.h \
    albumwidget.h
SOURCES         = picasa-download.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp \
    photo.cpp \
    picasa.cpp \
    album.cpp \
    albumwidget.cpp
FORMS += \
    widget.ui \
    albumwidget.ui
OTHER_FILES += \
    picasa-downlaod.json

TRANSLATIONS += ../../i18n/picasa-download_de.ts \
                ../../i18n/picasa-download_en.ts \
                ../../i18n/picasa-download_fr.ts \
                ../../i18n/picasa-download_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2

RESOURCES += \
    picasa-download.qrc
