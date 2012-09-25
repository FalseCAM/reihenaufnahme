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

#include "rename.h"
#include "widget.h"

Rename::Rename()
{
    widget = 0;
}

Rename::~Rename()
{
    if(this->widget)
        delete this->widget;
}

QString Rename::getName(){
    return QString("rename");
}

QString Rename::getTitle(){
    return QString(tr("Rename"));
}

QString Rename::getVersion(){
    return QString("0.1");
}

QString Rename::getAuthor(){
    return QString("FalseCAM");
}

QString Rename::getDescription(){
    return QString(tr("Plugin to rename images"));
}

QIcon Rename::getIcon(){
    return QIcon(":/plugins/rename/rename");
}

QWidget *Rename::getWidget(){
    if(!this->widget){
        this->widget = new Widget();
    }
    return this->widget;
}

void Rename::edit(Image *image){

    QString fileName = image->getName();
    if(widget->isRename() && widget->isNewName()){
        fileName = widget->getNewName();
    }
    if(widget->isRename()){
        if(widget->isPrependExifDate()){
            fileName.prepend(widget->getDateTime(getExifKey("Exif.Photo.DateTimeOriginal" ,image->getExifData()))
                             .toString(widget->getDateFormat()));
        }
        if(widget->isAppendExifDate()){
            fileName.append(widget->getDateTime(getExifKey("Exif.Photo.DateTimeOriginal" ,image->getExifData()))
                            .toString(widget->getDateFormat()));
        }
    }
    if(widget->isRename() && !(widget->getPrefix().isEmpty() && widget->getSuffix().isEmpty())){
        fileName.prepend(widget->getPrefix());
        fileName.append(widget->getSuffix());
    }
    if(widget->isRename()){
        if(widget->isCounter())
            fileName.append(QString("%1").arg(widget->getCounterStart()+image->getIndex(), widget->getCounterDecimals(), 10, QChar('0')) );
    }
    image->setName(fileName);

}

QString Rename::getExifKey(QString key, Exiv2::ExifData *exifData){
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
