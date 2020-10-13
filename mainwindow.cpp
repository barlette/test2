#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filedownloader.h"
#include "location.h"

#include <QtConcurrent/QtConcurrent>
#include <QWebEngineView>
#include <QObject>
#include <QLineEdit>
#include <QToolBar>
#include <QFileInfo>
#include <QDebug>
#include <QtWidgets>
#include <QThread>

#define WIDTH  950
#define HEIGHT 620
#define DEF_LOC "defaultLocation"

void MainWindow::setDefaultButton(){
    loc->setDefaultLocation(locationEdit->text());
}

void MainWindow::refreshView(){
    QUrl url = loc->changeLocation(locationEdit->text());
    view->load(url);
    view->setFocus();
}

/*void MainWindow::downloadHtml(){
    QString fileName = "def-loc.html";

    QString def_loc = "http://wttr.in/" + getDefaultLocation();

    file = new QFile;
    file->setFileName(fileName);
    file->open(QIODevice::WriteOnly);

    if(!file->isOpen()){
        return;
    }

    manager = new QNetworkAccessManager;
    QNetworkRequest request;

    request.setUrl(QUrl(def_loc));
    reply = manager->get(request);

    file->write(reply-)
    file->close();
}*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
    view = new QWebEngineView(this);
    QString def_loc = "http://wttr.in/" + loc->getDefaultLocation();
    view->load(QUrl(def_loc));
    view->resize(WIDTH,HEIGHT);
    this->resize(WIDTH,HEIGHT);

    locationEdit = new QLineEdit(this);
    locationEdit->setSizePolicy(QSizePolicy::Expanding, locationEdit->sizePolicy().verticalPolicy());
    //QObject::connect(locationEdit, &QLineEdit::returnPressed, this, &MainWindow::changeLocation);
    QObject::connect(locationEdit, &QLineEdit::returnPressed, this, &MainWindow::refreshView);

    QPushButton *defLoc_button = new QPushButton(this);
    defLoc_button->setText("Set as default location");

    QObject::connect(defLoc_button, SIGNAL(clicked()), this, SLOT(setDefaultButton()));

    QToolBar *toolbar = addToolBar(tr("Navigation"));
    toolbar->addWidget(locationEdit);
    toolbar->addWidget(defLoc_button);


    /*FileDownloader htmlDownloader;
    QThread updateFile;

    QThread::currentThread()->setObjectName("Main Thread");

    updateFile.setObjectName("updateFile");
    QObject::connect(&updateFile, SIGNAL(started()), &htmlDownloader, SLOT(checkLatest()));
    QObject::connect(&updateFile, SIGNAL(finished()), &htmlDownloader, SLOT(checkLatest()));

    htmlDownloader.moveToThread(&updateFile);
    updateFile.start();*/

    //QFuture<void> future = QtConcurrent::run(htmlDownloader->checkLatest());
    //QtConcurrent::run()
    view->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

