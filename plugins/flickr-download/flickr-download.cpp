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

#include "flickr-download.h"
#include "widget.h"
#include <QtWidgets/QProxyStyle>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QEventLoop>
#include <QtNetwork/QNetworkReply>

FlickrDownload::FlickrDownload()
{
    this->widget = 0;
    has_next = false;
	this->position = 0;
    manager = new QNetworkAccessManager(this);
}

FlickrDownload::~FlickrDownload()
{
}

QString FlickrDownload::getName(){
    return QString("flickr-download");
}

QString FlickrDownload::getTitle(){
    return QString(tr("Flickr Download"));
}

QString FlickrDownload::getVersion(){
    return QString("1.0");
}

QString FlickrDownload::getAuthor(){
    return QString("FalseCAM");
}

QString FlickrDownload::getDescription(){
    return QString(tr("Plugin to load images from flickr."));
}

QIcon FlickrDownload::getIcon(){
    return QIcon(":/plugins/flickr-download/flickr");
}

QWidget *FlickrDownload::getWidget(){
    if(!widget){
        widget = new Widget();
    }
    return widget;
}

void FlickrDownload::init(){
    this->photos = widget->getPhotos();
    this->position = 0;

    if(!(position >= photos.size())){
        has_next = true;
    } else {
        has_next = false;
    }
}

bool FlickrDownload::hasNext(){
    return has_next;
}

Image *FlickrDownload::next(){
    if(has_next){
        Photo photo = photos.at(position);
        QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(photo.getUrl(widget->getSize()))));
        QEventLoop loop;
        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        QByteArray array = reply->readAll();
        QImage *image = new QImage();
        image->loadFromData(array);
        QString album;
        if(photo.getOwner().isEmpty()){
            album = "flickr";
        } else {
            album = photo.getOwner();
        }
        QString name;
        if(widget->isNameId()){
            name = photo.getId();
        }else if(widget->isNameTitle()){
            name = photo.getTitle();
        }else{
            name = photo.getId() + "_" + photo.getTitle();
        }
        position++;
        if(position >= this->photos.size()){
            has_next = false;
        }
        Image *img = new Image(image, album, name, position - 1);
        //img->setExifData(readExifData(file));
        return img;
    }

    return 0;
}

int FlickrDownload::getProgress(){
    int progress = 0;
    if(photos.size()>0)
        progress = 100 * position / photos.size();
    return progress;
}

QString FlickrDownload::getName(QString file){
    QString name;
    name = QFileInfo(file).baseName();
    return name;
}

QString FlickrDownload::getFolder(QString file){
    QString folder;
    folder = QDir(QFileInfo(file).absoluteDir()).dirName();
    return folder;
}

// Reads metadata from given file
Exiv2::ExifData *FlickrDownload::readExifData(QString file){
    try{
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(
                    file.toStdString().c_str());
        image->readMetadata();
        Exiv2::ExifData *data = new Exiv2::ExifData();
        *data = image->exifData();
        return data;
    } catch (Exiv2::Error& e) {
        qCritical("[Filechooser] %s", e.what());
        return 0;
    }
}
