/*
    EasyImageSizer - Resize

    EasyImageSizer plugin to Resize a QImage

    Copyright (C) 2010  FalseCAM

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COLOR_H
#define COLOR_H

#include <QtPlugin>
#include <QObject>
#include <QIcon>
#include "plugins/editplugin.h"
#include "widget.h"

class Color : public EditPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "reihenaufnahme.color" FILE "color.json")
    Q_INTERFACES(EditPlugin)

public:
    Color();
    ~Color();
    QString getName();
    QString getTitle();
    QString getVersion();
    QString getAuthor();
    QString getDescription();
    QIcon getIcon();
    QWidget *getWidget();

    void edit(Image *image);

    static void grayscale(QImage* image);
    static void sepia(QImage* image);

private:
    Widget *widget;
};

#endif // COLOR_H
