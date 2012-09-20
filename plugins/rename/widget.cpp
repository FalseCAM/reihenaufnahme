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
    loadState();
    connect(ui->renameCheckBox, SIGNAL(toggled(bool)), this, SLOT(example()));
    connect(ui->newNameCheckBox, SIGNAL(toggled(bool)), this, SLOT(example()));
    connect(ui->counterCheckBox, SIGNAL(toggled(bool)), this, SLOT(example()));
    connect(ui->newNameLineEdit, SIGNAL(editingFinished()), this, SLOT(example()));
    connect(ui->prefixLineEdit, SIGNAL(editingFinished()), this, SLOT(example()));
    connect(ui->suffixLineEdit, SIGNAL(editingFinished()), this, SLOT(example()));
    connect(ui->startSpinBox, SIGNAL(valueChanged(int)), this, SLOT(example()));
    connect(ui->decimalSpinBox, SIGNAL(valueChanged(int)), this, SLOT(example()));
    connect(ui->prependExifCheckBox, SIGNAL(toggled(bool)), this, SLOT(example()));
    connect(ui->appendExifCheckBox, SIGNAL(toggled(bool)), this, SLOT(example()));
    connect(ui->exifLineEdit, SIGNAL(editingFinished()), this, SLOT(example()));
    example();
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

    ui->renameCheckBox->setChecked(settings.value("RenameUse", false).toBool());
    ui->newNameCheckBox->setChecked(settings.value("NewNameUse", false).toBool());
    ui->newNameLineEdit->setText(settings.value("NewName", "").toString());
    ui->counterCheckBox->setChecked(settings.value("CounterUse", false).toBool());
    ui->prefixLineEdit->setText(settings.value("Prefix", "").toString());
    ui->suffixLineEdit->setText(settings.value("Suffix", "").toString());
    ui->startSpinBox->setValue(settings.value("Start", 1).toInt());
    ui->decimalSpinBox->setValue(settings.value("Decimals", 0).toInt());
    ui->exifLineEdit->setText(settings.value("DateFormat", "yyyy_MM_dd").toString());
    ui->prependExifCheckBox->setChecked(settings.value("PrependExif", false).toBool());
    ui->appendExifCheckBox->setChecked(settings.value("AppendExif", false).toBool());
}

void Widget::saveState(){
    QSettings settings(QCoreApplication::organizationName(),
                       QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("Rename");

    settings.setValue("RenameUse", ui->renameCheckBox->isChecked());
    settings.setValue("NewNameUse", ui->newNameCheckBox->isChecked());
    settings.setValue("NewName", ui->newNameLineEdit->text());
    settings.setValue("CounterUse", ui->counterCheckBox->isChecked());
    settings.setValue("Prefix", ui->prefixLineEdit->text());
    settings.setValue("Suffix", ui->suffixLineEdit->text());
    settings.setValue("Start", ui->startSpinBox->value());
    settings.setValue("Decimals", ui->decimalSpinBox->value());
    settings.setValue("DateFormat", ui->exifLineEdit->text());
    settings.setValue("PrependExif", ui->prependExifCheckBox->isChecked());
    settings.setValue("AppendExif", ui->appendExifCheckBox->isChecked());
}


bool Widget::isRename(){
    return ui->renameCheckBox->isChecked();
}

bool Widget::isPrependExifDate(){
    return ui->prependExifCheckBox->isChecked();
}

bool Widget::isAppendExifDate(){
    return ui->appendExifCheckBox->isChecked();
}

bool Widget::isNewName(){
    return ui->newNameCheckBox->isChecked();
}

bool Widget::isCounter(){
    return ui->counterCheckBox->isChecked();
}

QString Widget::getNewName(){
    return ui->newNameLineEdit->text();
}

QString Widget::getPrefix(){
    return ui->prefixLineEdit->text();
}

QString Widget::getSuffix(){
    return ui->suffixLineEdit->text();
}

int Widget::getCounterStart(){
    return ui->startSpinBox->value();
}

int Widget::getCounterDecimals(){
    return ui->decimalSpinBox->value();
}

QString Widget::getDateFormat(){
    return ui->exifLineEdit->text();
}

void Widget::example(){
    QString text = tr("example");
    if(isRename()){
        if(isNewName()){
            text = getNewName();
        }
        if(isPrependExifDate()){
            text.prepend(getDateTime("").toString(ui->exifLineEdit->text()));
        }
        if(isAppendExifDate()){
            text.append(getDateTime("").toString(ui->exifLineEdit->text()));
        }
        if(!(getPrefix().isEmpty() && getSuffix().isEmpty())){
            text.prepend(getPrefix());
            text.append(getSuffix());
        }
        if(isCounter()){
            text.append(QString("%1").arg(getCounterStart(), getCounterDecimals(), 10, QChar('0')) );
        }
    }

    ui->exampleLabel->setText(text);
}

QDateTime Widget::getDateTime(QString exifDateTime){
    QDateTime dateTime;
    dateTime = QDateTime::fromString( exifDateTime,
                                      "yyyy:MM:dd hh:mm:ss");

    // Check if there is a correct Date
    if (!dateTime.isValid())
        return QDateTime(QDate(1900, 1, 1), QTime(0, 0, 0));
    return dateTime;
}

void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "1900_12_31_23_59_59"){
        ui->exifLineEdit->setText("yyyy_MM_dd_hh_mm_ss");
    }else if(arg1 == "1900_12_31"){
        ui->exifLineEdit->setText("yyyy_MM_dd");
    }else if(arg1 == "31_12_1900"){
        ui->exifLineEdit->setText("dd_MM_yyyy");
    }else if(arg1 == "31_12_23_59"){
        ui->exifLineEdit->setText("dd_MM_hh_mm");
    }
}
