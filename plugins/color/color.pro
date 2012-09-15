TARGET          = color
load(qt_plugin)
QT              += core widgets

INCLUDEPATH	+= ../../reihenaufnahme

HEADERS         = color.h \
    widget.h \
    ../../reihenaufnahme/image.h
SOURCES         = color.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp
FORMS += \
    widget.ui
RESOURCES += \
    color.qrc
OTHER_FILES += \
    color.json

TRANSLATIONS += ../../i18n/color_de.ts \
                ../../i18n/color_en.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2
