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

#include "rename-album.h"
#include "widget.h"

RenameAlbum::RenameAlbum()
{
    widget = 0;
}

RenameAlbum::~RenameAlbum()
{
    if(this->widget)
        delete this->widget;
}

QString RenameAlbum::getName(){
    return QString("rename-album");
}

QString RenameAlbum::getTitle(){
    return QString(tr("Rename Album"));
}

QString RenameAlbum::getVersion(){
    return QString("0.1");
}

QString RenameAlbum::getAuthor(){
    return QString("FalseCAM");
}

QString RenameAlbum::getDescription(){
    return QString(tr("Plugin to rename albums."));
}

QIcon RenameAlbum::getIcon(){
    return QIcon(":/plugins/rename-album/rename-album");
}

QWidget *RenameAlbum::getWidget(){
    if(!this->widget){
        this->widget = new Widget();
    }
    return this->widget;
}

void RenameAlbum::edit(Image *image){

    QString albumName = image->getAlbum();
    if(widget->isRename() && widget->isNewName()){
        albumName = widget->getNewName();
    }
    if(widget->isRename()){
        if(widget->isPrependExifDate()){
            albumName.prepend(widget->getDateTime(getExifKey("Exif.Photo.DateTimeOriginal" ,image->getExifData()))
                             .toString(widget->getDateFormat()));
        }
        if(widget->isAppendExifDate()){
            albumName.append(widget->getDateTime(getExifKey("Exif.Photo.DateTimeOriginal" ,image->getExifData()))
                            .toString(widget->getDateFormat()));
        }
    }
    if(widget->isRename() && !(widget->getPrefix().isEmpty() && widget->getSuffix().isEmpty())){
        albumName.prepend(widget->getPrefix());
        albumName.append(widget->getSuffix());
    }
    image->setAlbum(albumName);
}

QString RenameAlbum::getExifKey(QString key, Exiv2::ExifData *exifData){
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
