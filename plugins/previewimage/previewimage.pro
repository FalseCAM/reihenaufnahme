TARGET          = previewimage
load(qt_plugin)
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

DESTDIR		= ../../plugins

LIBS += -lexiv2
