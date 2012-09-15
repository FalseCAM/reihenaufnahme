/*
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "overlay.h"
#include "widget.h"

Overlay::Overlay()
{
    widget = 0;
}

Overlay::~Overlay()
{
    if(this->widget)
        delete this->widget;
}

QString Overlay::getName(){
    return QString("overlay");
}

QString Overlay::getTitle(){
    return QString(tr("Overlay"));
}

QString Overlay::getVersion(){
    return QString("0.1");
}

QString Overlay::getAuthor(){
    return QString("FalseCAM");
}

QString Overlay::getDescription(){
    return QString(tr("Plugin to overlay images"));
}

QIcon Overlay::getIcon(){
    return QIcon(":/plugins/overlay/overlay");
}

QWidget *Overlay::getWidget(){
    if(!this->widget){
        this->widget = new Widget();
    }
    return this->widget;
}

void Overlay::edit(Image *image){
    if(widget->isOverlay()){
        widget->addOverlay(image->getImage());
    }
}

//Q_EXPORT_PLUGIN2(overlay, Overlay);
