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

#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
#include <QtCore/QDateTime>

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
    bool isPrependExifDate();
    bool isAppendExifDate();
    QString getNewName();
    QString getPrefix();
    QString getSuffix();
    QString getDateFormat();
    int getCounterStart();
    int getCounterDecimals();

    static QDateTime getDateTime(QString exifDateTime);
    
private:
    Ui::Widget *ui;
    void loadState();
    void saveState();

private slots:
    void example();
    void on_comboBox_currentIndexChanged(const QString &arg1);
};

#endif // WIDGET_H
