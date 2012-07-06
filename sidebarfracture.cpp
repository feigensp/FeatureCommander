#include "sidebarfracture.h"

SideBarFracture::SideBarFracture(FeatureTreeWidget *t,Feature *f,int scenePosX, int scenePosY,int x, int y, int w, int h, QGraphicsScene *s, int l, QString name)
{
    //Variablen zuweisen
    featureTree = t;
    scene = s;
    setRect(x,y,w,h);
    setPos(scenePosX,scenePosY);
    scene->addItem(this);
    feature = f;
    length = l;
    setZValue(length);
    completeName = name;
    indentation = 0;
    bgFracture = 0;

    //DropEnable
    if (featureTree != 0)
        setAcceptDrops(true);

    //Farbe zuweisen
    setColor();
    indent();
    if (feature!=0){
        if (completeName == "")
            setToolTip(feature->getName());
        else{
            QString formatedName = completeName;
            formatedName.insert(0,"<p>");
            formatedName.insert(formatedName.indexOf(feature->getName()),"<b>");
            formatedName.insert(formatedName.indexOf(feature->getName())+feature->getName().length(),"</b>");
            formatedName.insert(formatedName.length(),"</p>");
            setToolTip(formatedName);

            QString iconString = "";
            if (completeName.contains("!"))
                iconString += "!";
            if (completeName.contains("&"))
                iconString += "&";
            if (completeName.contains(QRegExp("[<>]")))
                iconString += ">";
            if (completeName.contains("|"))
                iconString += "|";
            if (iconString != ""){
                QGraphicsTextItem *textItem = new QGraphicsTextItem(iconString);
                textItem->setParentItem(this);
                textItem->setPos(this->rect().topRight());
                //andere Icons an selber Stelle löschen
                QList <QGraphicsItem*> list = scene->items(0,textItem->parentItem()->mapToScene(textItem->y(),0).y(),
                                                           scene->width(),20,Qt::IntersectsItemBoundingRect);
                for (int i = 0 ; i < list.size();i++){
                    if (list.at(i)->parentItem() != 0 && list.at(i)!=textItem){
                        scene->removeItem(list.at(i));
                        list.at(i)->setParentItem(0);
                    }
                }

            }
        }
    }

}

void SideBarFracture::setColor(){
    //Farbe zuweisen
    if (feature!=0){
        QColor color = feature->getColor()->getColor();
        if (color == QColor(220, 220, 220, 255) || color == QColor(180, 180, 180, 255)){
            if (indentation % 2 == 0)
                color = QColor(220, 220, 220, 255);
            else
                color = QColor(180, 180, 180, 255);
        }
        setBrush(QBrush(color,Qt::SolidPattern));
        setPen(QPen(color));
        if (bgFracture != 0)
            bgFracture->setSideBarColor(color);
    }
}

void SideBarFracture::setBGFracture(BackgroundFracture *bg){
    bgFracture = bg;
}

void SideBarFracture::indent(){
    //Fractures je nach Startpunkt einrücken
    QList <QGraphicsItem*> colliding = collidingItems(Qt::IntersectsItemBoundingRect);
    int x = pos().x();
    int width = rect().width();
    for (int i = 0; i < colliding.size(); i++){
        SideBarFracture *container = static_cast <SideBarFracture*>(colliding.at(i));
        //rootItem, dass immer kollidiert ausschließen
        if (container->rect().width() < 20){

            if (container->pos().y() < pos().y()){
//                if ((container->pos().x()+width+2+container->rect().width() < scene->views().at(0)->width()) && container != root && this != root)
//                    scene->views().at(0)->setFixedWidth(scene->views().at(0)->width() + width + container->rect().width() + 2);
                setX(container->pos().x() + container->rect().width() + 2);
                indentation++;
                indent();
            }else{
//                if ((x+width+2+container->rect().width() < scene->views().at(0)->width()) && container != root && this != root)
//                    scene->views().at(0)->setFixedWidth(scene->views().at(0)->width() + width + container->rect().width() + 2);
                container->setX(x + width + 2);
                container->indent();
                container->indentation++;
            }
        }
    }
}

void SideBarFracture::setFeature(Feature *f){
    feature = f;
}

Feature *SideBarFracture::getFeature(){
    return feature;
}

void SideBarFracture::setLength(int l){
    length = l;
}

int SideBarFracture::getLength(){
    return length;
}

void SideBarFracture::addChildItems(){
    int origWidth = rect().width();
    int origXPos = pos().x();
    setRect(0,0,scene->views().at(0)->width(),rect().height());
    setX(0);
    QList <QGraphicsItem*> colliding = collidingItems(Qt::ContainsItemBoundingRect);
    for (int i = 0; i < colliding.size(); i++){
        SideBarFracture *container = static_cast <SideBarFracture*>(colliding.at(i));        
        if(parentItem()==0){
            container->setBrush(QBrush(QColor(100,200,255,100),Qt::SolidPattern));
            container->setPen(QPen(QColor(100,200,255,100)));
            setParentItem(container);
        }

    }
//    setRect(0,0,origWidth,rect().height());
//    setX(origXPos);
}

void SideBarFracture::mousePressEvent(QGraphicsSceneMouseEvent  *event){
    scene->views().at(0)->centerOn(mapToScene(rect().topLeft()));
    QTreeWidgetItem *item = featureTree->getItemFromFeatureName(feature->getName());
    featureTree->scrollToItem(item);
    featureTree->unselect();
    item->setSelected(true);

    QGraphicsItem::mousePressEvent(event);
}

void SideBarFracture::dropEvent (QGraphicsSceneDragDropEvent *event){

    if (feature!=0 && featureTree !=0)
        featureTree->assignColorFromSMVTreeWidget(feature->getName());
    event->ignore();
}

void SideBarFracture::dragEnterEvent ( QGraphicsSceneDragDropEvent * event ){
    event->setAccepted(!event->mimeData()->hasFormat("text/plain"));
}

