#ifndef LOCATION_H
#define LOCATION_H

#include <QWebEngineView>
#include <QObject>
#include <QLineEdit>
#include <QFile>

class Location
{
public:
    Location();
    ~Location();
    QString getDefaultLocation();
    QUrl changeLocation(QString new_location);
    void setDefaultLocation(QString new_location);
    QString new_location;
};

#endif // LOCATION_H
