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

#ifndef ALBUMWIDGET_H
#define ALBUMWIDGET_H

#include <QtWidgets/QWidget>
#include "album.h"

namespace Ui {
class AlbumWidget;
}

class AlbumWidget : public QWidget
{
    Q_OBJECT
    
public:
    AlbumWidget(QWidget *parent = 0);
    AlbumWidget(Album *album);
    ~AlbumWidget();
    Album *getAlbum();
    bool isChecked();
private:
    Ui::AlbumWidget *ui;
    Album *album;

    QPixmap getPixmap(QString url);
};

#endif // ALBUMWIDGET_H
