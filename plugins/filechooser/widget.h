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
    QStringList getFiles();
    
private slots:
    void on_removeImagePushButton_clicked();

    void on_clearListPushButton_clicked();

    void on_addImagesPushButton_clicked();

    void on_showPreviewCheckBox_toggled(bool checked);

private:
    Ui::Widget *ui;
    // Drag n Drop
    void dragEnterEvent( QDragEnterEvent* event );
    void dropEvent( QDropEvent* event );

    QStringList filesList;
    QString lastFolder;
    void loadState();
    void saveState();
    void addFiles();
    void addFiles(QStringList files);
    void addFileItem(QString file);
};

#endif // WIDGET_H
