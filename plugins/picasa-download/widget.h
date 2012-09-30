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

#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
#include "photo.h"
#include "picasa.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QList<Photo> getPhotos();
    QString getSize();
    bool isNameId();
    bool isNameTitle();
    
private slots:

    void on_loginButton_clicked();

    void on_activeButton_clicked();

    void on_loadUserButton_clicked();

private:
    Ui::Widget *ui;
    Picasa picasa;
    QString lastFolder;
    void loadState();
    void saveState();
    void clearList();
};

#endif // WIDGET_H
