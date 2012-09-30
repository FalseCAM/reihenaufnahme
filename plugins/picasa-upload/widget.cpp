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
#include <QtGui/QDesktopServices>

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
    settings.beginGroup("PicasaUpload");
    ui->exifCheckBox->setChecked(settings.value("Exif", false).toBool());
}

void Widget::saveState(){
    QSettings settings(QCoreApplication::organizationName(),
            QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("PicasaUpload");
    settings.setValue("Exif", ui->exifCheckBox->isChecked());
}

void Widget::updatePixmap(QImage *image){
    ui->uploadingImageLabel->setPixmap(QPixmap().fromImage(*image).scaled(256,256));
}

Picasa *Widget::getPicasa(){
    return &this->picasa;
}

bool Widget::isExif(){
    return ui->exifCheckBox->isChecked();
}

void Widget::on_loginButton_clicked()
{
    QDesktopServices::openUrl(picasa.getAuthUrl("read"));
}

void Widget::on_activeButton_clicked()
{
    picasa.setAuthCode(ui->codeLineEdit->text());
    picasa.genToken();
    if(!picasa.getToken().isEmpty()){
        ui->currentUserLabel->setText(picasa.getCurrentUser());
    }
}
