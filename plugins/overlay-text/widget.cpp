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
#include <QtWidgets/QFontDialog>
#include <QtWidgets/QColorDialog>
#include <QtGui/QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    font = new QFont();
    color = new QColor();
    pixmap = new QPixmap(32, 32);
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(setFont()));
    connect(ui->colorPushButton, SIGNAL(clicked()), this, SLOT(setColor()));

    connect(ui->Text, SIGNAL(editingFinished()), this, SLOT(makePreview()));
    connect(ui->xSpinBox, SIGNAL(valueChanged(int)), this, SLOT(makePreview()));
    connect(ui->ySpinBox, SIGNAL(valueChanged(int)), this, SLOT(makePreview()));
    loadState();

    ui->fontComboBox->setCurrentFont(*font);
    pixmap->fill(*color);
    ui->colorPushButton->setIcon(QIcon(*pixmap));
    makePreview();
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
    settings.beginGroup("OverlayText");

    ui->overlayCheckBox->setChecked(settings.value("OverlayTextUse", false).toBool());
    ui->Text->setText(settings.value("OverlayText").toString());
    ui->xSpinBox->setValue(settings.value("OverlayX").toInt());
    ui->ySpinBox->setValue(settings.value("OverlayY").toInt());
    ui->exifDateCheckBox->setChecked(settings.value("ExifDateUse", false).toBool());
    ui->exifDateComboBox->setCurrentIndex(ui->exifDateComboBox->findText(settings.value("ExifDateFormatCombo").toString()));
    ui->exifDateLineEdit->setText(settings.value("ExifDateFormat").toString());
    font->setPointSize(settings.value("OverlayFontSize").toInt());
    font->setFamily(settings.value("OverlayFontFamily").toString());
    color->setRed(settings.value("OverlayColorR").toInt());
    color->setGreen(settings.value("OverlayColorG").toInt());
    color->setBlue(settings.value("OverlayColorB").toInt());
}

void Widget::saveState(){
    QSettings settings(QCoreApplication::organizationName(),
                       QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("OverlayText");

    settings.setValue("OverlayTextUse", ui->overlayCheckBox->isChecked());
    settings.setValue("OverlayText", ui->Text->text());
    settings.setValue("OverlayX", ui->xSpinBox->value());
    settings.setValue("OverlayY", ui->ySpinBox->value());
    settings.setValue("ExifDateUse", ui->exifDateCheckBox->isChecked());
    settings.setValue("ExifDateFormatCombo", ui->exifDateComboBox->currentText());
    settings.setValue("ExifDateFormat", ui->exifDateLineEdit->text());
    settings.setValue("OverlayFontSize", font->pointSize());
    settings.setValue("OverlayFontFamily", font->family());
    int r, g, b;
    color->getRgb(&r, &g, &b);
    settings.setValue("OverlayColorR", r);
    settings.setValue("OverlayColorG", g);
    settings.setValue("OverlayColorB", b);
}

void Widget::addOverlay(QImage *image){
    addOverlay(image, ui->Text->text());
}

void Widget::addOverlay(Image *image){
    if(ui->exifDateCheckBox->isChecked()){
        QString date = getDateTime(getExifKey("Exif.Photo.DateTimeOriginal" ,image->getExifData()))
                .toString(ui->exifDateLineEdit->text());
        addOverlay(image->getImage(), date);
    }else{
        addOverlay(image->getImage(), ui->Text->text());
    }
}

// add Overlay
void Widget::addOverlay(QImage *image, QString overlay) {
    if (overlay.isEmpty())
        return;
    QPainter painter(image);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    int x = (int) ((double) image->width() * ((double) ui->xSpinBox->value()
                                              / 100.0));
    int y = (int) ((double) image->height() * ((double) ui->ySpinBox->value()
                                               / 100.0));
    painter.setPen(*color);
    QFont tempFont = *font;
    tempFont.setPointSize((int) (tempFont.pointSize() * image->width() / 100));
    painter.setFont(tempFont);
    painter.drawText(x, y, overlay);
    painter.end();
}
// shows a dialog to select font of text
void Widget::setFont() {
    bool ok;
    QFont temp = QFontDialog::getFont(&ok, *font, this);
    if (ok) {
        delete font;
        this->font = new QFont(temp);
        ui->fontComboBox->setCurrentFont(temp);
    }
    makePreview();
}

// shows a dialog to select color of text
void Widget::setColor() {
    QColor temp = QColorDialog::getColor(*color, this);

    delete color;
    color = new QColor(temp);
    pixmap->fill(*color);
    ui->colorPushButton->setIcon(QIcon(*pixmap));
    makePreview();
}

// makes a preview of text with position and size
void Widget::makePreview() {
    QImage previewImage(":/reihenaufnahme/r2");
    addOverlay(&previewImage);
    ui->imageLabel->setPixmap(QPixmap().fromImage(previewImage).scaled(200,200));
}

bool Widget::isOverlay(){
    return ui->overlayCheckBox->isChecked();
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

QString Widget::getExifKey(QString key, Exiv2::ExifData *exifData){
    // returns string represented by exif key
    QString ret;
    try {
        Exiv2::ExifData::iterator pos = exifData->findKey(
                    Exiv2::ExifKey(qPrintable(key)));
        if (pos == exifData->end()) return QString();
        else ret = QString().fromStdString(pos->value().toString());
    } catch (Exiv2::Error& e) {
        qCritical("[Overlay-Text] %s", e.what());
    }
    return ret;
}

void Widget::on_exifDateComboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "1900 12 31"){
        ui->exifDateLineEdit->setText("yyyy MM dd");
    } else if(arg1 == "12/31 23:59:59"){
        ui->exifDateLineEdit->setText("dd/MM hh:mm:ss");
    } else if(arg1 == "31.12 23:59"){
        ui->exifDateLineEdit->setText("dd.MM hh:mm");
    }
}
