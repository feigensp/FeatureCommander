#include "backgroundfracture.h"

BackgroundFracture::BackgroundFracture(FeatureTreeWidget *t,QColor c, Feature *f,int scenePosX, int scenePosY,int x, int y, int w, int h, QGraphicsScene *s)
{
    feature = f;
    setRect(x,y,w,h);
    setPos(scenePosX,scenePosY);
    s->addItem(this);
    color = c;
    featureTree = t;
    setColor(255);

    setFlag(QGraphicsItem::ItemIsSelectable,false);
    setFlag(QGraphicsItem::ItemIsMovable,false);
    setFlag(QGraphicsItem::ItemIsFocusable,false);

    if (featureTree!=0)
        setAcceptDrops(true);

}

void BackgroundFracture::setColor(int opacity){
    //Farbe zuweisen
    if (feature!=0 && color.isValid()){
        color.setAlpha(opacity);
        setBrush(QBrush(color,Qt::SolidPattern));
        setPen(QPen(color));
    }
}

void BackgroundFracture::setSideBarColor(QColor c){
    color = c;
}

Feature* BackgroundFracture::getFeature(){
    return feature;
}

void BackgroundFracture::dropEvent(QGraphicsSceneDragDropEvent *event){

    if (feature!=0 && featureTree !=0)
        featureTree->assignColorFromSMVTreeWidget(feature->getName());
    event->ignore();
}

void BackgroundFracture::dragEnterEvent ( QGraphicsSceneDragDropEvent * event ){
    event->setAccepted(!event->mimeData()->hasFormat("text/plain"));
}

//void BackgroundFracture::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
//
//    QMenu menu;
//    QAction *removeAction = menu.addAction("Remove ColorAssignment");
//    menu.show();
////    QMenu *menu = new QMenu(t);
////    MyTreeWidgetItem *item = static_cast<MyTreeWidgetItem*>(t->itemAt(p));
////    if (item->getBGColor()->getColor().isValid()){
////        QAction *actionDeleteColor = new QAction(QIcon(QPixmap(QString(":/images/cross.png"))),QString("remove ColorAssignment"),menu);
////        lastSelectedTreeWidgetItem = t->itemAt(p);
////        menu->addAction(actionDeleteColor);
////        connect(actionDeleteColor,SIGNAL(triggered()),this,SLOT(removeColorAssignment()));
////    }
////    QAction *actionAssignColor = new QAction(QIcon(QPixmap(QString(":/images/spectrum_small.png"))),QString("assign Color"),menu);
////    lastSelectedTreeWidgetItem = t->itemAt(p);
////    menu->addAction(actionAssignColor);
////    t->unselect();
////    item->setSelected(true);
////    connect(actionAssignColor,SIGNAL(triggered()),t,SLOT(assignAutomatically()));
////    menu->exec(t->mapToGlobal(p));
////    menu->show();
//
//
//}
