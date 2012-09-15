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

#ifndef IMAGE_H
#define IMAGE_H

#include <Qt/qobject.h>
#include <Qt/qimage.h>
#include <exiv2/exiv2.hpp>

class Image : public QObject
{
    Q_OBJECT
public:
    explicit Image(QImage *image, QString album, QString name, int index);

    QImage *getImage();
    QString getAlbum();
    QString getName();
    int getIndex();
    Exiv2::ExifData *getExifData();

    void setImage(QImage *image);
    void setAlbum(QString album);
    void setName(QString name);
    void setIndex(int index);
    void setExifData(Exiv2::ExifData *data);
    
signals:
    
public slots:

private:
    QImage *img;
    QString name;
    QString album;
    int index;
    Exiv2::ExifData *exifData;
    
};

#endif // IMAGE_H
