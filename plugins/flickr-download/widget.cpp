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
#include "logindialog.h"
#include <QtCore/QSettings>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtWidgets/QFileDialog>
#include <QtGui/QImageReader>
#include <QtCore/QUrl>
#include <QtCore/QMimeData>
#include <QtCore/QMap>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setAcceptDrops(true);
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
    settings.beginGroup("FlickrDownload");

    this->lastFolder = QDir::homePath();
}

void Widget::saveState(){
    QSettings settings(QCoreApplication::organizationName(),
                       QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("FlickrDownload");
}

QList<Photo> Widget::getPhotos(){
    return photos;
}

QString Widget::getSize(){
    QString size = "b";
    if(ui->sizeMidButton->isChecked()){
        size = "z";
    }else if(ui->sizeThumbnailButton->isChecked()){
        size = "t";
    }
    return size;
}

void Widget::on_userNameLineEdit_editingFinished()
{
    if(flickr.getToken().isEmpty()){
        this->photos = flickr.getPublicPhotosByUserId(flickr.getIdByUsername(ui->userNameLineEdit->text()));
    }else{
        this->photos = flickr.getPhotosByUserId(flickr.getIdByUsername(ui->userNameLineEdit->text()));
    }
    ui->photosListWidget->clear();
    foreach(Photo photo, photos){
        ui->photosListWidget->addItem(photo.getTitle());
    }
}

void Widget::on_loginButton_clicked()
{
    LoginDialog loginDialog;
    loginDialog.setUrl(flickr.getAuthUrl());
    if(loginDialog.exec() == 1){
        flickr.genToken();
        ui->currentUserLabel->setText(flickr.getCurrentUser());
    }
}

bool Widget::isNameId(){
    return ui->idRadioButton->isChecked();
}

bool Widget::isNameTitle(){
    return ui->titleRadioButton->isChecked();
}
