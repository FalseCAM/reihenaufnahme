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

#include "process.h"
#include "plugins/pluginloader.h"

Process::Process(QObject *parent) :
    QThread(parent)
{
}

void Process::run(){
    stopped = false;
    emit process(0);
    foreach(InputPlugin *inputPlugin, PluginLoader::getInstance().getInputPlugins()){
        if(PluginLoader::getInstance().isActivatedPlugin(inputPlugin)){
            inputPlugin->init();
            while(inputPlugin->hasNext()){
                Image *img = inputPlugin->next();
                edit(img);
                out(img);
                emit process(inputPlugin->getProgress());
                if(stopped){
                    emit process(100);
                    return;
                }
            }
        }
    }
    finnish();
}

void Process::stop(){
    this->stopped = true;
}

void Process::edit(Image *image){
    foreach(EditPlugin *editPlugin, PluginLoader::getInstance().getEditPlugins()){
        if(stopped) return;
        if(PluginLoader::getInstance().isActivatedPlugin(editPlugin)){
            editPlugin->edit(image);
        }
    }
}

void Process::out(Image *image){
    foreach(OutputPlugin *outputPlugin, PluginLoader::getInstance().getOutputPlugins()){
        if(stopped) return;
        if(PluginLoader::getInstance().isActivatedPlugin(outputPlugin)){
            outputPlugin->out(image);
        }
    }
}

void Process::finnish(){
    emit process(100);
    foreach(OutputPlugin *outputPlugin, PluginLoader::getInstance().getOutputPlugins()){
        if(stopped){
            return;
        }
        if(PluginLoader::getInstance().isActivatedPlugin(outputPlugin)){
            outputPlugin->finnish();
        }
    }
}
