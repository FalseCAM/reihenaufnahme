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

#ifndef RENAME_H
#define RENAME_H

#include <QtPlugin>
#include <QObject>
#include <QIcon>
#include "plugins/editplugin.h"
#include "widget.h"


class Rename : public EditPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "reihenaufnahme.rename" FILE "rename.json")
    Q_INTERFACES(EditPlugin)

public:
    Rename();
    ~Rename();
    QString getName();
    QString getTitle();
    QString getVersion();
    QString getAuthor();
    QString getDescription();
    QIcon getIcon();
    QWidget *getWidget();

    void edit(Image *image);

private:
    Widget *widget;
};

#endif // RESNAME_H
