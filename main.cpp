#include "mainwindow.h"
#include <QThread>
#include "filedownloader.h"

#include <QApplication>
//#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QtWebEngine::initialize();

    FileDownloader htmlDownloader;

    //htmlDownloader.downloadFile(QUrl("http://www.wttr.in/Lajeado"),"1");

    QThread updateFile;

    QThread::currentThread()->setObjectName("Main Thread");

    updateFile.setObjectName("updateFile");
    QObject::connect(&updateFile, SIGNAL(started()), &htmlDownloader, SLOT(checkLatest()));
    QObject::connect(&updateFile, SIGNAL(finished()), &a, SLOT(quit()));

    htmlDownloader.moveToThread(&updateFile);
    updateFile.start();






    MainWindow w;
    w.show();
    return a.exec();
}
