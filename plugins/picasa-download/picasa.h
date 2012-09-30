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

#ifndef PICASA_H
#define PICASA_H

#include <QtCore/QObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QUrl>
#include "photo.h"
#include "album.h"
#include "image.h"
#include "logindialog.h"

class Picasa : public QObject
{
    Q_OBJECT
public:
    explicit Picasa(QObject *parent = 0);
    ~Picasa();
    
signals:
    
public slots:
    QJsonDocument getJsonDocument(QUrl url);
    QString getUsernameById(QString id);
    QList<Photo> getPhotosByAlbum(Album *album);
    QList<Album> getAlbumsByUserId(QString userid);

    // auth
    void genToken();
    QString getToken();
    QString getCurrentUser();

    QString getAuthUrl(QString perms);
    void uploadImage(QByteArray *image, QString name);
    void setAuthCode(QString code);


private:
    QString client_id;
    QString client_secret;
    QString redirect_uri;
    QString auth_code;
    QString access_token;
    QString refresh_token;
    QString token_type;

    QString currentUser;
    QString currentUserId;
};

#endif // FLICKR_H
