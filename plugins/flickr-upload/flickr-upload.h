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

#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QtCore/QtPlugin>
#include <QtCore/QObject>
#include <QtGui/QIcon>
#include "widget.h"
#include "plugins/outputplugin.h"


class FlickrUpload : public OutputPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "reihenaufnahme.flickr-upload" FILE "flickr-upload.json")
    Q_INTERFACES(OutputPlugin)

public:
    FlickrUpload();
    ~FlickrUpload();
    QString getName();
    QString getTitle();
    QString getVersion();
    QString getAuthor();
    QString getDescription();
    QIcon getIcon();
    QWidget *getWidget();

    void out(Image *image);
    void finnish();

private:
    Widget *widget;
    void saveExifData(Exiv2::ExifData *exifData, QByteArray *image);
};

#endif // SAVEFILE_H
