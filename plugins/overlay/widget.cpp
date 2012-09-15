#include "widget.h"
#include "ui_widget.h"
#include <QSettings>
#include <QFileDialog>
#include <QPainter>
#include <QFile>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->overlayButton, SIGNAL(clicked()), this, SLOT(setOverlayImage()));
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
    settings.beginGroup("Overlay");

    ui->overlayCheckBox->setChecked(settings.value("OverlayUse").toBool());
    ui->overlayImage->setText(settings.value("OverlayImage").toString());
    updatePreviewImage();
}

void Widget::saveState(){
    QSettings settings(QCoreApplication::organizationName(),
            QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("Overlay");

    settings.setValue("OverlayUse", ui->overlayCheckBox->isChecked());
    settings.setValue("OverlayImage", ui->overlayImage->text());
}

void Widget::addOverlay(QImage *image){
    addOverlay(image, ui->overlayImage->text());
}

// Set Overlay Image to data
void Widget::setOverlayImage() {
    // opens a Dialog to choose save directory
    QString file = QFileDialog::getOpenFileName(this,
            tr("Please select a file"), ui->overlayImage->text(),
            "All Supported Image Files (*.bmp *.png *.tif *.tiff);;"
                "All Files (*.*)");
    // checks for dir exists
    if (QFile(file).exists()) {
        // save chosen dir
        this->ui->overlayImage->setText(file);
        updatePreviewImage();
    }
}

// add Overlay
void Widget::addOverlay(QImage* image, QString overlay) {
    if (overlay.isEmpty())
        return;
    QPainter painter(image);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0,
            QImage(overlay).scaled(image->width(), image->height()));
    painter.end();
}

void Widget::updatePreviewImage(){
    if(ui->overlayCheckBox->isChecked() && !ui->overlayImage->text().isEmpty()){
        QImage img(":/reihenaufnahme/r1");
        addOverlay(&img, this->ui->overlayImage->text());
        ui->image->setPixmap(QPixmap::fromImage(img));
    } else {
        ui->image->setPixmap(QPixmap(":/reihenaufnahme/r1"));
    }
}

bool Widget::isOverlay(){
    return ui->overlayCheckBox->isChecked();
}

void Widget::on_overlayCheckBox_toggled(bool checked)
{
    updatePreviewImage();
}

void Widget::on_examplePushButton_clicked()
{
    this->ui->overlayImage->setText(":/plugins/overlay/example");
    updatePreviewImage();
}
