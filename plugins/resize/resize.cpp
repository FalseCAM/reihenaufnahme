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

#include "resize.h"
#include "widget.h"

Resize::Resize()
{
    widget = 0;
}

Resize::~Resize()
{
    if(this->widget)
        delete this->widget;
}

QString Resize::getName(){
    return QString("resize");
}

QString Resize::getTitle(){
    return QString(tr("Resize"));
}

QString Resize::getVersion(){
    return QString("0.2");
}

QString Resize::getAuthor(){
    return QString("FalseCAM");
}

QString Resize::getDescription(){
    return QString(tr("Plugin to resize images"));
}

QIcon Resize::getIcon(){
    return QIcon(":/plugins/resize/resize");
}

QWidget *Resize::getWidget(){
    if(!this->widget){
        this->widget = new Widget();
    }
    return this->widget;
}

void Resize::edit(Image *image){
    // scale image by percentage
    if (widget->percentChange()) {
        image->setImage(
                new QImage(
                        image->getImage()->scaled(
                                image->getImage()->width()
                                        * widget->percentX()
                                        / 100,
                                image->getImage()->height()
                                        * widget->percentY()
                                        / 100, Qt::IgnoreAspectRatio)));
    } else if (widget->pixelChange()) {
        image->setImage(
                new QImage(
                        image->getImage()->scaled(
                                widget->pixelX(),
                                widget->pixelY(),
                                Qt::IgnoreAspectRatio)));
    } else {
    }

}
