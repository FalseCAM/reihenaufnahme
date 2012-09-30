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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tipsdialog.h"
#include "reihenaufnahme.h"
#include "translation.h"
#include "aboutdialog.h"
#include "plugins/pluginsconfigdialog.h"
#include "plugins/pluginloader.h"
#include "message.h"

#include <QtWidgets/QSplashScreen>
#include <QtCore/QTranslator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QSplashScreen splash;
    splash.setPixmap(QPixmap(":/reihenaufnahme/r0"));
    splash.show();

    splash.showMessage("Starting " + QCoreApplication::applicationName(),
                       Qt::AlignTop | Qt::AlignRight, Qt::white);

    translation = new Translation();
    timer = new QElapsedTimer();
    ui->setupUi(this);
    splash.showMessage("Loading config ...", Qt::AlignTop | Qt::AlignRight,
                                         Qt::white);
    createLanguageMenu();
    createToolBar();
    this->setWindowTitle(Reihenaufnahme::applicationName() + " " + Reihenaufnahme::applicationVersion());

    splash.showMessage("Loading Plugins ...", Qt::AlignTop | Qt::AlignRight,
                       Qt::white);
    loadInputPluginWidgets();
    loadEditPluginWidgets();
    loadOutputPluginWidgets();
    TipsDialog tips;
    tips.showOnStartup();
    process = new Process();
    connect(process, SIGNAL(process(int)), ui->progressBar, SLOT(setValue(int)));
    connect(process, SIGNAL(processImage(QImage*)), this, SLOT(updateProcessImage(QImage*)));
    connect(process, SIGNAL(finished()), this, SLOT(on_stopPushButton_clicked()));
    connect(Message::getSingleton(), SIGNAL(gotMessage(QString)), ui->statusBar, SLOT(showMessage(QString)));
    splash.finish(this);
}

MainWindow::~MainWindow()
{
    Reihenaufnahme::destroy();
    delete translation;
    delete ui;
}

void MainWindow::createLanguageMenu(){
    QStringList languages = translation->getLanguages();
    foreach(QString language, languages){
        QAction *action = new QAction(language, this);
        // Set current language as checked.
        connect(action, SIGNAL(triggered()), this, SLOT(languageChosen()));
        action->setCheckable(true);
        if(language == translation->language()){
            action->setChecked(true);
        }
        ui->menuLanguage->addAction(action);
    }
}

void MainWindow::createToolBar(){
    ui->mainToolBar->addAction(ui->actionPlugins);
}

void MainWindow::languageChosen(){
    QAction *action = qobject_cast<QAction *>(sender());
    // set all actions as not checked
    foreach(QAction *lang, ui->menuLanguage->actions()){
        lang->setChecked(false);
    }
    // Set currently selected action as checked.
    action->setChecked(true);
    translation->setLanguage(action->text());
}

void MainWindow::on_actionTips_triggered()
{
    TipsDialog tips;
    tips.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dialog;
    dialog.exec();
}

void MainWindow::on_actionPlugins_triggered()
{
    PluginsConfigDialog dialog;
    dialog.exec();
    loadInputPluginWidgets();
    loadEditPluginWidgets();
    loadOutputPluginWidgets();
}

void MainWindow::loadInputPluginWidgets(){
    ui->inputPluginTabWidget->clear();
    foreach (InputPlugin *plugin, PluginLoader::getInstance().getInputPlugins())
    {
        if (plugin && PluginLoader::getInstance().isActivatedPlugin(plugin)){
            ui->inputPluginTabWidget->addTab(plugin->getWidget(), plugin->getIcon(), plugin->getTitle());
        }
    }
}

void MainWindow::loadEditPluginWidgets(){
    ui->editPluginTabWidget->clear();
    foreach (EditPlugin *plugin, PluginLoader::getInstance().getEditPlugins())
    {
        if (plugin && PluginLoader::getInstance().isActivatedPlugin(plugin)){
            ui->editPluginTabWidget->addTab(plugin->getWidget(), plugin->getIcon(), plugin->getTitle());
        }
    }
}

void MainWindow::loadOutputPluginWidgets(){
    ui->outputPluginTabWidget->clear();
    foreach (OutputPlugin *plugin, PluginLoader::getInstance().getOutputPlugins())
    {
        if (plugin && PluginLoader::getInstance().isActivatedPlugin(plugin)){
            ui->outputPluginTabWidget->addTab(plugin->getWidget(), plugin->getIcon(), plugin->getTitle());
        }
    }
}

void MainWindow::on_startPushButton_clicked()
{
    ui->startPushButton->setEnabled(false);
    ui->stopPushButton->setEnabled(true);

    ui->inputGroupBox->setEnabled(false);
    ui->editGroupBox->setEnabled(false);
    ui->outputGroupBox->setEnabled(false);

    ui->actionPlugins->setEnabled(false);

    timer->start();
    process->start();
}

void MainWindow::on_stopPushButton_clicked()
{
    ui->startPushButton->setEnabled(true);
    ui->stopPushButton->setEnabled(false);

    ui->inputGroupBox->setEnabled(true);
    ui->editGroupBox->setEnabled(true);
    ui->outputGroupBox->setEnabled(true);

    ui->actionPlugins->setEnabled(true);
    ui->statusBar->showMessage(tr("Finnished in %1 milliseconds.").arg(timer->elapsed()));
    process->stop();
}

void MainWindow::on_inputPluginTabWidget_tabCloseRequested(int index)
{
    int counter = -1;
    foreach (InputPlugin *plugin, PluginLoader::getInstance().getInputPlugins())
    {
        if (plugin && PluginLoader::getInstance().isActivatedPlugin(plugin)){
            counter++;
            if(counter == index){
                PluginLoader::getInstance().deactivatePlugin(plugin);
            }
        }
    }
    loadInputPluginWidgets();
}

void MainWindow::on_editPluginTabWidget_tabCloseRequested(int index)
{
    int counter = -1;
    foreach (EditPlugin *plugin, PluginLoader::getInstance().getEditPlugins())
    {
        if (plugin && PluginLoader::getInstance().isActivatedPlugin(plugin)){
            counter++;
            if(counter == index){
                PluginLoader::getInstance().deactivatePlugin(plugin);
            }
        }
    }
    loadEditPluginWidgets();
}

void MainWindow::on_outputPluginTabWidget_tabCloseRequested(int index)
{
    int counter = -1;
    foreach (OutputPlugin *plugin, PluginLoader::getInstance().getOutputPlugins())
    {
        if (plugin && PluginLoader::getInstance().isActivatedPlugin(plugin)){
            counter++;
            if(counter == index){
                PluginLoader::getInstance().deactivatePlugin(plugin);
            }
        }
    }
    loadOutputPluginWidgets();
}

void MainWindow::updateProcessImage(QImage *image){
    ui->processImageLabel->setPixmap(QPixmap().fromImage(*image).scaled(64,64));
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}
