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

#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "reihenaufnahme.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QUrl>
#include <QtCore/QEventLoop>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->versionLabel->setText(Reihenaufnahme::applicationVersion());
    initAbout();
    initAuthors();
    initThanksto();
    initLicense();
    initUpdates();
}

AboutDialog::~AboutDialog()
{
    delete ui;
    delete manager;
}

void AboutDialog::initLicense(){
    ui->licenseBrowser->setAlignment(Qt::AlignCenter);

    QFile file(":/reihenaufnahme/license.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
    } else {
        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull()) {
            ui->licenseBrowser->insertPlainText(line);
            ui->licenseBrowser->insertPlainText("\n");
            line = in.readLine();
        }
        ui->licenseBrowser->moveCursor(QTextCursor::Start);
    }
}

void AboutDialog::initAbout(){
    ui->aboutLabel->setAlignment(Qt::AlignCenter);

    QFile file(":/reihenaufnahme/about.html");
    QString text;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
    } else {
        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull()) {
            text.append(line);
            text.append("\n");
            line = in.readLine();
        }
    }
    ui->aboutLabel->setText(text);
}

void AboutDialog::initAuthors(){
    ui->authorsLabel->setAlignment(Qt::AlignCenter);

    QFile file(":/reihenaufnahme/authors.html");
    QString text;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
    } else {
        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull()) {
            text.append(line);
            text.append("\n");
            line = in.readLine();
        }
    }
    ui->authorsLabel->setText(text);
}

void AboutDialog::initThanksto(){
    ui->thankstoLabel->setAlignment(Qt::AlignCenter);

    QFile file(":/reihenaufnahme/thanksto.html");
    QString text;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
    } else {
        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull()) {
            text.append(line);
            text.append("\n");
            line = in.readLine();
        }
    }
    ui->thankstoLabel->setText(text);
}

void AboutDialog::initUpdates(){
    ui->thisVersionLabel->setText(tr("This Version: ") + Reihenaufnahme::applicationVersion());
    manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("http://reihenaufnahme.falsecam.net/version")));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    ui->htmlVersionLabel->setText(reply->readAll());
    QObject::disconnect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    delete reply;
}

void AboutDialog::on_pushButton_clicked()
{
    this->close();
}
