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

#include "flickr.h"
#include <QtCore/QBuffer>
#include <QtCore/QEventLoop>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QCryptographicHash>


Flickr::Flickr(QObject *parent) :
    QObject(parent),
    secret_key("XXX"),
    api_key("XXX"),
    frob(""),
    token("")
{
    manager = new QNetworkAccessManager(this);
}

Flickr::~Flickr(){
    delete manager;
}

QJsonDocument Flickr::getJsonDocument(QUrl url){

    QNetworkReply *reply = manager->get(QNetworkRequest(url));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    return QJsonDocument().fromJson(reply->readAll());
}

QString Flickr::getIdByUsername(QString username){
    QString id;

    QMap<QString, QString> parameter;
    parameter.insert("method", "flickr.people.findByUsername");
    parameter.insert("api_key", api_key);
    parameter.insert("username", username);
    parameter.insert("format", "json");
    parameter.insert("nojsoncallback", "1");
    QString sig = getSig(parameter);
    parameter.insert("api_sig", sig);
    QUrl url = QUrl(getRequestUrl(parameter));

    QJsonDocument document = getJsonDocument(url);
    if(document.isObject()){
        id = document.object().take("user").toObject().take("id").toString();
    } else {
        id ="";
    }
    return id;
}

QString Flickr::getUsernameById(QString id){
    QString username;

    QMap<QString, QString> parameter;
    parameter.insert("method", "flickr.people.getInfo");
    parameter.insert("api_key", api_key);
    parameter.insert("user_id", id);
    parameter.insert("format", "json");
    parameter.insert("nojsoncallback", "1");
    QString sig = getSig(parameter);
    parameter.insert("api_sig", sig);
    QUrl url = QUrl(getRequestUrl(parameter));

    QJsonDocument document = getJsonDocument(url);
    if(document.isObject()){
        username = document.object().take("person").toObject().take("username").toString();
    } else {
        username ="";
    }
    return username;
}

QList<Photo> Flickr::getPublicPhotosByUserId(QString userid){
    QList<Photo> photos;
    QMap<QString, QString> parameter;
    parameter.insert("method", "flickr.people.getPublicPhotos");
    parameter.insert("api_key", api_key);
    parameter.insert("user_id", userid);
    parameter.insert("per_page", "1000");
    parameter.insert("extras", "owner_name");
    parameter.insert("format", "json");
    parameter.insert("nojsoncallback", "1");
    QString sig = getSig(parameter);
    parameter.insert("api_sig", sig);
    QUrl url = QUrl(getRequestUrl(parameter));
    QJsonDocument document = getJsonDocument(url);
    QJsonArray array = document.object().take("photos").toObject().take("photo").toArray();
    foreach(QJsonValue photo_, array){
        Photo photo(photo_.toObject());
        photos.append(photo);
    }
    return photos;
}

QList<Photo> Flickr::getPhotosByUserId(QString userid){
    QList<Photo> photos;
    QMap<QString, QString> parameter;
    parameter.insert("method", "flickr.people.getPhotos");
    parameter.insert("api_key", api_key);
    parameter.insert("auth_token", token);
    parameter.insert("user_id", userid);
    parameter.insert("per_page", "1000");
    parameter.insert("extras", "owner_name");
    parameter.insert("format", "json");
    parameter.insert("nojsoncallback", "1");
    QString sig = getSig(parameter);
    parameter.insert("api_sig", sig);
    QUrl url = QUrl(getRequestUrl(parameter));

    QJsonDocument document = getJsonDocument(url);
    QJsonArray array = document.object().take("photos").toObject().take("photo").toArray();
    foreach(QJsonValue photo_, array){
        Photo photo(photo_.toObject());
        photos.append(photo);
    }
    return photos;
}

// auth
void Flickr::genFrob(){
    QString frob;
    QMap<QString, QString> parameter;
    parameter.insert("method", "flickr.auth.getFrob");
    parameter.insert("api_key", api_key);
    parameter.insert("format", "json");
    parameter.insert("nojsoncallback", "1");
    QString sig = getSig(parameter);
    parameter.insert("api_sig", sig);
    QUrl url = QUrl(getRequestUrl(parameter));

    QJsonDocument document = getJsonDocument(url);
    if(document.isObject()){
        frob = document.object().take("frob").toObject().take("_content").toString();
    } else {
        frob ="";
    }
    this->frob = frob;
}

QString Flickr::getFrob(){
    return this->frob;
}

void Flickr::genToken(){
    QString token;
    QMap<QString, QString> parameter;
    parameter.insert("method", "flickr.auth.getToken");
    parameter.insert("api_key", api_key);
    parameter.insert("frob", frob);
    parameter.insert("format", "json");
    parameter.insert("nojsoncallback", "1");
    QString sig = getSig(parameter);
    parameter.insert("api_sig", sig);
    QUrl url = QUrl(getRequestUrl(parameter));

    QJsonDocument document = getJsonDocument(url);
    if(document.isObject()){
        QJsonObject auth = document.object().take("auth").toObject();
        token = auth.take("token").toObject()
                .take("_content").toString();
        currentUser = auth.take("user").toObject()
                .take("username").toString();
        currentUserId = auth.take("user").toObject()
                .take("nsid").toString();

    } else {
        token ="";
    }
    this->token = token;
}

QString Flickr::getToken(){
    return this->token;
}

QString Flickr::getCurrentUser(){
    return this->currentUser;
}

QString Flickr::getRequestUrl(QMap<QString, QString> parameter){
    // returns url build of parameters
    QString url = "http://api.flickr.com/services/rest/?";
    foreach(QString key, parameter.keys()){
        url.append(key+"="+parameter.take(key)+"&");
    }
    return url;
}

QString Flickr::getAuthUrl(QString perms){
    genFrob();
    QMap<QString, QString> parameter;
    parameter.insert("api_key", api_key);
    parameter.insert("frob", getFrob());
    parameter.insert("perms", perms);
    QString sig = getSig(parameter);
    parameter.insert("api_sig", sig);
    QString url = "http://flickr.com/services/auth/?";
    foreach(QString key, parameter.keys()){
        url.append(key+"="+parameter.take(key)+"&");
    }
    return url;
}

QString Flickr::getSig(QMap<QString, QString> parameter){
    QString sig = secret_key;
    QStringList sorted = parameter.keys();
    qSort(sorted.begin(), sorted.end());
    foreach(QString key, sorted){
        sig.append(key);
        sig.append(parameter.take(key));
    }
    QByteArray hash = QCryptographicHash::hash(sig.toUtf8(), QCryptographicHash::Md5);
    return hash.toHex();
}

/*
 * Some code from QtFlickr: http://www.qtflickr.com/
 */

void Flickr::uploadImage(QByteArray *image, QString name, QString description, bool friendsVisible){
    QByteArray boundary = genBoundary();
    QByteArray payload;
    QDataStream dataStream ( &payload, QIODevice::WriteOnly );

    QMap<QString,QString> map;
    map.insert ( "api_key", this->api_key );
    map.insert ( "auth_token", this->token );
    map.insert ( "title", name );
    map.insert ( "description", description);
    map.insert ( "is_public" , "0");
    if(friendsVisible)
        map.insert("is_friend", "1");
    else
        map.insert ( "is_friend", "0");

    QMapIterator<QString, QString> i ( map );
    QStringList keyList;
    while ( i.hasNext() )
    {
        i.next();
        keyList << i.key();
    }
    qSort ( keyList.begin(), keyList.end() );

    QString apiSig = getSig(map);

    // create fields
    for ( int i = 0; i < keyList.size(); ++i )
    {
        QByteArray field = constructField ( keyList.at ( i ),map.value ( keyList.at ( i ) ),boundary );
        dataStream.writeRawData ( field.data(), field.length() );

    }

    QByteArray sigField = constructField ( "api_sig", apiSig, boundary );
    dataStream.writeRawData ( sigField.data(), sigField.length() );

    QByteArray fileField = constructField ( "photo", "", boundary, name + ".jpg" );
    dataStream.writeRawData ( fileField.data(), fileField.length() );

    dataStream.writeRawData( image->data(), image->length());

    QByteArray endField;
    endField.append ( "\r\n--" );
    endField.append ( boundary );
    endField.append ( "--\r\n\r\n" );
    dataStream.writeRawData ( endField.data(), endField.length() );

    QString urlTmp("http://api.flickr.com/services/");
    urlTmp.append("upload/");

    QNetworkRequest uploadRequest ( urlTmp );
    uploadRequest.setRawHeader ( "Content-Type","multipart/form-data; boundary="+boundary );
    uploadRequest.setRawHeader ( "Host","ww.api.flickr.com" );

    QNetworkAccessManager manager(this);
    QNetworkReply *reply = manager.post ( uploadRequest , payload );
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

QByteArray Flickr::genBoundary()
{
    const int lenght = 15;
    QChar unicode[lenght];
    for ( int i = 0; i < lenght; ++i )
    {
        int sel = qrand() % 2;
        int temp = ( sel ) ? qrand() % 9 + 49 : qrand() % 23 + 98;
        unicode[i] = QChar ( temp );
    }

    int size = sizeof ( unicode ) / sizeof ( QChar );
    QString str = QString::fromRawData ( unicode, size );

    return str.toLatin1();
}

QByteArray Flickr::constructField ( QString name,
                                             QString content,
                                             QByteArray boundary,
                                             QString filename )
{
    QByteArray data;
    data.append ( "--" );
    data.append ( boundary );
    data.append ( "\r\n" );
    data.append ( "Content-Disposition: form-data; name=\"" );
    data.append ( name );
    if ( filename.isEmpty() )
    {
        data.append ( "\"\r\n\r\n" );
        data.append ( content );
        data.append ( "\r\n" );
    }
    else
    {
        data.append ( "\"; filename=\"" );
        data.append ( filename );
        data.append ( "\"\r\n" );
        data.append ( "Content-Type: image/jpeg\r\n\r\n" );
    }

    return data;
}
