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

Photo::Photo(QObject *parent) :
    QObject(parent)
{
}

Photo::Photo(const Photo & p){
    this->id = p.id;
    this->farm = p.farm;
    this->server = p.server;
    this->secret = p.secret;
    this->title = p.title;
}

Photo::Photo(QJsonObject jobject){
    this->id = jobject.take("id").toString();
    this->farm = QString::number(jobject.take("farm").toDouble());
    this->server = jobject.take("server").toString();
    this->secret = jobject.take("secret").toString();
    this->title = jobject.take("title").toString();
}

QString Photo::getId(){
    return this->id;
}

QString Photo::getTitle(){
    return this->title;
}

QString Photo::getUrl(QString size){
    QString url;
    url = "http://farm"+farm+".staticflickr.com/"+server
            + "/" + id + "_" + secret + "_" + size + ".jpg";
    return url;
}
