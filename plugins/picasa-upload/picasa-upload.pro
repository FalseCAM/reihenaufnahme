TARGET          = picasa-upload
load(qt_plugin)
QT              += core widgets network

INCLUDEPATH	+= ../../reihenaufnahme
INCLUDEPATH	+= ../picasa-download

HEADERS         = picasa-upload.h \
    widget.h \
    ../../reihenaufnahme/image.h \
    ../picasa-download/picasa.h \
    ../picasa-download/photo.h \
    ../picasa-download/album.h
SOURCES         = picasa-upload.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp \
    ../picasa-download/picasa.cpp \
    ../picasa-download/photo.cpp \
    ../picasa-download/album.cpp
FORMS += \
    widget.ui
OTHER_FILES += \
    picasa-upload.json

TRANSLATIONS += ../../i18n/picasa-upload_de.ts \
                ../../i18n/picasa-upload_en.ts \
                ../../i18n/picasa-upload_fr.ts \
                ../../i18n/picasa-upload_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2

RESOURCES += \
    picasa-upload.qrc
