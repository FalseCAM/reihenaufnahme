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

#include "reihenaufnahme.h"
#include "plugins/pluginloader.h"

#include <QtCore/QCoreApplication>

void Reihenaufnahme::setApplicationName(QString name){
    QCoreApplication::setApplicationName(name);
}

void Reihenaufnahme::setApplicationVersion(QString version){
    QCoreApplication::setApplicationVersion(version);
}

void Reihenaufnahme::setOrganizationName(QString organization_name){
    QCoreApplication::setOrganizationName(organization_name);
}

QString Reihenaufnahme::applicationName(){
    return QCoreApplication::applicationName();
}

QString Reihenaufnahme::applicationVersion(){
    return QCoreApplication::applicationVersion();
}

QString Reihenaufnahme::organizationName(){
    return QCoreApplication::organizationName();
}

QIcon Reihenaufnahme::applicationIcon(){
    return QIcon(":/reihenaufnahme/r5");
}

QString Reihenaufnahme::applicationDirPath(){
    return QCoreApplication::applicationDirPath();
}

void Reihenaufnahme::installTranslator(QTranslator *file){
    QCoreApplication::installTranslator(file);
}

void Reihenaufnahme::destroy(){
    PluginLoader::destroyInstance();
}
