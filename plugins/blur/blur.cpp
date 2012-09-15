/*
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "blur.h"
#include "widget.h"
#include <Qt/qpainter.h>

Blur::Blur()
{
    widget = 0;
}

Blur::~Blur()
{
    if(this->widget)
        delete this->widget;
}

QString Blur::getName(){
    return QString("blur");
}

QString Blur::getTitle(){
    return QString(tr("Blur"));
}

QString Blur::getVersion(){
    return QString("0.1");
}

QString Blur::getAuthor(){
    return QString("FalseCAM");
}

QString Blur::getDescription(){
    return QString(tr("Plugin to blur images"));
}

QIcon Blur::getIcon(){
    return QIcon(":/plugins/blur/blur");
}

QWidget *Blur::getWidget(){
    if(!this->widget){
        this->widget = new Widget();
    }
    return this->widget;
}

void Blur::edit(Image *img){
    QImage *image = img->getImage();
    if(!widget->isBlur())
        return;

    int fullw = image->width();
    int fullh = image->height();
    int x = widget->getPosX() * fullw / 100;
    int y = widget->getPosY() * fullh / 100;
    int w = widget->getWidth() * fullw / 100;
    int h = widget->getHeight() * fullh / 100;
    if(x+w > fullw) w = fullw-x;
    if(y+h > fullh) h = fullh-y;

    if(! widget->isInverted()){

        *image = Blur::blurred(*image, QRect(x, y, w, h), widget->getRadius());

    }else{
        QImage copy(*image);
        *image = Blur::blurred(*image, QRect(0, 0, fullw, fullh), widget->getRadius());
        QPainter painter(image);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawImage(x, y, copy, x, y,  w, h);
        painter.end();
    }
}

// Code from: http://qt.gitorious.org/qt/qt/blobs/7d5b560f71e0f11c20b7ebef11f3095e760ca32c/src/gui/image/qpixmapfilter.cpp

// Blur the image according to the blur radius

// Based on exponential blur algorithm by Jani Huhtanen

// (maximum radius is set to 16)

QImage Blur::blurred(QImage& image, const QRect& rect, int radius, bool alphaOnly)

{

    int tab[] = { 14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2 };

    int alpha = (radius < 1)  ? 16 : (radius > 17) ? 1 : tab[radius-1];

    QImage result = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);

    int r1 = rect.top();

    int r2 = rect.bottom();

    int c1 = rect.left();

    int c2 = rect.right();

    int bpl = result.bytesPerLine();

    int rgba[4];

    unsigned char* p;

    int i1 = 0;

    int i2 = 3;

    if (alphaOnly)

        i1 = i2 = (QSysInfo::ByteOrder == QSysInfo::BigEndian ? 0 : 3);

    for (int col = c1; col <= c2; col++) {

        p = result.scanLine(r1) + col * 4;

        for (int i = i1; i <= i2; i++)

            rgba[i] = p[i] << 4;

        p += bpl;

        for (int j = r1; j < r2; j++, p += bpl)

            for (int i = i1; i <= i2; i++)

                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;

    }

    for (int row = r1; row <= r2; row++) {

        p = result.scanLine(row) + c1 * 4;

        for (int i = i1; i <= i2; i++)

            rgba[i] = p[i] << 4;

        p += 4;

        for (int j = c1; j < c2; j++, p += 4)

            for (int i = i1; i <= i2; i++)

                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;

    }

    for (int col = c1; col <= c2; col++) {

        p = result.scanLine(r2) + col * 4;

        for (int i = i1; i <= i2; i++)

            rgba[i] = p[i] << 4;

        p -= bpl;

        for (int j = r1; j < r2; j++, p -= bpl)

            for (int i = i1; i <= i2; i++)

                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;

    }

    for (int row = r1; row <= r2; row++) {

        p = result.scanLine(row) + c2 * 4;

        for (int i = i1; i <= i2; i++)

            rgba[i] = p[i] << 4;

        p -= 4;

        for (int j = c1; j < c2; j++, p -= 4)

            for (int i = i1; i <= i2; i++)

                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;

    }

    return result;

}
