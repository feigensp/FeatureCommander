#ifndef FEATURE_H
#define FEATURE_H

#include <QColor>
#include <QString>
#include "color.h"


using namespace std;

class Feature
{
public:
    Feature(QString name);
    ~Feature();
    QString getName();
    bool operator==(Feature *f);
    bool operator==(Feature &f);
    const bool operator<(Feature &f);

    //die folgenden drei methoden werden gelöscht, sobald der colormanager in betrieb ist
//    QRgb color;
//    void setColor(QRgb farbe);
    Color* getColor();
    int index;
    //Color* setColor(Color c);
    QString name;

private:
    //Color *color;
    //string comment;


};

#endif // FEATURE_H
