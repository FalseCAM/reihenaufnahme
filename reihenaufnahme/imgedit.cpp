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
#include "imgedit.h"
#include <QtCore/QThreadPool>

ImgEdit::ImgEdit(Image *img)
{
    this->image = img;
}

void ImgEdit::run(){
    edit(image);
    out(image);
}

void ImgEdit::edit(Image *image){
    foreach(EditPlugin *editPlugin, PluginLoader::getInstance().getEditPlugins()){
        if(PluginLoader::getInstance().isActivatedPlugin(editPlugin)){
            editPlugin->edit(image);
        }
    }
}

void ImgEdit::out(Image *image){
    foreach(OutputPlugin *outputPlugin, PluginLoader::getInstance().getOutputPlugins()){
        if(PluginLoader::getInstance().isActivatedPlugin(outputPlugin)){
            outputPlugin->out(image);
        }
    }
}
