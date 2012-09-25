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

#ifndef FLICKRDOWNLOAD_H
#define FLICKRDOWNLOAD_H

#include <QtCore/QtPlugin>
#include <QtCore/QObject>
#include <QtGui/QIcon>
#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QList>
#include "plugins/inputplugin.h"
#include "image.h"
#include "widget.h"

/*
 * Icon from: http://findicons.com/icon/73725/flickr
 * Designer: Jeremy Roux
 */

class FlickrDownload : public InputPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "reihenaufnahme.flickr-download" FILE "flickr-download.json")
    Q_INTERFACES(InputPlugin)

public:
    FlickrDownload();
    ~FlickrDownload();
    QString getName();
    QString getTitle();
    QString getVersion();
    QString getAuthor();
    QString getDescription();
    QIcon getIcon();
    QWidget *getWidget();

    void init();
    bool hasNext();
    Image *next();
    int getProgress();

private:
    Widget *widget;
    bool has_next;
    QList<Photo> photos;
    int position;
    QNetworkAccessManager *manager;

    QString getFolder(QString file);
    QString getName(QString file);
    Exiv2::ExifData *readExifData(QString file);
};

#endif // FLICKRDOWNLOAD_H
