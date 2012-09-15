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

#ifndef EDITPLUGIN_H
#define EDITPLUGIN_H

#include <QtPlugin>
#include "plugin.h"
#include "../image.h"

class EditPlugin: public Plugin{
public:
    virtual ~EditPlugin() {
    }

    virtual void edit(Image *image) = 0;
};

Q_DECLARE_INTERFACE(EditPlugin,
        "Reihenaufnahme.EditPlugin/1.0");

#endif // EDITPLUGIN_H
