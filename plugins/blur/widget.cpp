#include "widget.h"
#include "ui_widget.h"
#include "blur.h"
#include <Qt/qsettings.h>
#include <Qt/qpainter.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    this->previewImage = 0;
    ui->setupUi(this);

    previewImageLabel = new PreviewImageLabel(this);
    ui->imageGridLayout->addWidget(previewImageLabel);
    on_resetPushButton_clicked();

    loadState();
    connect(previewImageLabel, SIGNAL(imageDroped(QString)), this, SLOT(setPreviewImage(QString)));
    connect(this->ui->blurCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateImage()));
    connect(this->ui->invertCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateImage()));
    connect(this->ui->radiusSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateImage()));

    connect(this->ui->posXSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateImage()));
    connect(this->ui->posYSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateImage()));
    connect(this->ui->widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateImage()));
    connect(this->ui->heightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateImage()));

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

    ui->blurCheckBox->setChecked(settings.value("BlurUse", false).toBool());
    ui->posXSpinBox->setValue(settings.value("PosX", 10).toInt());
    ui->posYSpinBox->setValue(settings.value("PosY", 10).toInt());
    ui->widthSpinBox->setValue(settings.value("Width", 80).toInt());
    ui->heightSpinBox->setValue(settings.value("Height", 80).toInt());
    ui->radiusSpinBox->setValue(settings.value("Radius", 7).toInt());
}

void Widget::saveState(){
    QSettings settings(QCoreApplication::organizationName(),
                       QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("Color");

    settings.setValue("BlurUse", ui->blurCheckBox->isChecked());
    settings.setValue("PosX", ui->posXSpinBox->value());
    settings.setValue("PosY", ui->posYSpinBox->value());
    settings.setValue("Width", ui->widthSpinBox->value());
    settings.setValue("Height", ui->heightSpinBox->value());
    settings.setValue("Radius", ui->radiusSpinBox->value());
}



void Widget::updateImage(){
    QImage image = QImage(*previewImage);

    if(ui->blurCheckBox->isChecked()){
        blur(&image);
    }
    this->previewImageLabel->setPixmap(QPixmap::fromImage(image));

}

void Widget::setPreviewImage(QString img){
    if(QString::compare(img, this->previewImageSrc) != 0){
        this->previewImageSrc = img;
        if(this->previewImage)
            delete this->previewImage;
        this->previewImage = new QImage(QImage(img).scaled(256,256));
        updateImage();
    }
}

void Widget::on_resetPushButton_clicked()
{
    setPreviewImage(QString(":/reihenaufnahme/r5"));
}

// Function blurs a rect of image by percentage
void Widget::blur(QImage *image){
    // uses percentage

    int fullw = image->width();
    int fullh = image->height();
    int x = ui->posXSpinBox->value() * fullw / 100;
    int y = ui->posYSpinBox->value() * fullh / 100;
    int w = ui->widthSpinBox->value() * fullw / 100;
    int h = ui->heightSpinBox->value() * fullh / 100;
    if(x+w > fullw) w = fullw-x;
    if(y+h > fullh) h = fullh-y;

    if(! ui->invertCheckBox->isChecked()){
        *image = Blur::blurred(*image, QRect(x, y, w, h), ui->radiusSpinBox->value());
    }else{
        QImage copy(*image);
        *image = Blur::blurred(*image, QRect(0, 0, fullw, fullh), getRadius());
        QPainter painter(image);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawImage(x, y, copy, x, y,  w, h);
        painter.end();
    }
}

bool Widget::isBlur(){
    return ui->blurCheckBox->isChecked();
}

bool Widget::isInverted(){
    return ui->invertCheckBox->isChecked();
}

int Widget::getPosX(){
    return ui->posXSpinBox->value();
}

int Widget::getPosY(){
    return ui->posYSpinBox->value();
}

int Widget::getWidth(){
    return ui->widthSpinBox->value();
}

int Widget::getHeight(){
    return ui->heightSpinBox->value();
}

int Widget::getRadius(){
    return ui->radiusSpinBox->value();
}
