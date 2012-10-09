/**
    This file is part of program Reihenaufnahme
    Copyright (C) 2012  FalseCAM

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "message.h"
#include <QtCore/QDebug>

Message *Message::singleton = 0;

Message::Message(QObject *parent) :
    QObject(parent)
{
}

Message *Message::getSingleton() {
    if(singleton == 0)
        singleton = new Message();
    return singleton;
}

// Message
void Message::message(QString message) {
    getSingleton()->pmessage(message);
}

void Message::pmessage(QString message) {
    emit gotMessage(message);
}

// Debug
void Message::debug(QString debug_message) {
    getSingleton()->pdebug(debug_message);
}

void Message::pdebug(QString debug_message) {
    emit gotDebug(debug_message);
    qDebug("%s", qPrintable(debug_message));
}
