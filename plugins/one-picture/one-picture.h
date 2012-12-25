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

#ifndef ONE_PICTURE_H
#define ONE_PICTURE_H

#include <QtCore/QtPlugin>
#include <QtCore/QObject>
#include <QtGui/QIcon>
#include "widget.h"
#include "plugins/outputplugin.h"


class OnePicture : public OutputPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "reihenaufnahme.one-picture" FILE "one-picture.json")
    Q_INTERFACES(OutputPlugin)

public:
    OnePicture();
    ~OnePicture();
    QString getName();
    QString getTitle();
    QString getVersion();
    QString getAuthor();
    QString getDescription();
    QIcon getIcon();
    QWidget *getWidget();

    void out(Image *image);
    void finnish();

    static QImage createImage(QImage &background, int row, int col, int border, QList<QImage*> images);

private:
    Widget *widget;
    void createImage();
    QList<QImage*> images;
    QString filename;
};

#endif // ONE_PICTURE_H
