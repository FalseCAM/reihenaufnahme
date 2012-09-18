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

#ifndef REIHENAUFNAHME_H
#define REIHENAUFNAHME_H

#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QCoreApplication>
#include <QtCore/QTranslator>
#include <QtGui/QIcon>

class Reihenaufnahme : public QObject
{
    Q_OBJECT
public:
    
    static void setApplicationName(QString name);
    static void setApplicationVersion(QString version);
    static void setOrganizationName(QString organization_name);

    static QString applicationName();
    static QString applicationVersion();
    static QString organizationName();
    static QIcon applicationIcon();

    static QString applicationDirPath();

    static void installTranslator(QTranslator *file);

    static void destroy();

signals:
    
public slots:
    
};

#endif // REIHENAUFNAHME_H
