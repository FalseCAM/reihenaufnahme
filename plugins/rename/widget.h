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

    bool isRename();
    bool isNewName();
    bool isCounter();
    QString getNewName();
    QString getPrefix();
    QString getSuffix();
    int getCounterStart();
    int getCounterDecimals();
    
private:
    Ui::Widget *ui;
    void loadState();
    void saveState();
private slots:
    void example();
};

#endif // WIDGET_H
