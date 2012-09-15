/*
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "color.h"
#include "widget.h"
#include <QProxyStyle>

Color::Color()
{
    widget = 0;
}

Color::~Color()
{
    if(this->widget)
        delete this->widget;
}

QString Color::getName(){
    return QString("color");
}

QString Color::getTitle(){
    return QString(tr("Color"));
}

QString Color::getVersion(){
    return QString("0.1");
}

QString Color::getAuthor(){
    return QString("FalseCAM");
}

QString Color::getDescription(){
    return QString(tr("Plugin to invert color or grayscale image"));
}

QIcon Color::getIcon(){
    return QIcon(":/plugins/color/color");
}

QWidget *Color::getWidget(){
    if(!this->widget){
        this->widget = new Widget();
    }
    return this->widget;
}

void Color::edit(Image *img){
    QImage * image = img->getImage();

        if(widget->isGrayscale()){
            grayscale(image);
        }
        if(widget->isInvert()){
            image->invertPixels();
        }
        if(widget->isSwap()){
            *image = image->rgbSwapped();
        }
        if(widget->isSepia()){
            sepia(image);
        }
}

void Color::grayscale(QImage *image){

    // Code from http://docs.huihoo.com/qt/4.7/tools-plugandpaintplugins-basictools.html

    for (int y = 0; y < image->height(); ++y) {
        for (int x = 0; x < image->width(); ++x) {
            int pixel = image->pixel(x, y);
            int gray = qGray(pixel);
            int alpha = qAlpha(pixel);
            image->setPixel(x, y, qRgba(gray, gray, gray, alpha));
        }
    }
}

void Color::sepia(QImage *image){

    // Code from http://docs.huihoo.com/qt/4.7/tools-plugandpaintplugins-basictools.html

    //compute the hsl/hsv coordinates of sepia color
    int sepiaH, sepiaS, sepiaL;
    QColor(162,128,101).getHsv( &sepiaH, &sepiaS, &sepiaL );


    //iterate over each selected scanline
    int x, y, pixelLuminance;
    QRgb* rgb;
    QColor sepiaColor;
    uchar* scanLine;

    for( y=0; y<image->height(); y++)
    {
        //iterate over each selected pixel in scanline
        scanLine = image->scanLine(y);
        for( x=0; x<image->width(); x++)
        {
            //compute gray value based on the display luminance of color coordinates
            rgb = ((QRgb*)scanLine+x);
            pixelLuminance = (int) (0.2125*qRed(*rgb) + 0.7154*qGreen(*rgb) + 0.0721*qBlue(*rgb));
            //compute and set sepia color
            sepiaColor.setHsv( sepiaH, sepiaS, pixelLuminance );
            *rgb = sepiaColor.rgb();
        }

    }
}
