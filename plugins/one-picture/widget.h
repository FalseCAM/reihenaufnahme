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

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    int getW();
    int getH();
    int getRow();
    int getCol();
    void updateImage(QImage * image);
    QString getDir();
    
private slots:

    void on_selectDestinationPushButton_clicked();

    void on_colorPushButton_clicked();

    void on_colSpinBox_valueChanged(int arg1);

    void on_rowSpinBox_valueChanged(int arg1);


    void on_borderSpinBox_valueChanged(int arg1);

private:
    Ui::Widget *ui;
    void loadState();
    void saveState();
    void updateImage();
    QColor *color;
};

#endif // WIDGET_H
