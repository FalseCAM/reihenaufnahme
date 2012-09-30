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

#ifndef PHOTO_H
#define PHOTO_H

#include <QtCore/QObject>
#include <QtCore/QJsonObject>
class Photo : public QObject
{
    Q_OBJECT
public:
    explicit Photo(QObject *parent = 0);
    Photo(const Photo &);
    Photo(QJsonObject jobject);

    QString getId();
    QString getTitle();
    QString getUrl(QString size);

    void setAlbum(QString album);
    QString getAlbum();
signals:
    
public slots:
private:
    QString id;
    QString url;
    QString title;
    QString album;
};

#endif // PHOTO_H
