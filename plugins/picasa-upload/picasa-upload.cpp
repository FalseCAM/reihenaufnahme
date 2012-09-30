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

#include "picasa-upload.h"
#include <QtWidgets/QProxyStyle>
#include <QtCore/QDir>
#include <QtCore/QBuffer>

PicasaUpload::PicasaUpload()
{
    this->widget = 0;
}

PicasaUpload::~PicasaUpload()
{
}

QString PicasaUpload::getName(){
    return QString("picasa-upload");
}

QString PicasaUpload::getTitle(){
    return QString(tr("Picasa Upload"));
}

QString PicasaUpload::getVersion(){
    return QString("1.0");
}

QString PicasaUpload::getAuthor(){
    return QString("FalseCAM");
}

QString PicasaUpload::getDescription(){
    return QString(tr("Plugin to upload images to google picasa."));
}

QIcon PicasaUpload::getIcon(){
    return QIcon(":/plugins/picasa-upload/picasa");
}

QWidget *PicasaUpload::getWidget(){
    if(!widget){
        widget = new Widget();
    }
    return widget;
}

void PicasaUpload::out(Image *image){
    getWidget();
    Picasa *picasa = widget->getPicasa();
    if(!picasa->getToken().isEmpty()){
        if(!widget->isHidden())
            widget->updatePixmap(image->getImage());
        // save file into bytearray
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        image->getImage()->save(&buffer, "JPG");
        if(widget->isExif())
            saveExifData(image->getExifData(), &ba);

        picasa->uploadImage(&ba, image->getName());
    }
}

// Saves Exifdata to given file
void PicasaUpload::saveExifData(Exiv2::ExifData *exifData, QByteArray *image){
    if(exifData == 0) return;
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

void PicasaUpload::finnish(){
}
