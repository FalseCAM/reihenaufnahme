/*
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "rename.h"
#include "widget.h"

Rename::Rename()
{
    widget = 0;
}

Rename::~Rename()
{
    if(this->widget)
        delete this->widget;
}

QString Rename::getName(){
    return QString("rename");
}

QString Rename::getTitle(){
    return QString(tr("Rename"));
}

QString Rename::getVersion(){
    return QString("0.1");
}

QString Rename::getAuthor(){
    return QString("FalseCAM");
}

QString Rename::getDescription(){
    return QString(tr("Plugin to rename images"));
}

QIcon Rename::getIcon(){
    return QIcon(":/plugins/rename/rename");
}

QWidget *Rename::getWidget(){
    if(!this->widget){
        this->widget = new Widget();
    }
    return this->widget;
}

void Rename::edit(Image *image){

    QString fileName = image->getName();
    if(widget->isRename() && widget->isNewName()){
        fileName = widget->getNewName();
    }
    if(widget->isRename() && !(widget->getPrefix().isEmpty() && widget->getSuffix().isEmpty())){
        fileName.prepend(widget->getPrefix());
        fileName.append(widget->getSuffix());

        if(widget->isCounter())
            fileName.append(QString("%1").arg(widget->getCounterStart()+image->getIndex(), widget->getCounterDecimals(), 10, QChar('0')) );
    }
    image->setName(fileName);

}
