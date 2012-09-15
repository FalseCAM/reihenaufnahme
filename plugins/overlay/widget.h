#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFont>
#include <QColor>
#include <QPixmap>
#include <QGraphicsScene>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void addOverlay(QImage *image);
    bool isOverlay();

private:
    Ui::Widget *ui;

    void loadState();
    void saveState();

private slots:
    void setOverlayImage();
    void addOverlay(QImage* image, QString overlay);
    void updatePreviewImage();

    void on_overlayCheckBox_toggled(bool checked);
    void on_examplePushButton_clicked();
};

#endif // WIDGET_H
