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

#ifndef BLUR_H
#define BLUR_H

#include <QtPlugin>
#include <QObject>
#include <QIcon>
#include "plugins/editplugin.h"
#include "widget.h"

class Blur : public EditPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "reihenaufnahme.blur" FILE "blur.json")
    Q_INTERFACES(EditPlugin)

public:
    Blur();
    ~Blur();
    QString getName();
    QString getTitle();
    QString getVersion();
    QString getAuthor();
    QString getDescription();
    QIcon getIcon();
    QWidget *getWidget();

    void edit(Image *image);

    static QImage blurred(QImage& image, const QRect& rect, int radius, bool alphaOnly = false);

private:
    Widget *widget;
};

#endif // BLUR_H
