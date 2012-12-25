TEMPLATE = lib
CONFIG += qt plugin
TARGET          = blur
QT              += core widgets

INCLUDEPATH	+= ../../reihenaufnahme
HEADERS         = blur.h \
    widget.h \
    previewimagelabel.h \
    ../../reihenaufnahme/image.h
SOURCES         = blur.cpp \
    widget.cpp \
    previewimagelabel.cpp \
    ../../reihenaufnahme/image.cpp
FORMS += \
    widget.ui
RESOURCES += \
    blur.qrc

OTHER_FILES += \
    blur.json

TRANSLATIONS += ../../i18n/blur_de.ts \
                ../../i18n/blur_en.ts \
                ../../i18n/blur_fr.ts \
                ../../i18n/blur_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2
