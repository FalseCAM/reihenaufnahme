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

#include "image.h"
#include <QtCore/QDateTime>
#include <QtWidgets/QWidget>
#include <QtGui/QFont>
#include <QtGui/QColor>
#include <QtGui/QPixmap>
#include <QtWidgets/QGraphicsScene>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void addOverlay(QImage *image);
    void addOverlay(Image *image);
    bool isOverlay();

private:
    Ui::Widget *ui;

    void loadState();
    void saveState();
    void addOverlay(QImage *image, QString overlay);
    QDateTime getDateTime(QString exifDateTime);
    QString getExifKey(QString key, Exiv2::ExifData *exifData);

    QFont *font;
    QColor *color;
    QPixmap *pixmap;
    QPixmap *scenePixmap;
    QGraphicsScene *scene;
    QImage *previewImage;

private slots:
    void setFont();
    void setColor();
    void makePreview();

    void on_exifDateComboBox_currentIndexChanged(const QString &arg1);
};

#endif // WIDGET_H
