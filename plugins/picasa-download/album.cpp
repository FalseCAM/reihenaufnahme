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

#include "album.h"
#include <QtCore/QJsonArray>

Album::Album(QObject *parent) :
    QObject(parent)
{
}

Album::Album(const Album & a){
    this->id = a.id;
    this->ownerid = a.ownerid;
    this->title = a.title;
    this->num_photos = a.num_photos;
    this->thumbnailUrl = a.thumbnailUrl;
}

Album::Album(QJsonObject jobject){
    this->id = jobject.take("gphoto$id").toObject().take("$t").toString();
    this->ownerid = jobject.take("gphoto$user").toObject().take("$t").toString();
    this->title = jobject.take("gphoto$name").toObject().take("$t").toString();
    this->num_photos = QString::number(
                jobject.take("gphoto$numphotos").toObject().take("$t").toDouble());
    this->thumbnailUrl = jobject.take("media$group").toObject()
            .take("media$thumbnail").toArray().first().toObject().take("url").toString();
    qDebug("%s", qPrintable(id + " " + title + " " + ownerid));
}

QString Album::getId(){
    return this->id;
}

QString Album::getOwnerId(){
    return this->ownerid;
}

QString Album::getTitle(){
    return this->title;
}

QString Album::getNumPhotos(){
    return this->num_photos;
}

QString Album::getThumbnailUrl(){
    return this->thumbnailUrl;
}
