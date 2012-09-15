#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "previewimagelabel.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    bool isBlur();
    bool isInverted();

    int getPosX();
    int getPosY();
    int getWidth();
    int getHeight();
    int getRadius();
    
private slots:

    void on_resetPushButton_clicked();
    void setPreviewImage(QString img);
    void updateImage();

private:
    Ui::Widget *ui;
    void loadState();
    void saveState();

    void blur(QImage *image);
    PreviewImageLabel *previewImageLabel;

    QString previewImageSrc;
    QImage *previewImage;


};

#endif // WIDGET_H
