#include "widget.h"
#include "ui_widget.h"
#include <QSettings>

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
}


bool Widget::isRename(){
    return ui->renameCheckBox->isChecked();
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

void Widget::example(){
    QString text = tr("example");
    if(isRename() && isNewName()){
        text = getNewName();
    }
    if(isRename() && !(getPrefix().isEmpty() && getSuffix().isEmpty())){
        text.prepend(getPrefix());
        text.append(getSuffix());
    }
    if(isRename() && isCounter()){
        text.append(QString("%1").arg(getCounterStart(), getCounterDecimals(), 10, QChar('0')) );
    }

    ui->exampleLabel->setText(text);
}
