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
    if(document.isObject()){qDebug("%s", qPrintable(document.toJson()));
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

QString Flickr::getAuthUrl(){
    genFrob();
    QMap<QString, QString> parameter;
    parameter.insert("api_key", api_key);
    parameter.insert("frob", getFrob());
    parameter.insert("perms", "read");
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
