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

#include "photo.h"
#include <QtCore/QStringList>
Photo::Photo(QObject *parent) :
    QObject(parent)
{
}

Photo::Photo(const Photo & p){
    this->id = p.id;
    this->url = p.url;
    this->title = p.title;
    this->album = p.album;
}

Photo::Photo(QJsonObject jobject){
    this->id = jobject.take("gphoto$id").toObject().take("$t").toString();
    this->title = jobject.take("title").toObject().take("$t").toString();
    this->url = jobject.take("content").toObject().take("src").toString();
    qDebug("%s", qPrintable(this->id + " " + title + " " + url));
}

QString Photo::getId(){
    return this->id;
}

QString Photo::getTitle(){
    return this->title;
}

void Photo::setAlbum(QString album){
    this->album = album;
}

QString Photo::getAlbum(){
    return this->album;
}

QString Photo::getUrl(QString size){
    QString url_;
    QStringList list = url.split("/");
    for(int i = 0; i<list.size()-1;i++){
        url_.append(list.at(i));
        url_.append("/");
    }
    url_.append("s" + size + "/");
    url_.append(list.last());
    qDebug("url: %s", qPrintable(url_));
    return url_;
}
