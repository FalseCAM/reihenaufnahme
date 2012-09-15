/*
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "rotate.h"
#include "widget.h"
#include <QMatrix>

Rotate::Rotate()
{
    widget = 0;
}

Rotate::~Rotate()
{
    if(this->widget)
        delete this->widget;
}

QString Rotate::getName(){
    return QString("rotate");
}

QString Rotate::getTitle(){
    return QString(tr("Rotate"));
}

QString Rotate::getVersion(){
    return QString("0.1");
}

QString Rotate::getAuthor(){
    return QString("FalseCAM");
}

QString Rotate::getDescription(){
    return QString(tr("Plugin to rotate images"));
}

QIcon Rotate::getIcon(){
    return QIcon(":/plugins/rotate/clockwise");
}

QWidget *Rotate::getWidget(){
    if(!this->widget){
        this->widget = new Widget();
    }
    return this->widget;
}

void Rotate::edit(Image *image){
    QMatrix m;
    if (widget->rotateClockwise())
        m.rotate(90.0);
    if (widget->rotateClockwise180())
        m.rotate(180.0);
    if (widget->rotateCounterClockwise())
        m.rotate(270.0);
    if (widget->rotateByAngle())
        m.rotate(widget->angle());
    // transform image
    image->setImage(new QImage(image->getImage()->transformed(m)));
}
