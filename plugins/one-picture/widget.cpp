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
#include "widget.h"
#include "ui_widget.h"
#include <QtCore/QDir>
#include <QtWidgets/QFileDialog>
#include <QtGui/QImageWriter>
#include <QtCore/QSettings>
#include <QtWidgets/QColorDialog>
#include <QtGui/QColor>
#include "one-picture.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    color = new QColor(Qt::black);
    loadState();
    updateImage();
    // set color of color button
    QPixmap pixmap(32,32);
    pixmap.fill(*color);
    ui->colorPushButton->setIcon(QIcon(pixmap));
}

Widget::~Widget()
{
    saveState();
    delete color;
    delete ui;
}

void Widget::loadState(){
    QSettings settings(QCoreApplication::organizationName(),
            QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("OnePicture");
    ui->widthSpinBox->setValue(settings.value("Width").toInt());
    ui->heightSpinBox->setValue(settings.value("Height").toInt());
    ui->colSpinBox->setValue(settings.value("Cols").toInt());
    ui->rowSpinBox->setValue(settings.value("Rows").toInt());
    ui->borderSpinBox->setValue(settings.value("Border").toInt());
    ui->folderLineEdit->setText(settings.value("SaveTo").toString());
    color->setRed(settings.value("ColorR").toInt());
    color->setGreen(settings.value("ColorG").toInt());
    color->setBlue(settings.value("ColorB").toInt());
}

void Widget::saveState(){
    QSettings settings(QCoreApplication::organizationName(),
            QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("OnePicture");
    settings.setValue("Width", ui->widthSpinBox->value());
    settings.setValue("Height", ui->heightSpinBox->value());
    settings.setValue("Cols", ui->colSpinBox->value());
    settings.setValue("Rows", ui->rowSpinBox->value());
    settings.setValue("Border", ui->borderSpinBox->value());
    settings.setValue("SaveTo", ui->folderLineEdit->text());
    int r, g, b;
    color->getRgb(&r, &g, &b);
    settings.setValue("ColorR", r);
    settings.setValue("ColorG", g);
    settings.setValue("ColorB", b);
}

void Widget::on_selectDestinationPushButton_clicked()
{
    QString folder = ui->folderLineEdit->text();
    folder = QFileDialog::getExistingDirectory(this, tr("Please select directory where images will saved to."), folder);
    if(!folder.isEmpty() && QDir(folder).exists()){
        ui->folderLineEdit->setText(folder);
        ui->folderLineEdit->setToolTip(folder);
    }
}

void Widget::on_colorPushButton_clicked()
{
    QColor c = QColorDialog::getColor(*color, this);
    delete this->color;
    this->color = new QColor(c);
    QPixmap pixmap(32,32);
    pixmap.fill(c);
    ui->colorPushButton->setIcon(QIcon(pixmap));
    updateImage();
}

void Widget::updateImage(){
    int row = ui->rowSpinBox->value();
    int col = ui->colSpinBox->value();
    int border = ui->borderSpinBox->value();
    QList<QImage*> images;
    for(int i = 0; i< row*col; i++){
        QImage* img = new QImage(1,1+i%2, QImage::Format_ARGB32);
        img->fill(Qt::green);
        images.append(img);
    }
    QImage img(100,100, QImage::Format_ARGB32);
    img.fill(this->color->toRgb());
    QImage image = OnePicture::createImage( img, row, col, border, images);
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
}

void Widget::on_colSpinBox_valueChanged(int arg1)
{
    updateImage();
}

void Widget::on_rowSpinBox_valueChanged(int arg1)
{
    updateImage();
}

void Widget::on_borderSpinBox_valueChanged(int arg1)
{
    updateImage();
}

void Widget::updateImage(QImage * image){
    ui->imageLabel->setPixmap(QPixmap::fromImage(image->scaled(100,100)));
}

int Widget::getW(){
    return ui->widthSpinBox->value();
}

int Widget::getH(){
    return ui->heightSpinBox->value();
}

int Widget::getRow(){
    return ui->rowSpinBox->value();
}

int Widget::getCol(){
    return ui->colSpinBox->value();
}

QString Widget::getDir(){
    QDir dir(ui->folderLineEdit->text());
    if(dir.exists()){
        return dir.absolutePath();
    }else{
        return QDir::homePath();
    }
}
