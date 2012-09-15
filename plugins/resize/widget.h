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

    bool percentChange();
    bool pixelChange();

    int percentX();
    int percentY();

    int pixelX();
    int pixelY();
    
private slots:
    void on_sizeRatioComboBox_currentIndexChanged(const QString &arg1);

    void on_pixelComboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::Widget *ui;
    void loadState();
    void saveState();
};

#endif // WIDGET_H
