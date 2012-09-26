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
#include "../flickr-download/logindialog.h"

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
    settings.beginGroup("FlickrUpload");
    ui->exifCheckBox->setChecked(settings.value("Exif", false).toBool());
    ui->friendsCheckBox->setChecked(settings.value("Friends", false).toBool());
}

void Widget::saveState(){
    QSettings settings(QCoreApplication::organizationName(),
            QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("FlickrUpload");
    settings.setValue("Exif", ui->exifCheckBox->isChecked());
    settings.setValue("Friends", ui->friendsCheckBox->isChecked());
}

void Widget::updatePixmap(QImage *image){
    ui->uploadingImageLabel->setPixmap(QPixmap().fromImage(*image).scaled(256,256));
}

Flickr *Widget::getFlickr(){
    return &this->flickr;
}

bool Widget::isFriendsVisible(){
    return ui->friendsCheckBox->isChecked();
}

QString Widget::getDescription(){
    return ui->descriptionLineEdit->text();
}

bool Widget::isExif(){
    return ui->exifCheckBox->isChecked();
}

void Widget::on_loginButton_clicked()
{
    LoginDialog loginDialog;
    loginDialog.setUrl(flickr.getAuthUrl("write"));
    if(loginDialog.exec() == 1){
        flickr.genToken();
        ui->currentUserLabel->setText(flickr.getCurrentUser());
    }
}
