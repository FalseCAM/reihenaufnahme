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

#ifndef ALBUM_H
#define ALBUM_H

#include <QtCore/QObject>
#include <QtCore/QJsonObject>

class Album : public QObject
{
    Q_OBJECT
public:
    explicit Album(QObject *parent = 0);
    Album(const Album &);
    Album(QJsonObject jobject);
    
    QString getId();
    QString getOwnerId();
    QString getTitle();
    QString getNumPhotos();
    QString getThumbnailUrl();
signals:
    
public slots:
private:
    QString id;
    QString ownerid;
    QString title;
    QString num_photos;
    QString thumbnailUrl;
};

#endif // ALBUM_H
