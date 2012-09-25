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
#include "color.h"
#include <QtCore/QSettings>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    loadState();
    updateImage();
}

Widget::~Widget()
{
    saveState();
    delete ui;
}

void Widget::loadState(){
    QSettings settings(QCoreApplication::organizationName(),
            QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("Color");

    ui->grayscaleCheckBox->setChecked(settings.value("GrayScale", false).toBool());
    ui->invertCheckBox->setChecked(settings.value("Invert", false).toBool());
    ui->swapCheckBox->setChecked(settings.value("Swap", false).toBool());
    ui->sepiaCheckBox->setChecked(settings.value("Sepia", false).toBool());
}

void Widget::saveState(){
    QSettings settings(QCoreApplication::organizationName(),
            QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("Color");

    settings.setValue("GrayScale", ui->grayscaleCheckBox->isChecked());
    settings.setValue("Invert", ui->invertCheckBox->isChecked());
    settings.setValue("Swap", ui->swapCheckBox->isChecked());
    settings.setValue("Sepia", ui->sepiaCheckBox->isChecked());
}



void Widget::updateImage(){
    QImage image(":/reihenaufnahme/r6");

    if(ui->grayscaleCheckBox->isChecked()){
        Color::grayscale(&image);
    }
    if(ui->invertCheckBox->isChecked()){
        image.invertPixels();
    }
    if(ui->swapCheckBox->isChecked()){
        image = image.rgbSwapped();
    }
    if(ui->sepiaCheckBox->isChecked()){
        Color::sepia(&image);
    }
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
}

void Widget::on_grayscaleCheckBox_toggled(bool checked)
{
    updateImage();
}

void Widget::on_invertCheckBox_toggled(bool checked)
{
    updateImage();
}

void Widget::on_swapCheckBox_toggled(bool checked)
{
    updateImage();
}

void Widget::on_sepiaCheckBox_toggled(bool checked)
{
    updateImage();
}

bool Widget::isGrayscale(){
    return ui->grayscaleCheckBox->isChecked();
}

bool Widget::isSwap(){
    return ui->swapCheckBox->isChecked();
}

bool Widget::isInvert(){
    return ui->invertCheckBox->isChecked();
}

bool Widget::isSepia(){
    return ui->sepiaCheckBox->isChecked();
}
