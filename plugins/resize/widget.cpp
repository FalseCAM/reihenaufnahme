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
#include <QSettings>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    loadState();
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
    settings.beginGroup("Resize");

    ui->pixelRadioButton->setChecked(settings.value("PixelUse", false).toBool());
    ui->percentageRadioButton->setChecked(settings.value("PercentUse", false).toBool());
    ui->xPixelSpinBox->setValue(settings.value("PixelX", 1920).toInt());
    ui->yPixelSpinBox->setValue(settings.value("PixelY", 1080).toInt());
    ui->xPercentageSpinBox->setValue(settings.value("PercentX", 100).toInt());
    ui->yPercentageSpinBox->setValue(settings.value("PercentY", 100).toInt());
}

void Widget::saveState(){
    QSettings settings(QCoreApplication::organizationName(),
            QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("Resize");

    settings.setValue("PixelUse", ui->pixelRadioButton->isChecked());
    settings.setValue("PercentUse", ui->percentageRadioButton->isChecked());
    settings.setValue("PixelX", ui->xPixelSpinBox->value());
    settings.setValue("PixelY", ui->yPixelSpinBox->value());
    settings.setValue("PercentX", ui->xPercentageSpinBox->value());
    settings.setValue("PercentY", ui->yPercentageSpinBox->value());
}

bool Widget::percentChange(){
    return ui->percentageRadioButton->isChecked();
}

bool Widget::pixelChange(){
    return ui->pixelRadioButton->isChecked();
}

int Widget::percentX(){
    return ui->xPercentageSpinBox->value();
}

int Widget::percentY(){
    return ui->yPercentageSpinBox->value();
}

int Widget::pixelX(){
    return ui->xPixelSpinBox->value();
}

int Widget::pixelY(){
    return ui->yPixelSpinBox->value();
}

void Widget::on_sizeRatioComboBox_currentIndexChanged(const QString &arg1)
{
    if(ui->percentageRadioButton->isChecked()){
        if (arg1 == "1:1") {
            ui->yPercentageSpinBox->setValue(
                    ui->xPercentageSpinBox->value() * (1.0 / 1));
        } else if (arg1 == "5:4") {
            ui->yPercentageSpinBox->setValue(
                    ui->xPercentageSpinBox->value() * (4.0 / 5));
        } else if (arg1 == "4:3") {
            ui->yPercentageSpinBox->setValue(
                    ui->xPercentageSpinBox->value() * (3.0 / 4));
        } else if (arg1 == "16:9") {
            ui->yPercentageSpinBox->setValue(
                    ui->xPercentageSpinBox->value() * (9.0 / 16));
        }
    } else {
        if (arg1 == "1:1") {
            ui->yPixelSpinBox->setValue(
                    ui->xPixelSpinBox->value() * (1.0 / 1));
        } else if (arg1 == "5:4") {
            ui->yPixelSpinBox->setValue(
                    ui->xPixelSpinBox->value() * (4.0 / 5));
        } else if (arg1 == "4:3") {
            ui->yPixelSpinBox->setValue(
                    ui->xPixelSpinBox->value() * (3.0 / 4));
        } else if (arg1 == "16:9") {
            ui->yPixelSpinBox->setValue(
                    ui->xPixelSpinBox->value() * (9.0 / 16));
        }
    }
}

void Widget::on_pixelComboBox_currentIndexChanged(const QString &arg1)
{
    ui->pixelRadioButton->setChecked(true);
        if (arg1 == "VGA (640x480)") {
            ui->xPixelSpinBox->setValue(640);
            ui->yPixelSpinBox->setValue(480);
        } else if (arg1 == "XGA (1024x768)") {
            ui->xPixelSpinBox->setValue(1024);
            ui->yPixelSpinBox->setValue(768);
        } else if (arg1 == "NTSC (576x486)") {
            ui->xPixelSpinBox->setValue(576);
            ui->yPixelSpinBox->setValue(486);
        } else if (arg1 == "PAL (720x486)") {
            ui->xPixelSpinBox->setValue(720);
            ui->yPixelSpinBox->setValue(486);
        } else if (arg1 == "HD (1920x1080)") {
            ui->xPixelSpinBox->setValue(1920);
            ui->yPixelSpinBox->setValue(1080);
        } else if (arg1 == "Flickr large (768x1024)") {
            ui->xPixelSpinBox->setValue(768);
            ui->yPixelSpinBox->setValue(1024);
        } else if (arg1 == "iPhone landscape (480x320)") {
            ui->xPixelSpinBox->setValue(480);
            ui->yPixelSpinBox->setValue(320);
        } else if (arg1 == "160x160") {
            ui->xPixelSpinBox->setValue(160);
            ui->yPixelSpinBox->setValue(160);
        } else if (arg1 == "HD 720 (1280x720)") {
            ui->xPixelSpinBox->setValue(1280);
            ui->yPixelSpinBox->setValue(720);
        } else if (arg1 == "SVGA (800x600)") {
            ui->xPixelSpinBox->setValue(800);
            ui->yPixelSpinBox->setValue(600);
        } else if (arg1 == "PSP (480x272)") {
            ui->xPixelSpinBox->setValue(480);
            ui->yPixelSpinBox->setValue(272);
        } else if (arg1 == "2K (2048x1080)") {
            ui->xPixelSpinBox->setValue(2048);
            ui->yPixelSpinBox->setValue(1080);
        }
}
