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

#include "overlay-text.h"
#include "widget.h"

OverlayText::OverlayText()
{
    widget = 0;
}

OverlayText::~OverlayText()
{
    if(this->widget)
        delete this->widget;
}

QString OverlayText::getName(){
    return QString("overlay-text");
}

QString OverlayText::getTitle(){
    return QString(tr("Overlay Text"));
}

QString OverlayText::getVersion(){
    return QString("0.1");
}

QString OverlayText::getAuthor(){
    return QString("FalseCAM");
}

QString OverlayText::getDescription(){
    return QString(tr("Plugin to overlay-text images"));
}

QIcon OverlayText::getIcon(){
    return QIcon(":/plugins/overlay-text/overlay-text");
}

QWidget *OverlayText::getWidget(){
    if(!this->widget){
        this->widget = new Widget();
    }
    return this->widget;
}

void OverlayText::edit(Image *image){
    if(widget->isOverlay())
        widget->addOverlay(image);
}
