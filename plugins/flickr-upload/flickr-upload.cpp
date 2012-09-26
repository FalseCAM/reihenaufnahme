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

#include "flickr-upload.h"
#include <QtWidgets/QProxyStyle>
#include <QtCore/QDir>
#include <QtCore/QBuffer>

FlickrUpload::FlickrUpload()
{
    this->widget = 0;
}

FlickrUpload::~FlickrUpload()
{
}

QString FlickrUpload::getName(){
    return QString("flickr-upload");
}

QString FlickrUpload::getTitle(){
    return QString(tr("Flickr Upload"));
}

QString FlickrUpload::getVersion(){
    return QString("1.0");
}

QString FlickrUpload::getAuthor(){
    return QString("FalseCAM");
}

QString FlickrUpload::getDescription(){
    return QString(tr("Plugin to upload images to flickr."));
}

QIcon FlickrUpload::getIcon(){
    return QIcon(":/plugins/flickr-upload/flickr");
}

QWidget *FlickrUpload::getWidget(){
    if(!widget){
        widget = new Widget();
    }
    return widget;
}

void FlickrUpload::out(Image *image){
    getWidget();
    Flickr *flickr = widget->getFlickr();
    if(!flickr->getToken().isEmpty()){
        if(!widget->isHidden())
            widget->updatePixmap(image->getImage());
        // save file into bytearray
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        image->getImage()->save(&buffer, "JPG");
        if(widget->isExif())
            saveExifData(image->getExifData(), &ba);

        flickr->uploadImage(&ba, image->getName(),widget->getDescription(), widget->isFriendsVisible());
    }
}

// Saves Exifdata to given file
void FlickrUpload::saveExifData(Exiv2::ExifData *exifData, QByteArray *image){
    try {
        Exiv2::Image::AutoPtr destImage = Exiv2::ImageFactory::open(
                    (Exiv2::byte*)image->constData(), (long)image->size());
        destImage->setExifData(*exifData);
        destImage->writeMetadata();
        // get updated image data
        Exiv2::BasicIo&  rawio = destImage->io();
        Exiv2::DataBuf  dbuf = rawio.read( rawio.size() );
        image->clear();
        image->append(QByteArray::fromRawData((char*)dbuf.pData_, dbuf.size_));
    } catch (Exiv2::Error& e) {
        qCritical("[SaveFile] %s", e.what());
    }
}

void FlickrUpload::finnish(){
}
