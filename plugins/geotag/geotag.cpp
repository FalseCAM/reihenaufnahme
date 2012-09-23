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

#include "geotag.h"
#include "widget.h"

Geotag::Geotag()
{
    widget = 0;
}

Geotag::~Geotag()
{
    if(this->widget)
        delete this->widget;
}

QString Geotag::getName(){
    return QString("geotag");
}

QString Geotag::getTitle(){
    return QString(tr("Geotag"));
}

QString Geotag::getVersion(){
    return QString("0.1");
}

QString Geotag::getAuthor(){
    return QString("FalseCAM");
}

QString Geotag::getDescription(){
    return QString(tr("Plugin to change geotag info in exif data."));
}

QIcon Geotag::getIcon(){
    return QIcon(":/plugins/geotag/geotag");
}

QWidget *Geotag::getWidget(){
    if(!this->widget){
        this->widget = new Widget();
    }
    return this->widget;
}

void Geotag::edit(Image *image){
    getWidget();
    if(widget->isGeotagChange()){
        Exiv2::ExifData *exifData = image->getExifData();
        char scratchBuf[100];
        long int deg, min;
        qreal lat = widget->getLatitude();
        qreal lng = widget->getLongitude();



        if(lng < 0)
            setExifKey("Exif.GPSInfo.GPSLongitudeRef", "W", exifData);
        else setExifKey("Exif.GPSInfo.GPSLongitudeRef", "E", exifData);

        if(lat > 0)
            setExifKey("Exif.GPSInfo.GPSLatitudeRef", "N", exifData);
        else setExifKey("Exif.GPSInfo.GPSLatitudeRef", "S", exifData);

        deg = (int)floor(fabs(lng)); // Slice off after decimal.
        min = (int)floor((fabs(lng) - floor(fabs(lng))) * 60000000);
        _snprintf(scratchBuf, 100, "%ld/1 %ld/1000000 0/1", deg, min);
        setExifKeyRational("Exif.GPSInfo.GPSLongitude", QString(scratchBuf), exifData);

        deg = (int)floor(fabs(lat)); // Slice off after decimal.
        min = (int)floor((fabs(lat) - floor(fabs(lat))) * 60000000);
        _snprintf(scratchBuf, 100, "%ld/1 %ld/1000000 0/1", deg, min);
        setExifKeyRational("Exif.GPSInfo.GPSLatitude", QString(scratchBuf), exifData);
    }
}

void Geotag::setExifKey(QString key, QString value, Exiv2::ExifData *exifData){
    try {
        // Create a ASCII string value (note the use of create)
        Exiv2::Value::AutoPtr v = Exiv2::Value::create(Exiv2::asciiString);
        // Set the value to a string
        v->read(qPrintable(value));
        // Add the value together with its key to the Exif data container
        Exiv2::ExifKey key_(qPrintable(key));
        exifData->add(key_, v.get());
    } catch (Exiv2::Error& e) {
        qCritical("[EisImage] %s", e.what());
    }
}

void Geotag::setExifKeyRational(QString key, QString value, Exiv2::ExifData *exifData){
    try {
        // Create a ASCII string value (note the use of create)
        Exiv2::URationalValue::AutoPtr v(new Exiv2::URationalValue);
        // Set the value to a string
        v->read(qPrintable(value));
        // Add the value together with its key to the Exif data container
        Exiv2::ExifKey key_(qPrintable(key));
        exifData->add(key_, v.get());
    } catch (Exiv2::Error& e) {
        qCritical("[Geotag] %s", e.what());
    }
}
