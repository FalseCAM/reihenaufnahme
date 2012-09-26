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

#ifndef FLICKR_H
#define FLICKR_H

#include <QtCore/QObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QStringList>
#include <QtCore/QMap>
#include "photo.h"
#include "image.h"
#include "logindialog.h"

class Flickr : public QObject
{
    Q_OBJECT
public:
    explicit Flickr(QObject *parent = 0);
    ~Flickr();
    
signals:
    
public slots:
    QJsonDocument getJsonDocument(QUrl url);
    QString getIdByUsername(QString username);
    QString getUsernameById(QString id);
    QList<Photo> getPublicPhotosByUserId(QString userid);
    QList<Photo> getPhotosByUserId(QString userid);
    // auth
    void genFrob();
    QString getFrob();
    void genToken();
    QString getToken();
    QString getCurrentUser();

    QString getSig(QMap<QString, QString> parameter);
    QString getRequestUrl(QMap<QString, QString> parameter);
    QString getAuthUrl(QString perms);
    void uploadImage(QByteArray *image, QString name, QString description, bool friendsVisible);



private:
    QString api_key;
    QString secret_key;
    QString frob;
    QString token;
    QString currentUser;
    QString currentUserId;
    QNetworkAccessManager *manager;

    QByteArray genBoundary();
    QByteArray constructField ( QString name, QString content,
                                QByteArray boundary,
                                QString filename = QString());
};

#endif // FLICKR_H
