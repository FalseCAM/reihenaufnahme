/*
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "savefile.h"
#include <QProxyStyle>
#include <QDir>

SaveFile::SaveFile()
{
    this->widget = 0;
}

SaveFile::~SaveFile()
{
}

QString SaveFile::getName(){
    return QString("savefile");
}

QString SaveFile::getTitle(){
    return QString(tr("Save File"));
}

QString SaveFile::getVersion(){
    return QString("1.0");
}

QString SaveFile::getAuthor(){
    return QString("FalseCAM");
}

QString SaveFile::getDescription(){
    return QString(tr("Plugin to save images to desktop."));
}

QIcon SaveFile::getIcon(){
    QProxyStyle s;
    return s.standardIcon (QStyle::SP_FileDialogNewFolder);
}

QWidget *SaveFile::getWidget(){
    if(!widget){
        widget = new Widget();
    }
    return widget;
}

void SaveFile::out(Image *image){
    getWidget();
    QString folder = this->widget->getFolder();
    folder.append("/");
    folder.append(image->getAlbum());
    folder.append("/");
    QString file = folder + image->getName() + "." + widget->getImageFormat();
    if(!QDir(folder).exists()){
        QDir().mkdir(folder);
    }
    qDebug("%s", qPrintable(file));
    if(!(widget->getImageQuality() == 0)){
        image->getImage()->save(file, qPrintable(widget->getImageFormat()), widget->getImageQuality());
    } else {
        image->getImage()->save(file, qPrintable(widget->getImageFormat()));
    }
    if(widget->getCopyMetaData()){
        saveExifData(image->getExifData(), file);
    }
}

// Saves Exifdata to given file
void SaveFile::saveExifData(Exiv2::ExifData *exifData, QString file){
    try {
        Exiv2::Image::AutoPtr destImage = Exiv2::ImageFactory::open(
                    file.toStdString().c_str());
        destImage->setExifData(*exifData);
        destImage->writeMetadata();
    } catch (Exiv2::Error& e) {
        qCritical("[SaveFile] %s", e.what());
    }
}

void SaveFile::finnish(){

}
