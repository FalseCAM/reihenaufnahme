#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    bool rotateClockwise();
    bool rotateClockwise180();
    bool rotateCounterClockwise();
    bool rotateByAngle();
    int angle();
    
private:
    Ui::Widget *ui;
    void loadState();
    void saveState();
private slots:
    void angleChanged(int value);
};

#endif // WIDGET_H
