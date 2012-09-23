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
#include <QtCore/QSettings>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->map = new Map(this);
    ui->mapGrid->addWidget(map);
    connect(ui->gotoButton, SIGNAL(clicked()), this, SLOT(on_gotoButton_clicked()));
    connect(map, SIGNAL(latChanged(qreal)), this, SLOT(latChanged(qreal)));
    connect(map, SIGNAL(lngChanged(qreal)), this, SLOT(lngChanged(qreal)));
    // Zoom Buttons
    connect(ui->zoomInButton, SIGNAL(clicked()), map, SLOT(zoomIn()));
    connect(ui->zoomOutButton, SIGNAL(clicked()), map, SLOT(zoomOut()));
    loadState();
    on_gotoButton_clicked();
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
    settings.beginGroup("Rename");

    ui->latLineEdit->setText(settings.value("latitude", "50.0000").toString());
    ui->lngLineEdit->setText(settings.value("longitude", "8.0000").toString());
}

void Widget::saveState(){
    QSettings settings(QCoreApplication::organizationName(),
                       QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("Rename");

    settings.setValue("latitude", ui->latLineEdit->text());
    settings.setValue("longitude", ui->lngLineEdit->text());
}

bool Widget::isGeotagChange(){
    return ui->geotagCheckBox->isChecked();
}

qreal Widget::getLatitude(){
    return ui->latLineEdit->text().toDouble();
}

qreal Widget::getLongitude(){
    return ui->lngLineEdit->text().toDouble();
}

void Widget::latChanged(qreal lat){
    ui->latLineEdit->setText(QString::number(lat));
}

void Widget::lngChanged(qreal lng){
    ui->lngLineEdit->setText(QString::number(lng));
}

void Widget::on_gotoButton_clicked()
{
    qreal lat = ui->latLineEdit->text().toDouble();
    qreal lng = ui->lngLineEdit->text().toDouble();
    if(lat < 90 && lat > -90)
        map->setCenter(lat , lng);
    map->invalidate();
}
