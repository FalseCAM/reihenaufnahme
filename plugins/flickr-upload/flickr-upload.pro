TARGET          = flickr-upload
load(qt_plugin)
QT              += core widgets network webkit

INCLUDEPATH	+= ../../reihenaufnahme
HEADERS         = flickr-upload.h \
    widget.h \
    ../../reihenaufnahme/image.h \
    ../flickr-download/flickr.h \
    ../flickr-download/photo.h \
    ../flickr-download/logindialog.h
SOURCES         = flickr-upload.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp \
    ../flickr-download/flickr.cpp \
    ../flickr-download/photo.cpp \
    ../flickr-download/logindialog.cpp
FORMS += \
    widget.ui \
    ../flickr-download/logindialog.ui
OTHER_FILES += \
    flickr-upload.json

TRANSLATIONS += ../../i18n/flickr-upload_de.ts \
                ../../i18n/flickr-upload_en.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2

RESOURCES += \
    flickr-upload.qrc
