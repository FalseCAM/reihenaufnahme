#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

class Message : public QObject
{
    Q_OBJECT
public:
    static Message *getSingleton();
    static void message(QString message);


    
signals:
    void gotMessage(QString);
    
public slots:
    
private:
    explicit Message(QObject *parent = 0);
    static Message *singleton;

    void pmessage(QString message);
};

#endif // MESSAGE_H
