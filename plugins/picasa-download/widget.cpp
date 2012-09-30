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
#include "albumwidget.h"
#include <QtCore/QSettings>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtWidgets/QFileDialog>
#include <QtGui/QImageReader>
#include <QtCore/QUrl>
#include <QtCore/QMimeData>
#include <QtCore/QMap>
#include <QtGui/QDesktopServices>

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
    clearList();
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
    QList<Photo> photos;
    for(int i = 0; i < ui->photosListWidget->count(); i++){
        AlbumWidget *awidget = (AlbumWidget*)ui->photosListWidget->itemWidget(
                    ui->photosListWidget->item(i));
        if(awidget->isChecked()){
            photos.append(picasa.getPhotosByAlbum(awidget->getAlbum()));
        }
    }
    return photos;
}

QString Widget::getSize(){
    QString size = "2048";
    if(ui->sizeSmallButton->isChecked()){
        size = "512";
    } else if(ui->sizeMidButton->isChecked()){
        size = "1024";
    }else if(ui->sizeThumbnailButton->isChecked()){
        size = "120";
    }
    return size;
}

void Widget::on_loginButton_clicked()
{
    QDesktopServices::openUrl(picasa.getAuthUrl("read"));
}

bool Widget::isNameId(){
    return ui->idRadioButton->isChecked();
}

bool Widget::isNameTitle(){
    return ui->titleRadioButton->isChecked();
}

void Widget::on_activeButton_clicked()
{
    picasa.setAuthCode(ui->codeLineEdit->text());
    picasa.genToken();
    ui->currentUserLabel->setText(picasa.getCurrentUser());
    on_loadUserButton_clicked();
}

void Widget::on_loadUserButton_clicked()
{
    clearList();
    foreach(Album album, picasa.getAlbumsByUserId(ui->userNameLineEdit->text())){
        AlbumWidget *awidget = new AlbumWidget(new Album(album));
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(40,150));
        ui->photosListWidget->addItem(item);

        ui->photosListWidget->setItemWidget(item, awidget);

    }
}

void Widget::clearList(){
    for(int i = 0; i < ui->photosListWidget->count(); i++){
        AlbumWidget *awidget = (AlbumWidget*)ui->photosListWidget->itemWidget(
                    ui->photosListWidget->item(i));
        delete awidget;
        delete ui->photosListWidget->itemWidget(ui->photosListWidget->item(i));
    }
    ui->photosListWidget->clear();
}
