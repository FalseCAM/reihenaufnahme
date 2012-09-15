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

    bool isGrayscale();
    bool isSwap();
    bool isInvert();
    bool isSepia();
    
private slots:
    void on_grayscaleCheckBox_toggled(bool checked);

    void on_invertCheckBox_toggled(bool checked);

    void on_swapCheckBox_toggled(bool checked);

    void on_sepiaCheckBox_toggled(bool checked);

private:
    Ui::Widget *ui;
    void loadState();
    void saveState();
    void updateImage();
};

#endif // WIDGET_H
