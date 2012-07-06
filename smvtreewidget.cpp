#include "smvtreewidget.h"
#include <iostream>
#include "mainwindow.h"


SMVTreeWidget::SMVTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    colorManager = new ColorManager();
    isFeatureView = false;

    connect(this, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(openFile(QTreeWidgetItem*,int)));
    connect(this,SIGNAL(itemExpanded(QTreeWidgetItem*)),this,SLOT(updateTexture()));
    ItemDelegate *delegate = new ItemDelegate(this, true);
    setItemDelegate(delegate);

//    connect(this,SIGNAL(entered(QModelIndex)),this,SLOT(hoverEnter(QModelIndex)));
//    connect(this,SIGNAL(expanded(QModelIndex)),this,SLOT(resizeRowHeight(QModelIndex)));
//    connect(this,SIGNAL(collapsed(QModelIndex)),this,SLOT(resizeRowHeight(QModelIndex)));

}
/*
SMVTreeWidget::SMVTreeWidget(SMVTreeWidget *tree){
    this

    this->invisibleRootItem() = tree->invisibleRootItem();

    for (int i=0; i<tree->invisibleRootItem()->childCount(); i++){
        copyNode(tree->invisibleRootItem()->child(i), this->invisibleRootItem());
    }

}
*/

void SMVTreeWidget::setFeatureTreeWidget(FeatureTreeWidget *f){
    featureTreeWidget = f;

}

void SMVTreeWidget::setColorManager(ColorManager *cm){
    colorManager = cm;
}

ColorManager* SMVTreeWidget::getColorManager(){
    return colorManager;
}

//void SMVTreeWidget::setMainWindow(MainWindow *mw){
//    mainWindow = mw;
//}
//
//MainWindow* SMVTreeWidget::getMainWindow(){
//    return mainWindow;
//}

void SMVTreeWidget::copyTree(STNode *rootOrigTree, STNode *rootCopyTree){
    int childCount = rootOrigTree->childCount();
    for(int i=0; i<rootOrigTree->childCount(); i++){
        QString orig = rootOrigTree->text(0);
        STNode *copy = new STNode ( *(reinterpret_cast<STNode*>(rootOrigTree->child(i))), true );
        rootCopyTree->addChild(copy);

        if (rootOrigTree->childCount()!=0){
            copyTree(static_cast <STNode*>(rootOrigTree->child(i)), copy);
        }
    }


//    QTreeWidgetItemIterator it(rootCopyTree,QTreeWidgetItemIterator::All);
//    while(*it){
//        STNode *currentNode = static_cast<STNode*>((*it));
//        STNode *copy = new STNode ( *(reinterpret_cast<STNode*>(currentNode->child(i))), true );
//
//        ++it;
//    }

}

void SMVTreeWidget::copyTree1(SMVTreeWidget *copy){
    copy = new SMVTreeWidget();
    for (int i=0; i<this->invisibleRootItem()->childCount(); i++){
        copyNode(static_cast <STNode*>(this->invisibleRootItem()->child(i)), static_cast <STNode*>(copy->invisibleRootItem()));
    }
}

//, STNode *copy
void SMVTreeWidget::copyNode(STNode *original, STNode *copyNodesParent){
    QString t = original->text(0);
    STNode *copy = new STNode(copyNodesParent);
    copy = original;
    int anz = original->childCount();
    for(int i=0; i<original->childCount(); i++){
        if(original->childCount()!=0){
            copyNode(static_cast <STNode*>(original->child(i)), copy);
        }
    }
}

void SMVTreeWidget::openFile(QTreeWidgetItem *item, int i){

   MainWindow::myMainWindow->updateTextEditFileNode(static_cast <STNode*>(item));
   // this->getMainWindow()->updateTextEditFileNode(static_cast <STNode*>(item));
}

void SMVTreeWidget::resize(int width, int height){

    if (height == 0)
        height = 29;
    if (isFeatureView)
        height = 29;
    double start = (double) width/250;
    double widthWithoutWhiteSpace = ((double) width/300)*212;//(Breite / Originalbreite)* OriginalBreiteOhneWeiﬂes

    QQueue<QTreeWidgetItem*> nodeQueue;
    for (int i = 0; i < invisibleRootItem()->childCount();i++){
        QTreeWidgetItem *item = invisibleRootItem()->child(i);
        nodeQueue.enqueue(item);
        while (!nodeQueue.isEmpty()){
            STNode *currentNode = static_cast<STNode*>(nodeQueue.dequeue());

//            QFont font = QFont(currentNode->font(0));
//            font.setPointSize(10);
//            currentNode->setFont(0,font);

            QPixmap pix = currentNode->backgroundSave.copy(0,0,currentNode->backgroundSave.width(),50).scaled(width,height,Qt::IgnoreAspectRatio,Qt::FastTransformation);
            QPainter painter(&pix);

            painter.fillRect(0,0,width,3,Qt::white);
            painter.fillRect(0,height-3,width,3,Qt::white);

            //einen grauen Rand
            painter.setPen(Qt::gray);
            QBrush brush(Qt::NoBrush);
            painter.setBrush(brush);
            painter.drawRect(start-2,2,widthWithoutWhiteSpace+1,height-5);
            painter.fillRect(start+widthWithoutWhiteSpace+1,0,width-widthWithoutWhiteSpace,height,Qt::white);

            QPixmap newPix = pix.copy(start-2,0,width,height);
            QBrush bg(newPix);
            currentNode->setBackground(0, bg);

            if (currentNode->isExpanded()){
                for (int i=0; i < currentNode->childCount(); i++){
                    nodeQueue.enqueue((currentNode->child(i)));
                }
            }
        }
    }
//        STNode *currentNode = static_cast <STNode*>(rootSTNode->child(0));
//        nodeQueue.enqueue(currentNode);
//
//        while (!nodeQueue.isEmpty()){
//            currentNode = nodeQueue.dequeue();
//
//            QString nodeName = currentNode->text(0);
//            QBrush brush (currentNode->drawBackgroundImagePackageView(width));
//            currentNode->setBackground(0, brush);
//            currentNode->backgroundSave = currentNode->background(0).texture();
//            int childCount = currentNode->childCount();
//            for (int i=0; i<childCount; i++){
//                nodeQueue.enqueue(static_cast <STNode*> (currentNode->child(i)));
//            }
//        }
//    while (*it) {
//
//        double start = (double) width/200;
//        double widthWithoutWhiteSpace = ((double) width/200)*100;//(Breite / Originalbreite)* OriginalBreiteOhneWeiﬂes
//        QPixmap pix = static_cast<STNode*>(*it)->backgroundSave.scaled(width,26,Qt::IgnoreAspectRatio,Qt::FastTransformation);
//        QPainter painter(&pix);
//
//        //einen schwarzen Rand
//        painter.setPen(Qt::black);
//        QBrush brush(Qt::NoBrush);
//        painter.setBrush(brush);
//        painter.drawRect(start,0,widthWithoutWhiteSpace,15);
//        QPixmap newPix = pix.copy(start,0,width,26);
//
//
//        QBrush bg(newPix);
//        (*it)->setBackground(0, bg);
//        ++it;
//    }
}
//void SMVTreeWidget::expandItem ( const QTreeWidgetItem * item ){
//    resize(this->size().width());
//    QTreeWidget::expandItem (item);
//}

void SMVTreeWidget::updateTexture(){
    resize(this->size().width());
}

void SMVTreeWidget::resizeEvent(QResizeEvent *event){
    resize(event->size().width());
    QTreeWidget::resizeEvent(event);

}

void SMVTreeWidget::hoverEnter(QModelIndex index){
//    int height = 80;
//
//    ItemDelegate *delegate = static_cast<ItemDelegate*>(itemDelegate());
//    QTreeWidgetItemIterator it(this,QTreeWidgetItemIterator::All);
//    delegate->setRowHeight(40);
//    resize(size().width());
//    while(*it){
//        STNode *currentNode = static_cast<STNode*>((*it));
//        currentNode->setSizeHint(0,QSize(0,0));
//
//        ++it;
//    }
//    delegate->setRowHeight(height);
//    delegate->setHoverItem(&index);
//    itemFromIndex(index)->setSizeHint(0,QSize(0,0));
//    STNode *hover = static_cast<STNode*>(itemFromIndex(index));
//
//    QPixmap pix = hover->backgroundSave.copy(0,0,hover->backgroundSave.width(),50).scaled(size().width(),height,Qt::IgnoreAspectRatio,Qt::FastTransformation);
//    QPainter painter(&pix);
//
//    double start = (double) size().width()/200;
//    double widthWithoutWhiteSpace = ((double) size().width()/200)*100;//(Breite / Originalbreite)* OriginalBreiteOhneWeiﬂes
//
//    painter.fillRect(0,0,size().width(),3,Qt::white);
//    painter.fillRect(0,height-3,size().width(),3,Qt::white);
//
//    //einen schwarzen Rand
//    painter.setPen(Qt::black);
//    QBrush brush(Qt::NoBrush);
//    painter.setBrush(brush);
//    painter.drawRect(start,2,widthWithoutWhiteSpace,height-5);
//
//
//    QPixmap newPix = pix.copy(start,0,size().width(),height);
//    QBrush bg(newPix);
//    hover->setBackground(0, bg);
}

void SMVTreeWidget::resizeRowHeight(QModelIndex index){
//    ItemDelegate *delegate = static_cast<ItemDelegate*>(itemDelegate());
//    QTreeWidgetItemIterator it(this,QTreeWidgetItemIterator::All);
//    delegate->setRowHeight(40);
//    resize(size().width());
//    while(*it){
//        STNode *currentNode = static_cast<STNode*>((*it));
//        currentNode->setSizeHint(0,QSize(25,25));
//
//        ++it;
//    }
}

void SMVTreeWidget::leaveEvent(QEvent *event){

//    QTreeWidgetItemIterator it(this,QTreeWidgetItemIterator::All);
//    ItemDelegate *delegate = static_cast<ItemDelegate*>(itemDelegate());
//    delegate->setRowHeight(40);
//    while(*it){
//        STNode *currentNode = static_cast<STNode*>((*it));
//        currentNode->setSizeHint(0,QSize(25,25));
//        ++it;
//    }
//    resize(size().width());
    QTreeWidget::leaveEvent(event);
}

void SMVTreeWidget::dropEvent(QDropEvent *event)
{
    //Darstellen des Drag-Bildes
    QByteArray itemData = event->mimeData()->data("application/x-color");
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);
    QPixmap pixmap;
    QPoint offset;
    dataStream >> pixmap >> offset;

    QTreeWidgetItem *item = itemAt(event->pos().x(),event->pos().y());
    QString featureName = "";
    if (!item->parent())
        featureName = item->text(0);
    else{
        QTreeWidgetItem *pathItem = item;
        while(pathItem->parent()){
            if (!pathItem->parent()->parent()){
                featureName = pathItem->parent()->text(0);
            }
            pathItem = pathItem->parent();

        }
    }
    featureTreeWidget->assignColorFromSMVTreeWidget(featureName);
    event->ignore();

}



