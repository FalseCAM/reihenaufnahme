TARGET          = flickr-download
load(qt_plugin)
QT              += core widgets network webkit
INCLUDEPATH	+= ../../reihenaufnahme

HEADERS         = flickr-download.h \
    widget.h \
    ../../reihenaufnahme/image.h \
    flickr.h \
    photo.h \
    logindialog.h
SOURCES         = flickr-download.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp \
    flickr.cpp \
    photo.cpp \
    logindialog.cpp
FORMS += \
    widget.ui \
    logindialog.ui
OTHER_FILES += \
    flickr-downlaod.json

TRANSLATIONS += ../../i18n/flickr-download_de.ts \
                ../../i18n/flickr-download_en.ts \
                ../../i18n/flickr-download_fr.ts \
                ../../i18n/flickr-download_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2

RESOURCES += \
    flickr-download.qrc
