TARGET          = rename
load(qt_plugin)
QT              += core widgets

INCLUDEPATH	+= ../../reihenaufnahme
HEADERS         = rename.h \
    widget.h \
    ../../reihenaufnahme/image.h
SOURCES         = rename.cpp \
    widget.cpp \
    ../../reihenaufnahme/image.cpp
FORMS += \
    widget.ui
RESOURCES += \
    rename.qrc
OTHER_FILES += \
    rename.json

TRANSLATIONS += ../../i18n/rename_de.ts \
                ../../i18n/rename_en.ts \
                ../../i18n/rename_fr.ts \
                ../../i18n/rename_ru.ts \

DESTDIR		= ../../plugins

LIBS += -lexiv2
