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

#include "one-picture.h"
#include <QtWidgets/QProxyStyle>
#include <QtCore/QDir>
#include <QtGui/QPainter>

OnePicture::OnePicture()
{
    this->widget = 0;
}

OnePicture::~OnePicture()
{
}

QString OnePicture::getName(){
    return QString("one-picture");
}

QString OnePicture::getTitle(){
    return QString(tr("One Picture"));
}

QString OnePicture::getVersion(){
    return QString("0.1");
}

QString OnePicture::getAuthor(){
    return QString("FalseCAM");
}

QString OnePicture::getDescription(){
    return QString(tr("Plugin to save images into one picture."));
}

QIcon OnePicture::getIcon(){
    return QIcon(":/plugins/one-picture/onepicture");
}

QWidget *OnePicture::getWidget(){
    if(!widget){
        widget = new Widget();
    }
    return widget;
}

void OnePicture::out(Image *image){
    getWidget();
    images.append(image->getImage());
    filename.append(image->getName());
    if(images.size()>= widget->getRow()* widget->getCol()){
        createImage();
    }
}

void OnePicture::finnish(){
    if(images.size()>0){
        createImage();
    }
}

void OnePicture::createImage(){
    int w = widget->getW();
    int h = widget->getH();
    int row = widget->getRow();
    int col = widget->getCol();
    QString filename = widget->getDir() + "/" + this->filename + ".jpg";
    this->filename.clear();
    QList<QImage*> images;
    images.append(this->images);
    this->images.clear();
    QImage image(w, h, QImage::Format_ARGB32);
    image.fill(Qt::black);
    QImage img = createImage(image,row,col, 1, images);
    widget->updateImage(&img);
    img.save(filename);
}

QImage OnePicture::createImage(QImage &background, int row, int col, int border, QList<QImage*> images){
    int w = background.width();
    int h = background.height();
    QImage image(background);
    QPainter painter(&image);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(images.size()> i*col + j){
                QImage * img = images.at(i*col + j);
                int width = w*1/col;
                int height = h*1/row;
                int x = j* width;
                int y = i* height;
                float m = img->width() / (width);
                if(img->height()/m  > height){
                    QImage img_ = img->scaledToHeight(height - border*2);
                    painter.drawImage(x + (width - img_.width())/2 , y + (height - img_.height())/2, img_);
                }else{
                    QImage img_ = img->scaledToWidth(width - border*2);
                    painter.drawImage(x + (width - img_.width())/2 , y + (height - img_.height())/2, img_);
                }
            }
        }
    }
    painter.end();
    return image;
}
