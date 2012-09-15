#include "widget.h"
#include "ui_widget.h"
#include <QSettings>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->angleSpinBox, SIGNAL(valueChanged(int)), this, SLOT(angleChanged(int)));
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
    settings.beginGroup("Rotate");

    ui->clockwiseRotationRadioButton->setChecked(settings.value("Clockwise", false).toBool());
    ui->clockwise180RadioButton->setChecked(settings.value("Clockwise180", false).toBool());
    ui->counterClockwiseRadioButton->setChecked(settings.value("CounterClockwise", false).toBool());
    ui->byAngleRotationRadioButton->setChecked(settings.value("ByAngle", false).toBool());
    ui->angleSpinBox->setValue(settings.value("Angle", 0).toInt());
}

void Widget::saveState(){
    QSettings settings(QCoreApplication::organizationName(),
            QCoreApplication::applicationName());
    settings.beginGroup("plugins");
    settings.beginGroup("Rotate");

    settings.setValue("Clockwise", ui->clockwiseRotationRadioButton->isChecked());
    settings.setValue("Clockwise180", ui->clockwise180RadioButton->isChecked());
    settings.setValue("CounterClockwise", ui->counterClockwiseRadioButton->isChecked());
    settings.setValue("ByAngle", ui->byAngleRotationRadioButton->isChecked());
    settings.setValue("Angle", ui->angleSpinBox->value());
}

void Widget::angleChanged(int value){
    if(value < 0){
        ui->angleSpinBox->setValue(359);
    } else if(value > 359){
        ui->angleSpinBox->setValue(0);
    } else {}
}

bool Widget::rotateClockwise(){
    return ui->clockwiseRotationRadioButton->isChecked();
}

bool Widget::rotateCounterClockwise(){
    return ui->counterClockwiseRadioButton->isChecked();
}

bool Widget::rotateClockwise180(){
    return ui->clockwise180RadioButton->isChecked();
}

bool Widget::rotateByAngle(){
    return ui->byAngleRotationRadioButton->isChecked();
}

int Widget::angle(){
    return ui->angleSpinBox->value();
}
