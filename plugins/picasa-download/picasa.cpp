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

#include "picasa.h"
#include "message.h"
#include <QtCore/QBuffer>
#include <QtCore/QEventLoop>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QCryptographicHash>
#include <QtNetwork/QSslConfiguration>
#include <QtNetwork/QSslSocket>


Picasa::Picasa(QObject *parent) :
    QObject(parent),
    client_id("XXX"),
    client_secret("XXX"),
    redirect_uri("urn:ietf:wg:oauth:2.0:oob")
{
}

Picasa::~Picasa(){
}

QJsonDocument Picasa::getJsonDocument(QUrl url){
    QNetworkRequest request(url);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    // TODO: install ssl certificate maybe solved in qt 5.1
    QSslConfiguration sslConfig = request.sslConfiguration();
    QList<QSslCertificate> certs = QSslCertificate::fromPath(":/plugins/picasa-download/picasacrt");
    sslConfig.setCaCertificates(certs);
    request.setSslConfiguration(sslConfig);
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QByteArray rep = reply->readAll();
    return QJsonDocument().fromJson(rep);
}

QString Picasa::getUsernameById(QString userid){
    QString username;
    if(userid.isEmpty())
        userid = "default";
    QUrl url = QUrl("https://picasaweb.google.com/data/feed/api/user/" + userid
                    + "?kind=photo&alt=json&access_token="+this->access_token);

    QJsonDocument document = getJsonDocument(url);
    QJsonObject feed = document.object().take("feed").toObject();
    username = feed.take("gphoto$nickname").toObject().take("$t").toString();
    if(userid == "default"){
        this->currentUserId = feed.take("gphoto$user").toObject().take("$t").toString();
        this->currentUser = username;
    }

    return username;
}

QList<Photo> Picasa::getPhotosByAlbum(Album *album){
    QList<Photo> photos;
    if(album->getId().isEmpty() || album->getOwnerId().isEmpty())
        return photos;
    QUrl url = QUrl("https://picasaweb.google.com/data/feed/api/user/" + album->getOwnerId()
                    + "/albumid/" + album->getId() + "?alt=json&access_token="+this->access_token);
    QJsonDocument document = getJsonDocument(url);
    QJsonObject feed = document.object().take("feed").toObject();
    QJsonArray array = feed.take("entry").toArray();

    foreach(QJsonValue photo_, array){
        Photo photo(photo_.toObject());
        photo.setAlbum(album->getTitle());
        photos.append(photo);
    }
    return photos;
}

QList<Album> Picasa::getAlbumsByUserId(QString userid){
    if(userid.isEmpty())
        userid = "default";
    QUrl url = QUrl("https://picasaweb.google.com/data/feed/api/user/" + userid
                    + "?alt=json&access_token="+this->access_token);

    QJsonDocument document = getJsonDocument(url);
    QJsonObject feed = document.object().take("feed").toObject();
    QJsonArray array = feed.take("entry").toArray();
    QList<Album> albums;
    foreach(QJsonValue album_, array){
        Album album(album_.toObject());
        albums.append(album);
    }
    return albums;
}


void Picasa::genToken(){
    QUrl urlTmp("https://accounts.google.com/o/oauth2/token");

    QByteArray params;
    params.append("code=" + this->auth_code.toLocal8Bit().toPercentEncoding());
    params.append("&client_id="+ this->client_id.toLocal8Bit().toPercentEncoding());
    params.append("&client_secret="+this->client_secret.toLocal8Bit().toPercentEncoding());
    params.append("&redirect_uri="+ this->redirect_uri.toLocal8Bit().toPercentEncoding());
    params.append("&grant_type=authorization_code");

    QNetworkRequest request;
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    // TODO: install ssl certificate maybe solved in qt 5.1
    QSslConfiguration sslConfig = request.sslConfiguration();
    QList<QSslCertificate> certs = QSslCertificate::fromPath(":/plugins/picasa-download/googlecrt");
    sslConfig.setCaCertificates(certs);
    request.setSslConfiguration(sslConfig);
    request.setUrl(urlTmp);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::UserAgentHeader, "Reihenaufnahme");
    request.setRawHeader ( "Host" , "accounts.google.com" );

    QNetworkAccessManager manager(this);
    QNetworkReply *reply = manager.post(request, params);
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray reply_ = reply->readAll();
    QJsonDocument doc = QJsonDocument().fromJson(reply_);
    if(doc.object().take("error").toString().isEmpty()){
        this->access_token = doc.object().take("access_token").toString();
        this->token_type = doc.object().take("token_type").toString();
        this->refresh_token = doc.object().take("refresh_token").toString();
        this->currentUser = getUsernameById("");
    }
}

QString Picasa::getToken(){
    return this->access_token;
}

QString Picasa::getCurrentUser(){
    return this->currentUser;
}

QString Picasa::getAuthUrl(QString perms){
    QString url("https://accounts.google.com/o/oauth2/auth?");
    url.append("client_id=" + client_id);
    url.append("&redirect_uri=" + redirect_uri);
    url.append("&response_type=code");
    url.append("&scope=https%3A%2F%2Fpicasaweb.google.com%2Fdata%2F");

    return url;
}

void Picasa::setAuthCode(QString code){
    this->auth_code = code;
}

void Picasa::uploadImage(QByteArray *image, QString name){

    QString urlTmp("https://picasaweb.google.com");
    urlTmp.append("/data/feed/api/user/default/albumid/default");

    QNetworkRequest uploadRequest;
    uploadRequest.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    // TODO: install ssl certificate maybe solved in qt 5.1
    QSslConfiguration sslConfig = uploadRequest.sslConfiguration();
    QList<QSslCertificate> certs = QSslCertificate::fromPath(":/plugins/picasa-download/picasacrt");
    sslConfig.setCaCertificates(certs);
    uploadRequest.setSslConfiguration(sslConfig);
    uploadRequest.setUrl(urlTmp);
    uploadRequest.setHeader(QNetworkRequest::ContentTypeHeader, "image/jpeg");
    QByteArray auth = "Bearer "+this->access_token.toLocal8Bit();
    uploadRequest.setRawHeader("Authorization", auth);

    uploadRequest.setRawHeader("GData-Version", "2");
    uploadRequest.setRawHeader("Content-Length", QString::number(image->size()).toLatin1());
    uploadRequest.setRawHeader("Slug", name.append(".jpg").toLatin1());

    QNetworkAccessManager manager(this);
    QNetworkReply *reply = manager.post ( uploadRequest , *image );
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

}
