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

#include "albumwidget.h"
#include "ui_albumwidget.h"
#include <QtCore/QEventLoop>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QCryptographicHash>
#include <QtNetwork/QSslConfiguration>
#include <QtNetwork/QSslSocket>

AlbumWidget::AlbumWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumWidget)
{
    ui->setupUi(this);
}

AlbumWidget::AlbumWidget(Album *album):
    QWidget(0),
    ui(new Ui::AlbumWidget)
{
    this->album = album;
    ui->setupUi(this);
    ui->titleLabel->setText(album->getTitle() + " (" + album->getNumPhotos() + ")");
    ui->iconLabel->setPixmap(getPixmap(album->getThumbnailUrl()));

}

AlbumWidget::~AlbumWidget()
{
    delete ui;
}

Album *AlbumWidget::getAlbum(){
    return this->album;
}

bool AlbumWidget::isChecked(){
    return ui->checkBox->isChecked();
}

QPixmap AlbumWidget::getPixmap(QString url){
    QByteArray bytes;
    QNetworkRequest request(url);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    QSslConfiguration sslConfig = request.sslConfiguration();
    QList<QSslCertificate> certs = QSslCertificate::fromPath(":/plugins/picasa-download/picasacrt");
    sslConfig.setCaCertificates(certs);
    request.setSslConfiguration(sslConfig);
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    bytes = reply->readAll();
    QImage img;
    img.loadFromData(bytes);
    return QPixmap::fromImage(img.scaledToHeight(32));
}
