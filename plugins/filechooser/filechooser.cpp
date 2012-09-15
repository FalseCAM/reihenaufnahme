/*
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "filechooser.h"
#include "widget.h"
#include <QProxyStyle>
#include <QFileInfo>
#include <QDir>

FileChooser::FileChooser()
{
    this->widget = 0;
    has_next = false;
}

FileChooser::~FileChooser()
{
}

QString FileChooser::getName(){
    return QString("filechooser");
}

QString FileChooser::getTitle(){
    return QString(tr("Filechooser"));
}

QString FileChooser::getVersion(){
    return QString("1.0");
}

QString FileChooser::getAuthor(){
    return QString("FalseCAM");
}

QString FileChooser::getDescription(){
    return QString(tr("Plugin to load images from desktop."));
}

QIcon FileChooser::getIcon(){
    QProxyStyle s;
    return s.standardIcon (QStyle::SP_FileIcon);
}

QWidget *FileChooser::getWidget(){
    if(!widget){
        widget = new Widget();
    }
    return widget;
}

void FileChooser::init(){
    this->files = widget->getFiles();
    this->position = 0;

    if(!(position >= files.size())){
        has_next = true;
    } else {
        has_next = false;
    }
}

bool FileChooser::hasNext(){
    return has_next;
}

Image *FileChooser::next(){
    if(has_next){
        QString file = this->files.at(this->position);
        QImage *image = new QImage(file);
        QString album = getFolder(file);
        QString name = getName(file);
        position++;
        if(position >= this->files.size()){
            has_next = false;
        }
        Image *img = new Image(image, album, name, position - 1);
        img->setExifData(readExifData(file));
        return img;
    }

    return 0;
}

int FileChooser::getProgress(){
    int progress = 0;
    if(files.size()>0)
        progress = 100 * position / files.size();
    return progress;
}

QString FileChooser::getName(QString file){
    QString name;
    name = QFileInfo(file).baseName();
    return name;
}

QString FileChooser::getFolder(QString file){
    QString folder;
    folder = QDir(QFileInfo(file).absoluteDir()).dirName();
    return folder;
}

// Reads metadata from given file
Exiv2::ExifData *FileChooser::readExifData(QString file){
    try{
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(
                    file.toStdString().c_str());
        image->readMetadata();
        Exiv2::ExifData *data = new Exiv2::ExifData();
        *data = image->exifData();
        return data;
    } catch (Exiv2::Error& e) {
        qCritical("[Filechooser] %s", e.what());
        return 0;
    }
}
