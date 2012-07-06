#include "xmldomparser.h"
#include <iostream>
#include <QTreeWidget>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QTreeWidgetItem>
#include <QQueue>
#include "stnode.h"
#include <QImage>
#include <QRgb>
#include <QBrush>
#include <QList>
#include "feature.h"
#include "featurefracture.h"
#include <QFile>
#include <QStack>
#include <QIODevice>
#include <QTextStream>
#include "smvtreewidget.h"
#include "mainwindow.h"

XmlDomParser::XmlDomParser(SMVTreeWidget *treePV, SMVTreeWidget *treeFV, vector <Feature> *list)
{
//    isLineBased = false;
//    if (MainWindow::path.contains("Xenomai")||MainWindow::path.contains("xenomai"))
        isLineBased = true;
    treeWidgetPackageView = treePV;
    treeWidgetFeatureView = treeFV;
    this->featureList = list;
}

XmlDomParser::~XmlDomParser(){}
bool XmlDomParser::readFile(QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
            std::cerr << "Error: Cannot read file "
                      << ": " << qPrintable(file.errorString())
                      << std::endl;
            return false;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument doc;
    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
        std::cerr << "Error: Parse error at line " << errorLine << ", "
                  << "column " << errorColumn << ": "
                  << qPrintable(errorStr) << std::endl;
        return false;
    }


    QDomElement root = doc.documentElement();
    if (root.tagName() != "project") {
        std::cerr << "Error: File is not a project file" << std::endl;
        return false;
    }

    STNode *rootSTNode = static_cast <STNode*> (treeWidgetPackageView->invisibleRootItem());
    parseProject(root, rootSTNode);
    deleteEmptyFolders(rootSTNode);
    file.close();
    return true;
}

void XmlDomParser::countTotalCharsAndAssignToSTNodes(QString &sourceRootDir){
//    STNode *rootSTNode = static_cast <STNode*> (treeWidgetPackageView->invisibleRootItem());
//
//    QQueue<STNode*> nodeQueue;
//
//    STNode *currentNode = static_cast <STNode*>(rootSTNode->child(0));
//    nodeQueue.enqueue(currentNode);

    //1. Finden der Java-Dateien im Baum und ermitteln der Gesamtzeichenanzahl pro File
    //über alle Blätter, d.h. .java oder .c oder .h Dateien iterieren
    QTreeWidgetItemIterator itLeaves(treeWidgetPackageView,QTreeWidgetItemIterator::NoChildren);
    while (*itLeaves) {
        STNode *currentNode = static_cast <STNode*>(*itLeaves);

        if(currentNode->childCount() == 0){
            QTreeWidgetItem *item = static_cast <QTreeWidgetItem*>(currentNode);
            QString path = "/" + currentNode->text(0);
            if (isLineBased){//nur, weil bei expressionp, etc. schon alles direkt im src ordner liegt
                while(item->parent()){
                    item = item->parent();
                    if (item->parent())
                        path.prepend("/"+item->text(0));
                }


            }

            QString javaFileName = sourceRootDir + path;
            int zeichenAnzahl = getTotalCharCountOfFile(javaFileName);
//            //test welche dateien gefunden wurden
//            if (zeichenAnzahl != 0)
//                currentNode->setSelected(true);
            currentNode->setNumberOfTotalChars(zeichenAnzahl);
        }
        ++itLeaves;
    }

    //2. Berechenen der Gesamtzeichenanzahl fÃ¼r alle anderen Folder
    QTreeWidgetItemIterator itParents(treeWidgetPackageView,QTreeWidgetItemIterator::HasChildren);
    //umgekehrt iterieren (deshalb zuerst den letzten Iterator finden)
    int cnt = 0;
    while (*itParents) {
         cnt++;
        ++itParents;
    }
    QTreeWidgetItemIterator itParents2(treeWidgetPackageView,QTreeWidgetItemIterator::HasChildren);
    itParents2+=(cnt-1);

    while (*itParents2) {
        STNode *currentNode = static_cast <STNode*>(*itParents2);
        currentNode->calculateNumberOfTotalChars();

        --itParents2;
    }



}

void XmlDomParser::calculateWhiteSpaceForAllSTNodes(){
    QTreeWidgetItemIterator it(treeWidgetPackageView,QTreeWidgetItemIterator::NoChildren);
    while (*it) {
        STNode *currentNode = static_cast <STNode*>(*it);
        currentNode->addWhiteSpaceToParent(currentNode->whiteSpace);
        currentNode->calculateFeaturePercentage();

        it++;
    }
}

void XmlDomParser::updateSTNodeTextures(Feature *feature){
    int width = 250;
    int height = 16;

    //Texturen für den FeatureView-Tree updaten
    QTreeWidgetItemIterator itFeature(treeWidgetFeatureView->invisibleRootItem()->child(feature->index),QTreeWidgetItemIterator::All);
    while (*itFeature) {
        STNode *currentNode = static_cast<STNode*>(*itFeature);

        if(currentNode->getNodeType()==STNode::FEATUREROOT){
            QPixmap image = currentNode->backgroundSave;
            QPainter painter(&image);

            painter.fillRect(1,1,width,image.rect().height(),feature->getColor()->getColor());
            QBrush brush (image);
            currentNode->setBackground(0, brush);
            currentNode->backgroundSave = image;
        }
        else{
            QPixmap image = currentNode->backgroundSave;
            QPainter painter(&image);

            painter.fillRect(1,1,currentNode->getColorDistributionListFeatureView()->list->at(feature->index)->offset+1
                             ,image.rect().height(),feature->getColor()->getColor());
            QBrush brush (image);
            currentNode->setBackground(0, brush);
            currentNode->backgroundSave = image;
        }
        ++itFeature;

        if (*itFeature){
            STNode *nextNode = static_cast<STNode*>(*itFeature);
            if (nextNode->getNodeType()==STNode::FEATUREROOT)
                break;
        }
    }

    //Texturen für den PackageView-Tree erzeugen
    QTreeWidgetItemIterator itPackage(treeWidgetPackageView,QTreeWidgetItemIterator::All);
    while (*itPackage) {
        STNode *currentNode = static_cast<STNode*>(*itPackage);
        if (currentNode->getColorDistributionList()->list->at(feature->index)->offset > 0){

            QPixmap image = currentNode->backgroundSave;
            QPainter painter(&image);
            QColor c = feature->getColor()->getColor();
            if (c == QColor(220,220,220,255)||c == QColor(180,180,180,255)){
                if (currentNode->getColorDistributionList()->list->at(feature->index)->greyTone)
                    c = QColor(220,220,220,255);
                else
                    c = QColor(180,180,180,255);
            }
            painter.fillRect(currentNode->getColorDistributionList()->list->at(feature->index)->start,1,
                             currentNode->getColorDistributionList()->list->at(feature->index)->offset,image.rect().height(),
                             c);

            //dahinter einige Pixel auf weiß setzen , damit Textur, die sich wiederholt nicht sofort anschlieÃŸt
            painter.fillRect(width,0,width,height,Qt::white);

            QBrush brush (image);
            currentNode->setBackground(0, brush);
            currentNode->backgroundSave = image;

            //            QBrush brush (currentNode->drawBackgroundImagePackageView(width));
            //            currentNode->setBackground(0, brush);

        }
        ++itPackage;
    }
}

void XmlDomParser::generateSTNodeTextures(int width){

//    //calculateWhiteSpaceForAllSTNodes();
//
//    //Texturen für den PackageView-Tree erzeugen
//
//    QTreeWidgetItemIterator itPackage(treeWidgetPackageView,QTreeWidgetItemIterator::All);
//    while (*itPackage) {
//        STNode *currentNode = static_cast<STNode*>(*itPackage);
//        QPixmap texture = currentNode->drawBackgroundImagePackageView(width);
//        QBrush brush (currentNode->drawBackgroundImagePackageView(width));
//        currentNode->setBackground(0, brush);
//        currentNode->backgroundSave = texture;
//
//        ++itPackage;
//    }
//    //Texturen für den FeatureView-Tree erzeugen
//
//    int featureIndex = -1;
//
//    QTreeWidgetItemIterator itFeature(treeWidgetFeatureView,QTreeWidgetItemIterator::All);
//    while (*itFeature) {
//        //Feature *currentFeature = &featureList->at(featureIndex);//getCorrespondingFeature(treeWidgetFeatureView->invisibleRootItem()->child(j)->text(0));
//        STNode *currentNode = static_cast<STNode*>(*itFeature);
//        if(currentNode->getNodeType()==STNode::FEATUREROOT){
//            featureIndex++;
//            QBrush brush (currentNode->drawFeatureNodeBackgroundImage(&featureList->at(featureIndex), width,featureIndex));
//            currentNode->setBackground(0, brush);
//            currentNode->backgroundSave = currentNode->background(0).texture();
//        }
//        else{
//            QBrush brush (currentNode->drawBackgroundImageFeatureView(&featureList->at(featureIndex), width,featureIndex));
//            currentNode->setBackground(0, brush);
//            currentNode->backgroundSave = currentNode->background(0).texture();
//        }
//
//        ++itFeature;
//
//    }
      // reduceTreeWidgetFeatureView();

}

//Einlesen des Project-Elements, Ãœbergabe des parent als Elternknoten des Projekt-Elements
void XmlDomParser::parseProject(const QDomElement &projectElement, STNode *parent){
    //item wird als kind von parent initialisiert
    //ROOT Knoten <project name="xxx">
    STNode *item = new STNode(parent);
    item->setText(0, projectElement.attribute("name"));
    item->setNodeType(STNode::PROJECT);
    item->setFeatureList(featureList);

    //<file name=".classpath"/>
    QDomNode child = (QDomNode)projectElement.firstChild();

    while (!child.isNull()) {
        const QDomElement &refChildElement = child.toElement();
        if(child.toElement().tagName() == "folder"){
            parseFolder(refChildElement, item);
        }else if (child.toElement().tagName() == "file"){
            parseFile(refChildElement, item);
        }else if(child.toElement().tagName() == "feature"){
            parseFeature(projectElement, refChildElement, item);
        }

       child = child.nextSibling();
    }

}

void XmlDomParser::parseFolder(const QDomElement &folderElement, STNode *parent){

    STNode *item = new STNode(parent);
    item->setText(0, folderElement.attribute("name"));
    item->setNodeType(STNode::FOLDER);
    item->setFeatureList(featureList);

    QDomNode child = folderElement.firstChild();
    while (!child.isNull()) {
        const QDomElement &refChildElement = child.toElement();
        if(child.toElement().tagName() == "folder"){
            parseFolder(refChildElement, item);
        }else if (child.toElement().tagName() == "file"){
            parseFile(refChildElement, item);
        }else if(child.toElement().tagName() == "feature"){
            parseFeature(folderElement, refChildElement, item);
        }

       child = child.nextSibling();
    }
}

void XmlDomParser::parseFile(const QDomElement &fileElement, STNode *parent){

    //nur java-Files werden in den Baum aufgenommen
    QString name = fileElement.attribute("name");
    if (name.endsWith(".java") || name.endsWith(".c")|| name.endsWith(".h")){ //auch für C

        STNode *item = new STNode(parent);
        item->setText(0, fileElement.attribute("name"));
        item->setNodeType(STNode::FILE);
        item->setFeatureList(featureList);

        QDomNode child = fileElement.firstChild();
        if (fileElement.childNodes().size()==0)
            item->whiteSpace = fileElement.attribute("length").toInt();
        while (!child.isNull()) {
            const QDomElement &refChildElement = child.toElement();
            if(child.toElement().tagName() == "fragment"){
                parseFragment(refChildElement, item);
            }else if(child.toElement().tagName() == "feature"){
                parseFeature(fileElement, refChildElement, item);
            }

           child = child.nextSibling();
        }

    }
}

void XmlDomParser::parseFeature(const QDomElement &domParent, const QDomElement &featureElement, STNode *parent){
    if (!featureElement.text().contains(QRegExp("[^\\w_]"))){
        STNode *item = new STNode(parent);
        QString featureName = featureElement.text();
        item->setNodeType(STNode::FEATURE);
        item->setText(0, featureName);
        
        //Feature bezieht sich auf ein Fragment
        if(parent->getNodeType() == STNode::FRAGMENT){
            int length;
            int offset;
            if (isLineBased){
                length = domParent.attribute("endline").toInt()-domParent.attribute("startline").toInt();
                offset = domParent.attribute("startline").toInt();
            }else{
                length = domParent.attribute("length").toInt()-domParent.attribute("startline").toInt();
                offset = domParent.attribute("offset").toInt();
            }
            int numberOfFeaturesAssignedToThisPart = domParent.childNodes().size();

            STNode *grandParent = static_cast <STNode*>(parent->parent());
            Feature *corrFeature = getCorrespondingFeature(featureName);
            if (corrFeature!=0){
                grandParent->addToFeatureFractureList(corrFeature, length, offset, numberOfFeaturesAssignedToThisPart);
                grandParent->featureFractureList->back().completeName = "";
                grandParent->getWhiteSpace(domParent.parentNode().toElement().attribute("length").toInt());
            }
        }

        //Feature bezieht sich auf Project, File oder Folder
        else{
            cout << "TODO: Feature assigned to Project, File oder Folder" <<endl;
        }
    }else{
        STNode *item = new STNode(parent);
        QString featureName = featureElement.text();
        item->setNodeType(STNode::FEATURE);
        item->setText(0, featureName);

        //Feature bezieht sich auf ein Fragment
        if(parent->getNodeType() == STNode::FRAGMENT){
            int length;
            int offset;
            if (isLineBased){
                length = domParent.attribute("endline").toInt()-domParent.attribute("startline").toInt();
                offset = domParent.attribute("startline").toInt();
            }else{
                length = domParent.attribute("length").toInt()-domParent.attribute("startline").toInt();
                offset = domParent.attribute("offset").toInt();
            }
            int numberOfFeaturesAssignedToThisPart = domParent.childNodes().size();

            STNode *grandParent = static_cast <STNode*>(parent->parent());
            QList<Feature*>*features = getCorrespondingFeatures(featureName);
            if (features!=0){
                for (int i = 0; i < features->size(); i++){
                    grandParent->addToFeatureFractureList(features->at(i), length, offset, numberOfFeaturesAssignedToThisPart);
                    grandParent->featureFractureList->back().completeName = featureName;
                }
                grandParent->getWhiteSpace(domParent.parentNode().toElement().attribute("length").toInt());
            }
        }

        //Feature bezieht sich auf Project, File oder Folder
        else{
            cout << "TODO: Feature assigned to Project, File oder Folder" <<endl;
        }
    }
    
}

void XmlDomParser::parseFragment(const QDomElement &fragmentElement, STNode *parent){

    STNode *item = new STNode(parent);
    item->setText(0, "fragment");
    item->setNodeType(STNode::FRAGMENT);


    QDomNode child = fragmentElement.firstChild();
    while (!child.isNull()) {
        const QDomElement &refChildElement = child.toElement();
        if(child.toElement().tagName() == "feature"){
            parseFeature(fragmentElement, refChildElement, item);
        }
       child = child.nextSibling();
    }
}

//lÃ¶scht leere Ordner aus dem Baum, die dadurch entstanden sind, dass nicht-java-dateien nicht eingefÃ¼gt wurden
//lÃ¶scht auch Fragment- und Featureknoten
void XmlDomParser::deleteEmptyFolders(STNode *root){

    bool emptyFoldersDeleted = true;
    QQueue<STNode*> nodeQueue;


    while (emptyFoldersDeleted){
        emptyFoldersDeleted = false;

        STNode *currentNode = static_cast <STNode*>(root->child(0));
        nodeQueue.enqueue(currentNode);

        while (!nodeQueue.isEmpty()){
            currentNode = nodeQueue.dequeue();

            QString nodeName = currentNode->text(0);
            int childCount = currentNode->childCount();
            for (int i=0; i<childCount; i++){
                nodeQueue.enqueue(static_cast <STNode*> (currentNode->child(i)));
            }

            //wenn Knoten Folder ist und keine Kinder hat, aus dem Baum entfernen
            if(!(nodeName.endsWith(".java") || nodeName.endsWith(".c")|| nodeName.endsWith(".h"))&& childCount == 0){
                STNode *parent = static_cast <STNode*>(currentNode->parent());
                parent->removeChild(currentNode);
                delete currentNode->getFeatureFractureList();
                delete currentNode->getColorDistributionListFeatureView();
                delete currentNode;

                emptyFoldersDeleted = true;
            }

        }


    }

}

void XmlDomParser::fillFeatureViewTreeWidget(MainWindow *mw){

    calculateWhiteSpaceForAllSTNodes();

    int featureCount = featureList->size();
    //wenn es keine Features gibt, leeren Baum anzeigen
    if (featureCount == 0){
        treeWidgetFeatureView->setDisabled(true);
        //treeWidgetFeatureView->invisibleRootItem()->child(0)->setDisabled(true);
    }

    //Texturen für den PackageView-Tree erzeugen

    QTreeWidgetItemIterator itPackage(treeWidgetPackageView,QTreeWidgetItemIterator::All);
    while (*itPackage) {
        STNode *currentNode = static_cast<STNode*>(*itPackage);
        QPixmap pix = currentNode->drawBackgroundImagePackageView(250);
        QBrush brush (pix);
        currentNode->setBackground(0, brush);
        currentNode->backgroundSave = pix;

        ++itPackage;
    }

    mw->setFilePath();

    for(int i=0; i<featureCount; i++){
        //static_cast<ItemDelegate*>(treeWidgetFeatureView->itemDelegate())->setRowHeight(25);
        STNode *rootFeatureNode = new STNode(treeWidgetFeatureView->invisibleRootItem());
        rootFeatureNode->setText(0, featureList->at(i).getName());
        rootFeatureNode->setNodeType(STNode::FEATUREROOT);
        rootFeatureNode->addChild(treeWidgetPackageView->topLevelItem(0)->clone());

        QTreeWidgetItemIterator itFeature(treeWidgetFeatureView->topLevelItem(i),QTreeWidgetItemIterator::All);
        while (*itFeature) {
            //Feature *currentFeature = &featureList->at(featureIndex);//getCorrespondingFeature(treeWidgetFeatureView->invisibleRootItem()->child(j)->text(0));
            STNode *currentNode = static_cast<STNode*>(*itFeature);
            if(currentNode->getNodeType()==STNode::FEATUREROOT){
                QPixmap pix = currentNode->drawFeatureNodeBackgroundImage(&featureList->at(i), 250,i);
                QBrush brush (pix);
                currentNode->setBackground(0, brush);
                currentNode->backgroundSave = pix;
            }
            else{
                QPixmap pix = currentNode->drawBackgroundImageFeatureView(&featureList->at(i), 200,i);
                QBrush brush (pix);
                currentNode->setBackground(0, brush);
                currentNode->backgroundSave = pix;
            }

            ++itFeature;
            if (*itFeature){
                STNode *nextNode = static_cast<STNode*>(*itFeature);
                if (nextNode->getNodeType()==STNode::FEATUREROOT)
                    break;
            }
            removeChildren(static_cast<STNode*>(treeWidgetFeatureView->topLevelItem(i)));
        }
    }
}

void XmlDomParser::removeChildren(STNode *currentNode){
    if (!currentNode->isColored){
        STNode *parent = static_cast <STNode*>(currentNode->parent());
        parent->removeChild(currentNode);
    }

    for (int i = 0;i<currentNode->childCount();i++){
        STNode *child = static_cast <STNode*>(currentNode->child(i));
        removeChildren(child);
        //Index anpassen, wenn Kind gelöscht wird
        if (!child->isColored)
            i--;
    }

}

void XmlDomParser::reduceTreeWidgetFeatureView(){
    for (int i = 0; i < featureList->size();i++){
        STNode *currentNode = static_cast<STNode*>(treeWidgetFeatureView->invisibleRootItem()->child(i));
        removeChildren(currentNode);
    }
//    QTreeWidgetItemIterator it(treeWidgetFeatureView->,QTreeWidgetItemIterator::All);
//    while(*it){
//        STNode *currentNode = static_cast<STNode*>((*it));
//        if (currentNode->isColored == false){
//            STNode *parent = static_cast <STNode*>(currentNode->parent());
//            parent->removeChild(currentNode);
//        }
//        ++it;
//    }






    
//    for(int i=0; i<treeWidgetFeatureView->invisibleRootItem()->childCount(); i++){
////    //for(int i=0; i<featureList->size(); i++){
//
//        bool emptyFoldersDeleted = true;
//        QQueue<STNode*> nodeQueue;
//
//        while (emptyFoldersDeleted){
//            emptyFoldersDeleted = false;
//
//            STNode *currentNode = static_cast <STNode*>(treeWidgetFeatureView->invisibleRootItem()->child(i)->child(0));
//            nodeQueue.enqueue(currentNode);
//
//            while (!nodeQueue.isEmpty()){
//                currentNode = nodeQueue.dequeue();
//
//                int childCount = currentNode->childCount();
//                for (int i=0; i<childCount; i++){
//                    nodeQueue.enqueue(static_cast <STNode*> (currentNode->child(i)));
//                }
//
//                //wenn Knoten in seiner FeatureFractureList kein Fracture vom aktuellen Feature hat, lÃ¶schen
//                bool FFListContainsCurrentFeature = false;
////                for(int j=0; j<currentNode->getFeatureFractureList()->size(); j++){
////                    FeatureFracture ff = currentNode->getFeatureFractureList()->at(j);
////                    Feature *feature = ff.getFeature();
////                    QString name = feature->name;
////
////                        if(name == featureList->at(i).name){
////                            FFListContainsCurrentFeature = true;
////                            break;
////                        }
////
////                }
//                if(currentNode->getColorDistributionList()->list->at(i)->offset>0){
//                    FFListContainsCurrentFeature = true;
//                }
//
//                if(!FFListContainsCurrentFeature){
//                    STNode *parent = static_cast <STNode*>(currentNode->parent());
//                    parent->removeChild(currentNode);
//                    //delete currentNode;
//                    //delete currentNode->getFeatureFractureList();
//                    emptyFoldersDeleted = true;
//                }
//            }
//        }
//    }


}

//zu Ã¼berarbeiten!
void XmlDomParser::freeMemory(){

    QQueue<STNode*> nodeQueue;
    bool childNodesDeleted = true;
    STNode *rootSTNode = static_cast <STNode*> (treeWidgetPackageView->invisibleRootItem());

    while (childNodesDeleted){
        childNodesDeleted = false;
        STNode *currentNode = static_cast <STNode*>(rootSTNode->child(0));
        nodeQueue.enqueue(currentNode);

        while (!nodeQueue.isEmpty()){
            currentNode = nodeQueue.dequeue();
            QString cNN = currentNode->text(0);

            int childCount = currentNode->childCount();
            for (int i=0; i<childCount; i++){
                nodeQueue.enqueue(static_cast <STNode*> (currentNode->child(i)));
            }

            //wenn Knoten Folder ist und keine Kinder hat, aus dem Baum entfernen
            if(childCount == 0){
                STNode *parent = static_cast <STNode*>(currentNode->parent());
                //cout << currentNode->text(0).toStdString() << endl;
                if(currentNode->getNodeType() != NULL){
                    cout << "lÃ¶schen: " << currentNode->text(0).toStdString() << endl;
                    parent->removeChild(currentNode);
                    delete currentNode;
                    delete currentNode->getFeatureFractureList();
                    childNodesDeleted = true;
                }
            }

        }
    }
}

template <typename T>
bool XmlDomParser::containsElement (vector <T> v, T element){

    for(int i=0; i<v.size(); i++){
        if(v.at(i)==element) return true;
    }
    return false;
}

//ausbaufÃ¤hig
QString XmlDomParser::getcorrespondingJavaFileName(QString &nodeName, QString &rootSourceDir){
    //Vorraussetzungen, dafÃ¼r, dass richtiger Pfad zurÃ¼ckgegeben wird:
    //-alle Java Dateien liegen im rootSourceDir
    //-der Javaklassenname entspricht nodeName
    QString result = rootSourceDir+"/"+nodeName;

    return result;
}

int XmlDomParser::getTotalCharCountOfFile(QString &javaFileName){

    QFile file (javaFileName);
    if(!file.exists()){
        return 0;
    }


    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    int result = 0;
    QTextStream in(&file);
     while (!in.atEnd()) {
         QString line = in.readLine();
         if (isLineBased)
             result += 1;
         else
            result += line.size();
     }
     return result;
}

Feature* XmlDomParser::getCorrespondingFeature(QString featureName){
    for(int i=0; i<featureList->size(); i++){
        Feature *currentFeature = &(featureList->at(i));
        if(currentFeature->getName() == featureName){
            return currentFeature;
        }
    }
    //cout << "Feature mit dem Namen " + featureName +" existiert nicht." <<endl;
    return 0;
}

QList <Feature*>* XmlDomParser::getCorrespondingFeatures(QString featureName){
    QList <Feature*> *features = new QList <Feature*>();
    for(int i=0; i<featureList->size(); i++){
        Feature *currentFeature = &(featureList->at(i));
        if(currentFeature->getName() == featureName){
            features->push_back(currentFeature);
            return features;
        }
        else if(featureName.contains(QRegExp("\\W" + currentFeature->getName() + "\\W")) ||
                                (featureName.startsWith(currentFeature->getName())
                                 && featureName.contains(QRegExp(currentFeature->getName() + "\\W")))  ||
                                (featureName.endsWith(currentFeature->getName()) &&
                                featureName.contains(QRegExp("\\W" + currentFeature->getName())))){
            features->push_back(currentFeature);
        }
    }
    if (!features->isEmpty())
        return features;
    //cout << "Feature mit dem Namen " + featureName +" existiert nicht." <<endl;
    return 0;
}

