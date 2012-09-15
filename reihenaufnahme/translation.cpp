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

#include "translation.h"
#include <Qt/qdir.h>
#include <Qt/qtranslator.h>
#include <Qt/qdebug.h>
#include <Qt/qcoreapplication.h>
#include "reihenaufnahme.h"

Translation::Translation(QObject *parent) :
    QObject(parent)
{
    languages = new QMultiMap<QString, QString>();
    foreach( QString qmFile, qmFiles()){
        if(!languageName(qmFile).isEmpty())
            languages->insert(languageName(qmFile), qmFile);
    }
    loadLanguage();
    loadLanguageFile();
}

Translation::~Translation(){
    delete languages;
}

void Translation::loadLanguage(){
    QSettings settings(Reihenaufnahme::organizationName(), Reihenaufnahme::applicationName());
    this->currentLanguage = settings.value(QString::fromUtf8("language"), "English").toString();
}


void Translation::setLanguage(QString language){
    QSettings settings(Reihenaufnahme::organizationName(), Reihenaufnahme::applicationName());
    settings.setValue("language", language);
}

QStringList Translation::getLanguages(){
    return QStringList(languages->keys());
}

QString Translation::language(){
    return this->currentLanguage;
}

QString Translation::locale(){
    return tr("en"); // Locale of language, here en for english
}

void Translation::loadLanguageFile(){
    QTranslator *translator = new QTranslator;
    translator->load(languages->value(this->currentLanguage));
    Reihenaufnahme::installTranslator(translator);
}

QStringList Translation::qmFiles()
{
    QDir dir(Reihenaufnahme::applicationDirPath()+"/i18n");
    QStringList fileNames = dir.entryList(QStringList("*.qm"), QDir::Files,
                                          QDir::Name);
    QMutableStringListIterator i(fileNames);
    while (i.hasNext()) {
        i.next();
        i.setValue(dir.filePath(i.value()));
    }
    return fileNames;
}

QString Translation::languageName(const QString &qmFile)
{
    QTranslator translator;
    translator.load(qmFile);
    return translator.translate("Translation", "English");
}

void Translation::installPluginTranslation(QString pluginName){
    QTranslator *translator = new QTranslator;
    QString file(Reihenaufnahme::applicationDirPath()+"/i18n/"+ pluginName + "_" + locale()+ ".qm" );
    qDebug("%s",qPrintable(file));
    translator->load(file);
    Reihenaufnahme::installTranslator(translator);
}
