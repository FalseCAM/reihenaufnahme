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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "translation.h"
#include "process.h"

#include <QtWidgets/QMainWindow>
#include <QtCore/QElapsedTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void languageChosen();
private slots:
    void on_actionTips_triggered();

    void on_actionAbout_triggered();

    void on_actionPlugins_triggered();

    void on_startPushButton_clicked();

    void on_stopPushButton_clicked();

    void on_editPluginTabWidget_tabCloseRequested(int index);

    void on_inputPluginTabWidget_tabCloseRequested(int index);

    void on_outputPluginTabWidget_tabCloseRequested(int index);

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;

    QElapsedTimer *timer;

    void createLanguageMenu();
    void createToolBar();

    Translation *translation;
    void loadInputPluginWidgets();
    void loadEditPluginWidgets();
    void loadOutputPluginWidgets();

    Process *process;
};

#endif // MAINWINDOW_H
