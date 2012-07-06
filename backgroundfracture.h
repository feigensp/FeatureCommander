#ifndef BACKGROUNDFRACTURE_H
#define BACKGROUNDFRACTURE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "feature.h"
#include "featuretreewidget.h"
class BackgroundFracture : public QGraphicsRectItem
{
public:
    BackgroundFracture(FeatureTreeWidget *t,QColor c,Feature *f,int scenePosX, int scenePosY,int x, int y, int w, int h, QGraphicsScene *s);
    void setColor(int opacity);
    Feature* getFeature();
    void setSideBarColor(QColor c);
    void dropEvent (QGraphicsSceneDragDropEvent *event);
    void dragEnterEvent ( QGraphicsSceneDragDropEvent * event );
//    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
private:
    Feature *feature;
    QColor color;
    FeatureTreeWidget *featureTree;

};

#endif // BACKGROUNDFRACTURE_H
