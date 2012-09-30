#include "message.h"

Message *Message::singleton = 0;

Message::Message(QObject *parent) :
    QObject(parent)
{
}

Message *Message::getSingleton(){
    if(singleton == 0)
        singleton = new Message();
    return singleton;
}

void Message::message(QString message){
    getSingleton()->pmessage(message);
}

void Message::pmessage(QString message){
    emit gotMessage(message);
}
