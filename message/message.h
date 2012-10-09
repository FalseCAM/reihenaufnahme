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
#ifndef MESSAGE_H
#define MESSAGE_H

#include "message_global.h"
#include <QtCore/QObject>

class MESSAGESHARED_EXPORT Message : public QObject
{
    Q_OBJECT
public:
    static Message *getSingleton();
    static void message(QString message);
    static void debug(QString debug_message);

signals:
    void gotMessage(QString);
    void gotDebug(QString);

public slots:

private:
    explicit Message(QObject *parent = 0);
    static Message *singleton;

    void pmessage(QString message);
    void pdebug(QString debug_message);
};

#endif // MESSAGE_H
