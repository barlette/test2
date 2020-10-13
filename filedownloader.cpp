#include "filedownloader.h"
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "location.h"
#include <QThread>

FileDownloader::FileDownloader(QObject *parent) :
    QObject(parent),
    webCtrl(new QNetworkAccessManager(this))
{
}

FileDownloader::~FileDownloader()
{
    delete webCtrl;
}

void FileDownloader::downloadFile(QUrl url, QString id)
{
    QString url_string = url.toString();
    //QString path = dir_absolute_path + url_string.right(url_string.size() - url_string.lastIndexOf("/"));

    QString path = "def-loc.html";

    QFile *file = new QFile(path, this);
    if(!file->open(QIODevice::WriteOnly))
    {
        return;
    }

    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", userAgent);

    QSslConfiguration sslConfiguration(QSslConfiguration::defaultConfiguration());
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfiguration.setProtocol(QSsl::AnyProtocol);
    request.setSslConfiguration(sslConfiguration);

    QNetworkReply *reply = webCtrl->get(request);
    replytofile.insert(reply, file);
    replytopathid.insert(reply, QPair<QString, QString>(path, id));

    //QEventLoop loop;
    //connect(reply, SIGNAL(finished()), &loop, &FileDownloader::fileDownloaded);
    QObject::connect(reply, &QNetworkReply::finished, this, &FileDownloader::fileDownloaded);
    QObject::connect(reply, &QNetworkReply::readyRead, this, &FileDownloader::onReadyRead);
}

void FileDownloader::fileDownloaded()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if (replytofile[reply]->isOpen())
    {
        replytofile[reply]->close();
        replytofile[reply]->deleteLater();
    }

    switch(reply->error())
    {
    case QNetworkReply::NoError:
        break;

    default:
        emit error(reply->errorString().toLatin1());
        break;
    }

    emit downloaded(replytopathid[reply].first, replytopathid[reply].second);

    replytofile.remove(reply);
    replytopathid.remove(reply);
    delete reply;
}

void FileDownloader::onReadyRead()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    replytofile[reply]->write(reply->readAll());
}

void FileDownloader::checkLatest(){

    QFile file("def-loc.html");
    QFileInfo fileInfo; fileInfo.setFile(file);
    QDateTime lMod = fileInfo.lastModified();
    QDateTime current;
    QString def_loc = "http://wttr.in/" + loc->getDefaultLocation();

    qDebug() << "Hello from: " << QThread::currentThread()->objectName();
    int hour = lMod.time().hour();
    qDebug() << hour;
    int minute = lMod.time().minute();
    qDebug() << "Entering while true!";
    qDebug() << loc->getDefaultLocation();
    while(true){
        qDebug() << "After 15 seconds!";
        /*if(hour < current.currentDateTime().time().hour()){
            def_loc = "http://wttr.in/" + loc->getDefaultLocation();
            downloadFile(def_loc, "1", QCoreApplication::applicationDirPath());
            lMod = fileInfo.lastModified();
            hour = lMod.time().hour();
            qDebug() << "Old file!";
        }
        QThread::sleep(15);*/
        if(minute < current.currentDateTime().time().minute()){
                    def_loc = "http://www.wttr.in/" + loc->getDefaultLocation();
                    qDebug() << def_loc;
                    downloadFile(QUrl(def_loc), "1");

                    minute = current.currentDateTime().time().minute();
                    qDebug() << "Old file!";
         }
        QThread::sleep(15);
    }


}
