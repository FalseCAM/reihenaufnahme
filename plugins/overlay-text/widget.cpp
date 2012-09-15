#include "widget.h"
#include "ui_widget.h"
#include <QSettings>
#include <QFontDialog>
#include <QColorDialog>
#include <QPainter>

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

    ui->overlayCheckBox->setChecked(settings.value("OverlayTextUse").toBool());
    ui->Text->setText(settings.value("OverlayText").toString());
    ui->xSpinBox->setValue(settings.value("OverlayX").toInt());
    ui->ySpinBox->setValue(settings.value("OverlayY").toInt());
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
