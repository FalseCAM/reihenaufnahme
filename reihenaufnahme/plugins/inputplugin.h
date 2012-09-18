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

#ifndef INPUTPLUGIN_H
#define INPUTPLUGIN_H

#include "plugin.h"
#include "../image.h"

#include <QtCore/QtPlugin>

class InputPlugin: public Plugin{
public:
    virtual ~InputPlugin() {
    }

    virtual void init() = 0;
    virtual bool hasNext() = 0;
    virtual Image *next() = 0;
    virtual int getProgress() = 0;
};

Q_DECLARE_INTERFACE(InputPlugin,
        "Reihenaufnahme.InputPlugin/1.0");

#endif // INPUTPLUGIN_H
