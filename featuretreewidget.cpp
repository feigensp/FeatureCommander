
#include <QtGui>
#include <QListWidgetItem>
#include "mainwindow.h"
#include "featuretreewidget.h"
#include "main.cpp"
#include <vector>
#include "feature.h"
#include <iostream>
#include "colormanager.h"
using namespace std;

FeatureTreeWidget::FeatureTreeWidget(QWidget *parent,
                                     QFile *file,QListWidget *listWidget,ColorManager *colorManager, MainWindow *mw)
                                         : QTreeWidget(parent)
{
    this->colorManager = colorManager;
    this->listWidget = listWidget;
    mainWindow = mw;
    ItemDelegate *delegate = new ItemDelegate(this,false,mainWindow->checkBoxWidth);
    setItemDelegate(delegate);

    featureList = new vector <Feature>();
    setColumnCount(2);
    header()->setStretchLastSection(false);
    header()->setResizeMode(0,QHeaderView::Stretch);
    header()->setResizeMode(1,QHeaderView::ResizeToContents);
    setUniformRowHeights(true);
//    connect (this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(updateCheckboxes(QTreeWidgetItem*)));
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    file->open(QIODevice::ReadOnly);

    QString data = static_cast <QString>(file->readAll());
    file->close();

    data.remove('[');
    data.remove(']');
    data.remove("\n");
    data.remove("\r");
    data.remove("\t");
    data.remove(' ');

    //ohne Checkboxen
    QFlags<Qt::ItemFlag> flgChild = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;
    QFlags<Qt::ItemFlag> flgParent = Qt::ItemIsEnabled;
//    root = new MyTreeWidgetItem(QStringList(QString("empty")));
//    addTopLevelItem(root);
//    root->setFlags(flgParent);
    QStringList lines = data.split(QString(";"));
    for (int i = 0; i < lines.size(); i++){
        if (!static_cast<QString>(lines.at(i)).isEmpty()){
            QStringList line = static_cast<QString>(lines.at(i)).split(QRegExp(":{1}"));

            QString par = static_cast<QString>(line.first());
            MyTreeWidgetItem *parent = new MyTreeWidgetItem(QStringList(par));

            //Suche nach schon vorhandenem Item
            QTreeWidgetItemIterator it (this,QTreeWidgetItemIterator::All);
            bool found = false;
            while(*it){
                if ((*it)->text(0) == par){
                    parent = static_cast<MyTreeWidgetItem*>(*it);
                    found = true;
                    break;
                }
                ++it;
            }
            if (!found)
                addTopLevelItem(parent);
            parent->setFlags(flgParent);
            if (line.size() > 1){
                QStringList children = static_cast<QString>(line.at(1)).split('|');
                for (int j = 0; j < children.size(); j++){
                    MyTreeWidgetItem *child = new MyTreeWidgetItem(QStringList(static_cast<QString>(children.at(j))));
                    parent->addChild(child);
                    child->setFlags(flgChild);
                }
            }
        }
    }
    if (topLevelItemCount() > 0)
        root = topLevelItem(0);
    else{
        root = new MyTreeWidgetItem(QStringList(QString("empty")));
        addTopLevelItem(root);
    }


//    QRegExp rx("[A-Z|a-z|_]:");
//    int found = data.indexOf(rx,0);
//    while (found != -1){
//        data.replace(found+1,1," :");
//        found = data.indexOf(rx,found+2);
//    }
//
//    //Flags, die für jeden erstellten Knoten gesetzt werden müssen -> Checkboxen!
////    QFlags<Qt::ItemFlag> flgChild = Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;
////    QFlags<Qt::ItemFlag> flgParent = Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
//    //ohne Checkboxen
//    QFlags<Qt::ItemFlag> flgChild = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;
//    QFlags<Qt::ItemFlag> flgParent = Qt::ItemIsEnabled;
//    root = new MyTreeWidgetItem(QStringList(QString("empty")));
//    addTopLevelItem(root);
//    root->setFlags(flgParent);
////    root->setCheckState(0,Qt::Checked);
//    QStringList lines = data.split(QString(";"));
//
//    //jede Zeile in einzelne Knoten zerlegen
//    //toDo: in Methoden auslagern
//    for (int i=0; i<lines.size();i++)
//    {
//        QString line = static_cast<QString>(lines.at(i));
//        if (!line.startsWith("\n")){
//            QString node;
//            QString rest;
//            QStringList splitLine = line.split(QString(" : "));
//            if (splitLine.size()==2){
//                node = static_cast<QString>(splitLine.at(0));
//                rest = static_cast<QString>(splitLine.at(1));
//            }
//            else break;
//            //mittleren Teil (die Kindknoten) in einzelne Knoten zerlegen
//            QStringList splitRest1 = rest.split(QString("::"));
//            QStringList splitRest = QStringList();
//            for (int i = 0; i < splitRest1.size();i++){
//                QString deleteSpaces = splitRest1.at(i);
//                if (deleteSpaces.startsWith(" "))
//                    deleteSpaces.remove(0,1);
//                if (deleteSpaces.endsWith(" "))
//                    deleteSpaces.remove(deleteSpaces.length(),1);
//                splitRest.push_back(deleteSpaces);
//            }
//            QStringList children = splitRest.at(0).split(QString(" "));
//
//            //wenn Baum noch leer, füge Kinder dem Wurzelknoten hinzu
//            if (root->childCount()==0){
//                root->setText(0,node);
//                //Fall: "Feature : Kinder des Unterfeatures :: Unterfeature"
//                if (splitRest.size() == 2){
//                    if (!splitRest.at(1).startsWith(QString("_"))){
//                        MyTreeWidgetItem *newItem = new MyTreeWidgetItem(QStringList(splitRest.at(1)));
//                        newItem->setFlags(flgParent);
////                        newItem->setCheckState(0,Qt::Checked);
//                        root->addChild(newItem);
//
//                        addChildren(root->child(0),children);
//                    }
//                }
//                //Normalfall: "Feature : Featurekinder :: _Feature"
//                if (splitRest.size() > 1){
//                    if (splitRest.at(1).startsWith(QString("_"))){
//                        addChildren(root,children);
//                    }
//                }
//                //Fall: "Feature : Kinder des Unterfeatures :: Unterfeature
//                //  | Kinder des zweiten Unterfeatures :: zweites Unterfeature ..."
//                if (splitRest.size() > 2){
//                    for (int i = 1;i < splitRest.size();i+=2){
//                        QStringList splitString = splitRest.at(i).split(QString("|"));
//                        MyTreeWidgetItem *newItem = new MyTreeWidgetItem(QStringList(splitString.at(0)));
//                        newItem->setFlags(flgParent);
////                        newItem->setCheckState(0,Qt::Checked);
//                        root->addChild(newItem);
//                        addChildren(root->child(0),children);
//                        children = splitString.at(1).split(QString(" "));
//                    }
//                }
//            }
//            //ansonsten suche nach schon vorhandenem Elternknoten und füge Kinder hinzu
//            else{
//                MyTreeWidgetItem *item;
//                QTreeWidgetItem *itemExists;
//                node.remove(0,2);
//                //Fall: "Feature : Kinder des Unterfeatures :: Unterfeature"
//                if (splitRest.size() == 2){
//                    if (!splitRest.at(1).startsWith(QString("_")) && findTreeWidgetItem(root,node)!=0){
//                        item = new MyTreeWidgetItem(QStringList(splitRest.at(1)));
//                        item->setFlags(flgParent);
////                        item->setCheckState(0,Qt::Checked);
//                        findTreeWidgetItem(root,node)->addChild(item);
//                        addChildren(item,children);
//                    }
//                }
//                //Normalfall: "Feature : Featurekinder :: _Feature"
//                if (splitRest.size() > 1){
//                    if (splitRest.at(1).startsWith(QString("_")) && findTreeWidgetItem(root,node)!=0){
//                        itemExists = findTreeWidgetItem(root,node);
//                        itemExists->setFlags(flgParent);
////                        itemExists->setCheckState(0,Qt::Checked);
//                        addChildren(itemExists,children);
//                    }
//                }
//                //Fall: "Feature : Kinder des Unterfeatures :: Unterfeature
//                //  | Kinder des zweiten Unterfeatures :: zweites Unterfeature ..."
//                if (splitRest.size() > 2 && findTreeWidgetItem(root,node)!=0){
//                    for (int i = 1;i < splitRest.size();i++){
//                        QStringList splitString = splitRest.at(i).split(QString("|"));
//                        MyTreeWidgetItem *newItem = new MyTreeWidgetItem(QStringList(splitString.at(0)));
//                        newItem->setFlags(flgParent);
////                        newItem->setCheckState(0,Qt::Checked);
//                        findTreeWidgetItem(root,node)->addChild(newItem);
//                        addChildren(findTreeWidgetItem(root,node)->child(i-1),children);
//                        if (splitString.size() > 1)
//                            children = splitString.at(1).split(QString(" "));
//                    }
//                }
//            }
//        }
//    }

    expandAll();
    setIndentation(12);
    expandsOnDoubleClick();
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::DropOnly);
    setDefaultDropAction(Qt::TargetMoveAction);
    setAutoFillBackground(true);
    setHeaderHidden(true);

//weiß als Highlightfarbe (richtiges Highlighting wird in ItemDelegate ausgeführt)
    QPalette palette = this->palette();
    palette.setColor(QPalette::Highlight,Qt::white);
    this->setPalette(palette);
}

void FeatureTreeWidget::createFeatureList (){
    QTreeWidgetItemIterator it(this,QTreeWidgetItemIterator::NoChildren);
    int featureIndex = 0;
    while (*it) {
        Feature newFeature ((*it)->text(0));
        newFeature.index = featureIndex;
        featureList->push_back(newFeature);
        featureIndex++;
        ++it;
    }
}

vector<Feature>* FeatureTreeWidget::getFeatureList(){
    return featureList;
}

void FeatureTreeWidget::addChildren(QTreeWidgetItem *item, QStringList children)
{
    //Flags, die für jeden erstellten Knoten gesetzt werden müssen -> Checkboxen!
//    QFlags<Qt::ItemFlag> flgChild = Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;
//    QFlags<Qt::ItemFlag> flgParent = Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
    //ohne Checkboxen
    QFlags<Qt::ItemFlag> flgChild = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;
    QFlags<Qt::ItemFlag> flgParent = Qt::ItemIsEnabled;

    item->setFlags(flgParent);
//    item->setCheckState(0,Qt::Checked);
    for (int j = 0;j < children.size();j++)
    {
        QString child = children.at(j);
        if (child.isEmpty()==false){
            MyTreeWidgetItem *newItem = new MyTreeWidgetItem(QStringList(children.at(j)));
            newItem->setFlags(flgChild);
//            newItem->setCheckState(0,Qt::Checked);
            item->addChild(newItem);
        }
    }
}

QTreeWidgetItem* FeatureTreeWidget::findTreeWidgetItem(QTreeWidgetItem *item, QString name)
{
    for (int i = 0; i<item->childCount();i++)
    {
        if (item->child(i)->text(0).compare(name)==0)
            return item->child(i);
        else if (item->childCount()!=0){
            if (findTreeWidgetItem(item->child(i),name)!=0)
                return findTreeWidgetItem(item->child(i),name);
        }
    }
    return 0;

}

void FeatureTreeWidget::updateCheckboxes(QTreeWidgetItem *item)
{
//    if (item->childCount()> 0)
//        updateChildrenCheckboxes(item);
//    if (item->parent())
//    {
//        if (item->parent()->childCount()==1)
//            item->parent()->setCheckState(0,item->checkState(0));
//        else{
//            bool partiallyChecked = false;
//            int checked = 0;
//            int unchecked = 0;
//            for (int i = 0; i < item->parent()->childCount();i++)
//            {
//                if (item->parent()->child(i)->checkState(0)==Qt::PartiallyChecked){
//                    i = item->parent()->childCount()-1;
//                    partiallyChecked = true;
//                }
//
//                else if (item->parent()->child(i)->checkState(0)==Qt::Checked)
//                    checked ++;
//                else if (item->parent()->child(i)->checkState(0)==Qt::Unchecked)
//                    unchecked ++;
//            }
//            if (partiallyChecked == true || (checked!=item->parent()->childCount() && unchecked!=item->parent()->childCount()))
//                item->parent()->setCheckState(0,Qt::PartiallyChecked);
//            else if (partiallyChecked == false && checked==item->parent()->childCount())
//                item->parent()->setCheckState(0,Qt::Checked);
//            else if (partiallyChecked == false && unchecked==item->parent()->childCount())
//                item->parent()->setCheckState(0,Qt::Unchecked);
//        }
//        if (item->parent()->parent())
//            updateCheckboxes(item->parent());
//
//    }


}

void FeatureTreeWidget::updateChildrenCheckboxes(QTreeWidgetItem *item)
{
    for (int i = 0; i < item->childCount();i++){
        if (item->checkState(0)!=Qt::PartiallyChecked)
            item->child(i)->setCheckState(0,item->checkState(0));
        updateChildrenCheckboxes(item->child(i));
    }
}

void FeatureTreeWidget::setCheckboxes(QTreeWidgetItem *item)
{
//    //Flags, die für jeden erstellten Knoten gesetzt werden müssen -> Checkboxen!
//    QFlags<Qt::ItemFlag> flgParent = Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;
//    item->setFlags(flgParent);
//    item->setCheckState(0,Qt::Checked);
//    for (int i = 0; i<item->childCount();i++)
//    {
//        if (item->child(i)->childCount()==0){
//            item->child(i)->setFlags(flgParent);
//            item->child(i)->setCheckState(0,Qt::Checked);
//
//            if (item->child(i)->backgroundColor(0).isValid()){
//                QToolButton *deleteButton = new QToolButton(this);
//                deleteButton->setFixedSize(20,20);
//                QIcon icon = QIcon();
//                icon.addPixmap(QPixmap(QString(":/images/cross.png")),QIcon::Normal,QIcon::On);
//                deleteButton->setIcon(icon);
//                setItemWidget(item->child(i),1,deleteButton);
//            }
//
//        }
//        if (item->child(i)->childCount()!=0)
//            setCheckboxes(item->child(i));
//    }
}
//
void FeatureTreeWidget::removeColorAssignment()
{
    mainWindow->questionDialog->writeToLog("deleteColor<1>");
    MyTreeWidgetItem *item = static_cast<MyTreeWidgetItem*>(itemAt(mapFromGlobal(cursor().pos())));
    MyListWidgetItem *listItem = new MyListWidgetItem(QString(""));
    listItem->setBGColor(item->getBGColor());
    //Icon wichtig, damit Item überhaupt angezeigt wird!

    Feature *f = getCorrespondingFeature(item->text(0));
    colorManager->deleteColorForFeature(f);
    QIcon icon = QIcon();
    icon.addPixmap(QPixmap(QString(":/images/leer.png")),QIcon::Normal,QIcon::On);
    listItem->setIcon(icon);
    listWidget->addItem(listItem);

    item->setBackgroundInvalid();
    itemWidget(item,1)->hide();
    redrawListWidget();
    mainWindow->updateSMVTreeTexture(f);
}

void FeatureTreeWidget::removeColorAssignmentFromSelection()
{
    QString size = "";
    size = size.setNum(selectedItems().size());
    mainWindow->questionDialog->writeToLog("deleteColor<" + size + ">");
    for (int i = 0; i < selectedItems().size();i++){

        MyTreeWidgetItem *item = static_cast<MyTreeWidgetItem*>(selectedItems().at(i));
        if (item->getBGColor()->getColor().isValid()){
            MyListWidgetItem *listItem = new MyListWidgetItem(QString(""));
            listItem->setBGColor(item->getBGColor());
            //Icon wichtig, damit Item überhaupt angezeigt wird!

            Feature *f = getCorrespondingFeature(item->text(0));
            colorManager->deleteColorForFeature(f);
            QIcon icon = QIcon();
            icon.addPixmap(QPixmap(QString(":/images/leer.png")),QIcon::Normal,QIcon::On);
            listItem->setIcon(icon);
            listWidget->addItem(listItem);

            item->setBackgroundInvalid();
            itemWidget(item,1)->hide();
            mainWindow->updateSMVTreeTexture(f);
        }
    }
    redrawListWidget();
}

QList <QTreeWidgetItem*> FeatureTreeWidget::findBackGroundColor(QColor background,QTreeWidgetItem *item, QList <QTreeWidgetItem*> *list){

    for (int i = 0; i < item->childCount();i++)
    {
        if (item->child(i)->backgroundColor(0)==background){
            list->push_back(item->child(i));
        }

        if (item->child(i)->childCount()!=0)
            findBackGroundColor(background,item->child(i),list);
    }
    return *list;
    
}

void FeatureTreeWidget::assignAutomatically(){
    QString size = "";
    size = size.setNum(selectedItems().size());
    mainWindow->questionDialog->writeToLog("assignColor<" + size + ">");

    //schon zugewiesene Farben löschen
    for (int i = 0; i < selectedItems().size();i++){
        MyTreeWidgetItem *item = static_cast<MyTreeWidgetItem*>(selectedItems().at(i));
        if (item->backgroundColor(0).isValid()){
            MyListWidgetItem *listItem = new MyListWidgetItem(QString(""));
            listItem->setBGColor(item->getBGColor());
            //Icon wichtig, damit Item überhaupt angezeigt wird!
            QIcon icon = QIcon();
            icon.addPixmap(QPixmap(QString(":/images/leer.png")),QIcon::Normal,QIcon::On);
            listItem->setIcon(icon);
            listWidget->addItem(listItem);

            colorManager->deleteColorForFeature(getCorrespondingFeature(item->text(0)));

            //item->setBackgroundColor(0,QColor(-1,-1,-1,-1));
            item->setBackgroundInvalid();
            itemWidget(item,1)->hide();
        }
    }

    int cnt = 0;
    if (selectedItems().size() <= listWidget->count())
        cnt = selectedItems().size();
    else
        cnt = listWidget->count();
    //nacheinander jedem ausgewählten Knoten, möglichst unterschiedliche Farben des ListWidgets zuweisen
    QList <Color*> *colors = new QList<Color*>();
    int step = 0;
    if (cnt >1) //Division durch 0 verhindern
        step = (listWidget->count()-1)/(cnt-1);
    else
        step = 0;

    //Farben unterschiedlicher wählen
    if (step < selectedItems().size()/15)
        step = selectedItems().size()/15;
    //Farbliste füllen
    if (cnt > 1){
        for (int i = 0;i < cnt;i++){
            int add = 0;
            while (colors->contains(static_cast<MyListWidgetItem*>(listWidget->item((i*step + add)%listWidget->count()))->getBGColor())){
                add++;
            }
            colors->push_back(static_cast<MyListWidgetItem*>(listWidget->item((i*step + add)%listWidget->count()))->getBGColor());
        }
    }else{
        int random = rand() % listWidget->count();
        colors->push_back(static_cast<MyListWidgetItem*>(listWidget->item(random))->getBGColor());
    }

    for (int i = 0; i < cnt;i++){

        QTreeWidgetItem *item = selectedItems().at(i);

        Feature *f = getCorrespondingFeature(item->text(0));
        //Color *c = static_cast<MyListWidgetItem*>(listWidget->item(0))->getBGColor();
        Color *c = colors->at(i);
        colorManager->setColorForFeature(f,c);

        //aktualisiere SmvTreeWidget und TextEdit
        mainWindow->updateSMVTreeTexture(f);

        //X zum Abwählen der Farbe setzen
        if (itemWidget(item, 1))
            itemWidget(item, 1)->show();
        else{
            QToolButton *deleteButton = new QToolButton(this);
            deleteButton->setFont(QFont(QString("MS Shell Dlg 2"),9,10,false));
            //deleteButton->setFixedSize(15,18);
            deleteButton->setFixedWidth(16);

            QIcon icon = QIcon();
            icon.addPixmap(QPixmap(QString(":/images/cross.png")),QIcon::Normal,QIcon::On);
            deleteButton->setIcon(icon);
            deleteButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            setItemWidget(item,1,deleteButton);
            connect(deleteButton,SIGNAL(clicked()),this,SLOT(removeColorAssignment()));
        }


        //wenn Farbe schon in FeatureTreeWidget vorhanden, setze diese auf weiß/transparent
        QList <QTreeWidgetItem*> *treeList = new QList <QTreeWidgetItem*>();
        findBackGroundColor(listWidget->item(0)->backgroundColor(),root,treeList);
        if (treeList->isEmpty()==false)
        {
            for (int i = 0;i < treeList->size();i++){
                static_cast<MyTreeWidgetItem*>(treeList->at(i))->setBackgroundInvalid();
//                treeList->at(i)->background(0).setStyle(Qt::NoBrush);
//                treeList->at(i)->setBackgroundColor(0,QColor(0,0,0,0));
                colorManager->deleteColorForFeature(getCorrespondingFeature(treeList->at(i)->text(0)));
            }
        }
        //setze Farbe im FeatureTreeWidget
        static_cast<MyTreeWidgetItem*>(item)->setBGColor(c);

        redrawListWidget();

    }
}
//

void FeatureTreeWidget::dragMoveEvent (QDragMoveEvent *event){

    QWidget::dragMoveEvent(event);
}

void FeatureTreeWidget::dropEvent(QDropEvent *event)
{
    //Darstellen des Drag-Bildes
    QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);
    QPixmap pixmap;
    QPoint offset;
    dataStream >> pixmap >> offset;

    QTreeWidgetItem *item = itemAt(event->pos().x(),event->pos().y());
    //wenn auf ein TreeWidgetItem gedropt und dieses ein Blattknoten ist
    if (item!=0)
    {

        if (item->childCount()==0){
            mainWindow->questionDialog->writeToLog("assignColor<1>");
            Feature *f = getCorrespondingFeature(item->text(0));
            //Color *c = new Color (selected->color.convertTo(QColor::Hsv));
            Color *c = static_cast<MyListWidgetItem*>(listWidget->selectedItems().at(0))->getBGColor();
            if (item->backgroundColor(0).isValid())
                mainWindow->removeColorAssignment(static_cast<MyTreeWidgetItem*>(item));
            colorManager->setColorForFeature(f,c);

            //X zum Abwählen der Farbe setzen
            if (itemWidget(item, 1))
                itemWidget(item, 1)->show();
            else{
                QToolButton *deleteButton = new QToolButton(this);
                deleteButton->setFont(QFont(QString("MS Shell Dlg 2"),9,10,false));
                //deleteButton->setFixedSize(15,18);
                deleteButton->setFixedWidth(16);


                QIcon icon = QIcon();
                icon.addPixmap(QPixmap(QString(":/images/cross.png")),QIcon::Normal,QIcon::On);
                deleteButton->setIcon(icon);
                deleteButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
                setItemWidget(item,1,deleteButton);
                connect(deleteButton,SIGNAL(clicked()),this,SLOT(removeColorAssignment()));
            }

            //aktualisiere SmvTreeWidget und TextEdit
            mainWindow->updateSMVTreeTexture(f);
            redrawListWidget();

            //wenn Farbe schon in FeatureTreeWidget vorhanden, setze diese auf weiß/transparent
            QList <QTreeWidgetItem*> *treeList = new QList <QTreeWidgetItem*>();
            findBackGroundColor(c->color,root,treeList);
            if (treeList->isEmpty()==false)
            {
                for (int i = 0;i < treeList->size();i++){
                    static_cast<MyTreeWidgetItem*>(treeList->at(i))->setBackgroundInvalid();
//                    treeList->at(i)->background(0).setStyle(Qt::NoBrush);
//                    treeList->at(i)->setBackgroundColor(0,QColor(0,0,0,0));
                    colorManager->deleteColorForFeature(getCorrespondingFeature(treeList->at(i)->text(0)));

                }
            }
            //setze Farbe im FeatureTreeWidget
            static_cast<MyTreeWidgetItem*>(item)->setBGColor(c);
            //item->setBackgroundColor(0,selected->color);


        }
        event->ignore();
    }
}

void FeatureTreeWidget::assignColorFromSMVTreeWidget(QString featureName)
{
    QTreeWidgetItem *item = getItemFromFeatureName(featureName);

    if (item!=0)
    {
        if (item->childCount()==0){
            mainWindow->questionDialog->writeToLog("assignColor<1>");
            Feature *f = getCorrespondingFeature(featureName);
            Color *c = static_cast<MyListWidgetItem*>(listWidget->selectedItems().at(0))->getBGColor();
            if (item->backgroundColor(0).isValid())
                mainWindow->removeColorAssignment(static_cast<MyTreeWidgetItem*>(item));
            colorManager->setColorForFeature(f,c);

            //X zum Abwählen der Farbe setzen
            if (itemWidget(item, 1))
                itemWidget(item, 1)->show();
            else{
                QToolButton *deleteButton = new QToolButton(this);
                deleteButton->setFont(QFont(QString("MS Shell Dlg 2"),9,10,false));
                //deleteButton->setFixedSize(15,18);
                deleteButton->setFixedWidth(16);

                QIcon icon = QIcon();
                icon.addPixmap(QPixmap(QString(":/images/cross.png")),QIcon::Normal,QIcon::On);
                deleteButton->setIcon(icon);
                deleteButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
                setItemWidget(item,1,deleteButton);
                connect(deleteButton,SIGNAL(clicked()),this,SLOT(removeColorAssignment()));
            }

            //aktualisiere SmvTreeWidget und TextEdit
            mainWindow->updateSMVTreeTexture(f);
            redrawListWidget();

            //wenn Farbe schon in FeatureTreeWidget vorhanden, setze diese auf weiß/transparent
            QList <QTreeWidgetItem*> *treeList = new QList <QTreeWidgetItem*>();
            findBackGroundColor(c->color,root,treeList);
            if (treeList->isEmpty()==false)
            {
                for (int i = 0;i < treeList->size();i++){
                    static_cast<MyTreeWidgetItem*>(treeList->at(i))->setBackgroundInvalid();
//                    treeList->at(i)->background(0).setStyle(Qt::NoBrush);
//                    treeList->at(i)->setBackgroundColor(0,QColor(0,0,0,0));
                    colorManager->deleteColorForFeature(getCorrespondingFeature(treeList->at(i)->text(0)));

                }
            }
            //setze Farbe im FeatureTreeWidget
            static_cast<MyTreeWidgetItem*>(item)->setBGColor(c);
            //item->setBackgroundColor(0,selected->color);
        }
    }
}

void FeatureTreeWidget::redrawListWidget()
{
    listWidget->clear();
    //erstelle ListWidgetItems aller Farbmöglichkeiten
    for (int i = 0;i < colorManager->colorArray->size();i++)
    {
        if (colorManager->colorArray->at(i)->isAvailable()){
            MyListWidgetItem *item = new MyListWidgetItem(QString(""));


            item->setBGColor(colorManager->colorArray->at(i));
            //Icon wichtig, damit Item überhaupt angezeigt wird!
            QIcon icon = QIcon();
            icon.addPixmap(QPixmap(QString(":/images/leer.png")),QIcon::Normal,QIcon::On);
            item->setIcon(icon);

            listWidget->addItem(item);
        }
    }
}

void FeatureTreeWidget::setColorManager(ColorManager *cm){
    colorManager = cm;
}

Feature* FeatureTreeWidget::getCorrespondingFeature(QString featureName){
    for(int i=0; i<featureList->size(); i++){
        Feature *currentFeature = &(featureList->at(i));
        if(currentFeature->getName() == featureName){
            return currentFeature;
        }
    }
    //cout << "Feature mit dem Namen " + featureName +" existiert nicht." <<endl;
    return NULL;
}

void FeatureTreeWidget::unselect(){
    setSelection(rect(),QItemSelectionModel::Deselect);
}

void FeatureTreeWidget::updateEditorGeometries(){
    QTreeWidget::updateEditorGeometries();
    QTreeWidgetItemIterator it (this,QTreeWidgetItemIterator::NoChildren);
    while(*it){
        MyTreeWidgetItem *item = static_cast<MyTreeWidgetItem*>(*it);
        if (itemWidget(item,1)!=0 && !item->getBGColor()->color.isValid()){
            itemWidget(item,1)->hide();
        }
        ++it;
    }
}

QTreeWidgetItem *FeatureTreeWidget::getItemFromFeatureName(QString featureName){
    QTreeWidgetItemIterator it (this,QTreeWidgetItemIterator::NoChildren);
    while(*it){
        if ((*it)->text(0) ==  featureName){
            return (*it);
        }
        ++it;
    }
    return 0;
}
