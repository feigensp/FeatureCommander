#ifndef SIDEBARFRACTURE_H
#define SIDEBARFRACTURE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "feature.h"
#include <QGraphicsSceneDragDropEvent>
#include "featuretreewidget.h"
#include "backgroundfracture.h"


class SideBarFracture : public QGraphicsRectItem
{
public:
    SideBarFracture(FeatureTreeWidget *t,Feature *f,int scenePosX, int scenePosY, int x, int y, int w, int h, QGraphicsScene *s, int l,QString name);
    void setColor();
    void indent();
    void setFeature(Feature *f);
    void addChildItems();
    Feature *getFeature();
    void setLength(int l);
    int getLength();
    QString completeName;
    int indentation;
    void mousePressEvent(QGraphicsSceneMouseEvent  *event);
    void dropEvent (QGraphicsSceneDragDropEvent * event);
    void dragEnterEvent ( QGraphicsSceneDragDropEvent * event );
    void setBGFracture(BackgroundFracture *bg);
    
private:
    Feature *feature;
    int length;
    QGraphicsScene *scene;
    FeatureTreeWidget *featureTree;
    BackgroundFracture *bgFracture;


};

#endif // SIDEBARFRACTURE_H
