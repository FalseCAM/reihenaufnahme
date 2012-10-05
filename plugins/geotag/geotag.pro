TARGET          = geotag
load(qt_plugin)
QT              += core widgets network

INCLUDEPATH	+= ../../reihenaufnahme
HEADERS         = geotag.h \
    map.h \
    widget.h \
    ../../reihenaufnahme/image.h
SOURCES         = geotag.cpp \
    map.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp
FORMS += \
    widget.ui
RESOURCES += \
    geotag.qrc
OTHER_FILES += \
    geotag.json

TRANSLATIONS += ../../i18n/geotag_de.ts \
                ../../i18n/geotag_en.ts \
                ../../i18n/geotag_fr.ts \
                ../../i18n/geotag_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2
