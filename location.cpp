#include "location.h"
#include <QWebEngineView>
#include <QObject>
#include <QLineEdit>
#include <QToolBar>
#include <QFileInfo>
#include <QDebug>
#include <QtWidgets>
#include <QString>

#define DEF_LOC "defaultLocation"

Location::Location()
{

}

QString Location::getDefaultLocation(){
    bool fileExists = QFileInfo::exists(DEF_LOC) && QFileInfo(DEF_LOC).isFile();
    QFile inFile(DEF_LOC);
    QString line;
    if (fileExists){
       QTextStream in(&inFile);

           if(inFile.open(QIODevice::ReadOnly)){
            line = in.readLine();
            inFile.close();
           }
            return line;
       } else {
            QString empty = QString();
            return empty;
        }
    return "0";
}

void Location::setDefaultLocation(QString new_location){
    bool fileExists = QFileInfo::exists(DEF_LOC) && QFileInfo(DEF_LOC).isFile();
    qDebug() << new_location;

    QFile inFile(DEF_LOC);
    if (fileExists){
        QFile::remove(DEF_LOC);
    }

    if(inFile.open(QIODevice::ReadWrite)){
        QTextStream in(&inFile);
        in << new_location;
        inFile.close();
    } else {
        qDebug() << "Error while trying to set default location!";
        exit(1);
    }
}

QUrl Location::changeLocation(QString new_location){
    QUrl url = QUrl("http://wttr.in/" + new_location);
    return url;
}
