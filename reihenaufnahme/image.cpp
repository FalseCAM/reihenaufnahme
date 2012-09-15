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

#include "image.h"

Image::Image(QImage *image, QString album, QString name, int index){
    this->img = 0;
    this->exifData = 0;
    setImage(image);
    setAlbum(album);
    setName(name);
    setIndex(index);
}

QImage *Image::getImage(){
    return this->img;
}

QString Image::getAlbum(){
    return this->album;
}

QString Image::getName(){
    return this->name;
}

int Image::getIndex(){
    return this->index;
}

Exiv2::ExifData* Image::getExifData(){
    return this->exifData;
}

void Image::setImage(QImage *image){
    if (this->img != image){
        if (this->img != 0)
            delete this->img;
        this->img = image;
    }
}

void Image::setAlbum(QString album){
    this->album = album;
}

void Image::setName(QString name){
    this->name = name;
}

void Image::setIndex(int index){
    this->index = index;
    if(this->index < 0)
        this->index = 0;
}

void Image::setExifData(Exiv2::ExifData *data){
    if(this->exifData != data){
        if (this->exifData != 0)
            delete this->exifData;
        this->exifData = data;
    }
}
