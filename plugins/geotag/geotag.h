/**
    This file is part of program Reihenaufnahme
    Copyright (C) 2012  FalseCAM

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GEOTAG_H
#define GEOTAG_H

#include <QtCore/QtPlugin>
#include <QtCore/QObject>
#include <QtGui/QIcon>
#include "plugins/editplugin.h"
#include "widget.h"


class Geotag : public EditPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "reihenaufnahme.geotag" FILE "geotag.json")
    Q_INTERFACES(EditPlugin)

public:
    Geotag();
    ~Geotag();
    QString getName();
    QString getTitle();
    QString getVersion();
    QString getAuthor();
    QString getDescription();
    QIcon getIcon();
    QWidget *getWidget();

    void edit(Image *image);

private:
    Widget *widget;
    void setExifKey(QString key, QString value, Exiv2::ExifData *exifData);
    void setExifKeyRational(QString key, QString value, Exiv2::ExifData *exifData);
};

#endif // GEOTAG_H
