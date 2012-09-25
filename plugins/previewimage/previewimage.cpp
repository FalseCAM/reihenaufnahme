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

#include "previewimage.h"
#include "widget.h"
#include <QtCore/QBuffer>

Previewimage::Previewimage()
{
    widget = 0;
}

Previewimage::~Previewimage()
{
    if(this->widget)
        delete this->widget;
}

QString Previewimage::getName(){
    return QString("previewimage");
}

QString Previewimage::getTitle(){
    return QString(tr("Previewimage"));
}

QString Previewimage::getVersion(){
    return QString("0.1");
}

QString Previewimage::getAuthor(){
    return QString("FalseCAM");
}

QString Previewimage::getDescription(){
    return QString(tr("Plugin to update previewimage in exif data."));
}

QIcon Previewimage::getIcon(){
    return QIcon(":/plugins/previewimage/previewimage");
}

QWidget *Previewimage::getWidget(){
    if(!this->widget){
        this->widget = new Widget();
    }
    return this->widget;
}

void Previewimage::edit(Image *image){
    getWidget(); // avoid nullpointer exception
    if(widget->isUpdate()){

        QImage thumbnail = image->getImage()->scaled(160, 120);
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        thumbnail.save(&buffer, "JPG");
        if(image->getExifData() == 0) image->setExifData(new Exiv2::ExifData());
        Exiv2::ExifThumb exifThumb(*image->getExifData());
        exifThumb.erase();
        exifThumb.setJpegThumbnail((Exiv2::byte*)ba.constData() ,ba.size());
    } else if (widget->isRemove()){
        if(image->getExifData() == 0) image->setExifData(new Exiv2::ExifData());
        Exiv2::ExifThumb exifThumb(*image->getExifData());
        exifThumb.erase();
    } else {

    }
}

QString Previewimage::getExifKey(QString key, Exiv2::ExifData *exifData){
    // returns string represented by exif key
    if(exifData == 0) return QString();
    QString ret;
    try {
        Exiv2::ExifData::iterator pos = exifData->findKey(
                    Exiv2::ExifKey(qPrintable(key)));
        if (pos == exifData->end()) return QString();
        else ret = QString().fromStdString(pos->value().toString());
    } catch (Exiv2::Error& e) {
        qCritical("[Rename] %s", e.what());
    }
    return ret;
}
