#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "location.h"
#include <QMainWindow>
#include <QWebEngineView>
#include <QObject>
#include <QLineEdit>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    //void downloadHtml();
    //QString getDefaultLocation();
    //void changeLocation();
    void setDefaultButton();
    void refreshView();
private:
    Ui::MainWindow *ui;
    QWebEngineView *view;
    QLineEdit *locationEdit;
    //QString new_location;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QFile *file;
    Location *loc;
};
#endif // MAINWINDOW_H
