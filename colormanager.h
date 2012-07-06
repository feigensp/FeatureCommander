#ifndef COLORMANAGER_H
#define COLORMANAGER_H

#include "color.h"
#include <QtGui>
#include <QColor>
#include "feature.h"
#include <QMap>
#include <vector>
#include <iostream>
#include <map>


struct FeatureColorPair{
    Feature *feature;
    Color *color;

    FeatureColorPair(Feature *f, Color *c){
        this->feature = f;
        this->color = c;
    }

    bool operator==(FeatureColorPair p){
        return ((this->feature == p.feature) && (this->color == p.color));
    }

};

class ColorManager
{

public:
    static ColorManager* aktColormanager;
    QList <Color*> *colorArray;

    enum Colors{RED,ORANGE,YELLOW,BLUE,GREEN,PINK,MAGENTA,VIOLET,GREY};
    ColorManager(vector <Feature> *fList, int colorCount);
    ColorManager();
    ~ColorManager();

    //Color createColor(QColor color);
    //Color createColor(QString name = QString("NoName"));

    void setFeatureList(vector <Feature> * FList);
    vector <Feature>* getFeatureList();

    //gibt an, ob sich Paar p in der Feature-Color-Pair-List befindet
    bool FCPListContainsPair(FeatureColorPair *p);
    //gibt an, ob sich Color c in der Feature-Color-Pair-List befindet
    bool FCPListContainsColor(Color *c);

    //gibt Position in der Liste an, an der sich Paar mit Feature f befindet
    int FCPListContainsFeature(Feature *f);

    //gibt Farbe zurück, die Feature f zugeordnet ist
    Color* getColorForFeature(Feature *f);
    //setzt Farbe c für Feature f
    bool setColorForFeature(Feature *f, Color *c);
    //löscht Farbe des Features f: setzt sie auf einen der beiden default Grauwerte
    bool deleteColorForFeature(Feature *f);

    //gibt Feature zurück, dass einer Farbe c zugeordnet ist
    Feature* getFeatureForColor(Color *c);

    void setMaxColorCount(int i);
    int getMaxColorCount();

    //Methode erstellt eine Liste hierarchischer Kinderfarben zu c
    //dabei wird der value von hsv verändert
    //vector <Color>* getHierarchicalColorList(QColor c, int colorCount);

    //füllt das Array mit den zur Verfügung stehenden Farben mit n automatisch erzeugten Farben
    void fillColorArray(int n);
    //vector <Color>* fillHierarchicalColorList(int n, double start, double end,vector <Color> *hierarchy);
    //Feature-Color-Pair-List wird initialisiert:
    //jedem Feature wird einer der beiden default-Grauwerte zugewiesen
    void initializeFCPList();
    vector <Feature> *featureList;
    vector <FeatureColorPair> *FCPList;

private:
    Color *defaultGrey1;
    Color *defaultGrey2;
    Color *white;

    //Anzahl der Farben, die maximal zur Verfügung stehen sollen
    int maxColorCount;

    int dummyToDoMod2;


};

#endif // COLORMANAGER_H
