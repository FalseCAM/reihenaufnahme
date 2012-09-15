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
    void addOverlay(QImage *image, QString overlay);

    QFont *font;
    QColor *color;
    QPixmap *pixmap;
    QPixmap *scenePixmap;
    QGraphicsScene *scene;
    QImage *previewImage;

private slots:
    void setFont();
    void setColor();
    void makePreview();

};

#endif // WIDGET_H
