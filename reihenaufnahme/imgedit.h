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

#ifndef IMGEDIT_H
#define IMGEDIT_H

#include "image.h"
#include <QtCore/QRunnable>

/**
 * @brief The ImgEdit class
 *  This class is a thread to parallelize edit and out part of images.
 */

class ImgEdit : public QRunnable
{
public:
    explicit ImgEdit(Image *img);
protected:
    void run();

private:
    Image *image;
    void edit(Image *image);
    void out(Image *image);

};

#endif // PROCESS_H
