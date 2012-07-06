#include "stnode.h"
#include <iostream>
#include "smvtreewidget.h"

STNode::STNode(QTreeWidgetItem *parent, int type) : QTreeWidgetItem(parent, type)
{
    path = "";
    featureFractureQList = new QList <FeatureFracture>();
    featurePercentage = new QList <int>();

    colorDistributionList = new STNodeColorDistribution();
    colorDistributionListFeatureView = new STNodeColorDistribution();
    featureFractureList = new vector <FeatureFracture>();

    featureList = new vector <Feature>();
    backgroundSave = QPixmap();
    isColored = false;
    //totalChars = 0;
    whiteSpace = 0;

}
QList <FeatureFracture>* STNode::getFeatureFractureQList(){
    if (featureFractureQList)
        return featureFractureQList;
    else return 0;
}

STNode *STNode::clone() const
{

    //for(int j=0; j<currentNode->getFeatureFractureList()->size(); j++){
    //                    FeatureFracture ff = currentNode->getFeatureFractureList()->at(j);
    //                    Feature *feature = ff.getFeature();
    //                    QString name = feature->name;
    //
    //                        if(name == featureList->at(i).name){
    //                            FFListContainsCurrentFeature = true;
    //                            break;
    //                        }
    //
    //                }

    STNode *copy = 0;

    QStack<const STNode*> stack;
    QStack<STNode*> parentStack;
    stack.push(this);
    parentStack.push(0);

    STNode *root = 0;
    const STNode *item = 0;
    STNode *parent = 0;

    while (!stack.isEmpty()) {
        // get current item, and copied parent
        item = stack.pop();
        parent = parentStack.pop();

        // copy item
        copy = new STNode(*item);
        if (!root)
            root = copy;

        // set parent and add to parents children list
        if (parent) {

            QList<QTreeWidgetItem*> copyList = QList<QTreeWidgetItem*>();
            copyList.push_back(copy);
            parent->insertChildren(0,copyList);

        }

        for (int i = 0; i < item->childCount(); ++i) {
            stack.push(static_cast <STNode*>(item->child(i)));
            parentStack.push(copy);
        }
    }
    return root;
}
STNode::STNode(const QTreeWidgetItem &other) : QTreeWidgetItem(other)
{
    featureFractureQList = new QList <FeatureFracture>();
    featurePercentage = new QList <int>();
    colorDistributionList = new STNodeColorDistribution();
    colorDistributionListFeatureView = new STNodeColorDistribution();
    type = STNode::NON;
    totalChars = 0;
    featureList = new vector<Feature>();
    featureFractureList = new vector <FeatureFracture>();
    isColored = false;

}
//STNode STNode::child(int index){
//    if (index < 0 || index >= children.size())
//        return 0;
//    executePendingSort();
//    return children.at(index);
//
//}
STNode::STNode( STNode &other, bool dummi) : QTreeWidgetItem(other)
{
    featureFractureQList = new QList <FeatureFracture>(*other.featureFractureQList);
    featurePercentage = new QList <int>();
    colorDistributionList = new STNodeColorDistribution();
    colorDistributionListFeatureView = new STNodeColorDistribution();
    type = other.getNodeType();
    totalChars = other.totalChars;
    featureList = new vector<Feature>(*(other.getFeatureList()));
    featureFractureList = new vector <FeatureFracture>(*(other.featureFractureList));

    isColored = false;
}

void STNode::setFeatureList(vector<Feature> *FList){
    featureList = FList;
    for (int i = 0; i < featureList->size(); i++){
        featurePercentage->push_back(0);
    }
}

vector <Feature>* STNode::getFeatureList(){
    return featureList;
}



void STNode::setFeatureFractureList(vector <FeatureFracture> *FFList){

    featureFractureList = FFList;
}

vector <FeatureFracture>* STNode::getFeatureFractureList(){
    return featureFractureList;
}

void STNode::setNodeType(NodeType t){
    type = t;
}

STNode::NodeType STNode::getNodeType(){
    return type;
}

void STNode::calculateNumberOfTotalChars(){
    STNode *child;
    int result = 0;
    for(int i=0; i<this->childCount(); i++){
        child = static_cast <STNode*>(this->child(i));
        result += child->getNumberOfTotalChars();
    }
    this->totalChars = result;
}

void STNode::setNumberOfTotalChars(int i){
    totalChars = i;
}

int STNode::getNumberOfTotalChars(){
    return totalChars;
}

void STNode::addToFeatureFractureList(Feature *f, int chars, int charOffset, int numberOfFeaturesAssignedToThisPart){
    if (f!=0){
        FeatureFracture ff (f,chars, charOffset, numberOfFeaturesAssignedToThisPart);
        featureFractureList->push_back(ff);
        featureFractureQList->push_back(FeatureFracture(ff));

        //adden des FF auch bei Elternknoten
        //rekursiver Aufruf erfolgt bis zum Root-Node des Baums
        STNode *parent = static_cast <STNode*>(this->parent());
        if(parent != NULL){
            parent->addToFeatureFractureList(ff);
            //parent->getWhiteSpace();
        }
    }

}

void STNode::addToFeatureFractureList(FeatureFracture ff){
    featureFractureList->push_back(ff);
    featureFractureQList->push_back(FeatureFracture(ff));

    //adden des FF auch bei Elternknoten
    //rekursiver Aufruf erfolgt bis zum Root-Node des Baums
    STNode *parent = static_cast <STNode*>(this->parent());
    if(parent != NULL){
        parent->addToFeatureFractureList(ff);
        //parent->getWhiteSpace();
    }
}


QPixmap STNode::drawBackgroundImagePackageView(int width){

    QString toolTip = "";
    int featuresContained = 0;
    for (int i = 0; i < featurePercentage->size(); i++){
        if (featurePercentage->at(i)>0){
            toolTip += featureList->at(i).getName() + "\n";
            featuresContained++;
        }
        if (featuresContained > 50){
            toolTip += "...\n";
            break;
        }
    }
    if (toolTip != "")
        toolTip.remove(toolTip.length()-1,2);
    setToolTip(0,toolTip);
    
    //End Space, um nach den eigentlichen 100% Breite noch wei√ü malen zu k√∂nnen
    int widthPlusEndSpace = width + 100;
    int height = 35;
    int heightPlusEndSpace = height + 10;

    //FeatureFractureQList nach length sortieren
    sortFeatureFractureQList(false);

    double whiteSpacePercentage = 0;
    if (totalChars>0){
        whiteSpacePercentage = ((double)whiteSpace/(double)totalChars) * (double)width;
        if (whiteSpacePercentage>0 && whiteSpacePercentage<1)
            whiteSpacePercentage = 1;
    }
    if (width >= whiteSpacePercentage)
        width -=(int)whiteSpacePercentage;
    
    

    QPixmap texture (widthPlusEndSpace+1,heightPlusEndSpace);//, QImage::Format_RGB32);
    QPainter painter(&texture);


    //Knoten-Fl‰che weiﬂ einf‰rben
    painter.fillRect(0,0,widthPlusEndSpace,heightPlusEndSpace,Qt::white);

    int totalFeatureLines = 0;
    for (int i = 0; i < featurePercentage->size(); i++){
        totalFeatureLines += featurePercentage->at(i);
    }
    int numberOfOnePixelParts = 0;
    int oldWidth = width;
    //Fill colorDistributionlists
    for (int i = 0; i < featureList->size(); i++){
        colorDistributionList->writeToFeatureDistributionList(i,0,0);
        colorDistributionListFeatureView->writeToFeatureDistributionList(i,0,0);
    }
    if (width == 0 && totalFeatureLines > 0)
        width = 2;
    if (width > 0){
        //int numberOfOnePixelParts = 0;
        for (int i = 0; i < featurePercentage->size(); i++){
            double lengthPercentage = (double)featurePercentage->at(i)/(double)totalFeatureLines * (double)width;
            if (lengthPercentage >= 0 && lengthPercentage < 1 && featurePercentage->at(i)>0)
                numberOfOnePixelParts++;
        }
        width -=numberOfOnePixelParts;
        if (width < 1)
            width = 1;
        int dummy = 0;
        int x = 1;
        for (int i = 0; i < featurePercentage->size(); i++){
            if (featurePercentage->at(i)>0){
                QColor colorValue = featureList->at(i).getColor()->getColor();
                double lengthPercentage = (double)featurePercentage->at(i)/(double)totalFeatureLines * (double)width;
                if (lengthPercentage >= 0 && lengthPercentage < 1 && featurePercentage->at(i)>0)
                    lengthPercentage = 1;

                if (colorValue == QColor(220, 220, 220, 255) || colorValue == QColor(180, 180, 180, 255)){
                    if (dummy % 2 == 0){
                        colorValue = QColor(220, 220, 220, 255);
                    }else{
                        colorValue = QColor(180, 180, 180, 255);
                    }
                }
                dummy++;

                int roundedPercentage = static_cast<int>(lengthPercentage + 0.5);
                painter.fillRect(x,0,roundedPercentage,50,colorValue);

                colorDistributionList->writeToFeatureDistributionList(i,x,roundedPercentage);
                x += roundedPercentage;
                if (roundedPercentage > 0)
                    isColored = true;
            }
        }
    }
    //dahinter einige Pixel auf weiﬂ setzen , damit Textur, die sich wiederholt nicht sofort anschlie√üt
//    painter.fillRect(oldWidth,0,widthPlusEndSpace,height,Qt::blue);
//    painter.fillRect(0,20,250,25,Qt::green);



//    if (x > 0){
//        QPixmap withoutWhiteSpace = texture.copy(0,0,x,heightPlusEndSpace);
//        painter.fillRect(0,0,width,heightPlusEndSpace,QBrush(withoutWhiteSpace.scaledToWidth(width)));
//    }
    //dahinter einige Pixel auf weiﬂ setzen, damit Textur, die sich wiederholt nicht sofort anschlie√üt
    //painter.fillRect(oldWidth,0,widthPlusEndSpace,height,Qt::blue);

    return texture;//.copy(0,0,widthPlusEndSpace,heightPlusEndSpace);
}

QPixmap STNode::drawBackgroundImageFeatureView(Feature *f, int width, int indexOfFeature){

    setToolTip(0,"");
    //int width = 100;
    //End Space, um nach den eigentlichen 100% Breite noch wei√ü malen zu k√∂nnen
    int widthPlusEndSpace = width + 100;
    int height = 35;
    int heightPlusEndSpace = height + 10;
    QPixmap texture (widthPlusEndSpace,heightPlusEndSpace);
    QPainter painter(&texture);

    //Knoten-Fl√§che wei√ü einf√§rben
    painter.fillRect(0,0,width,height,Qt::white);

    //dahinter einige Pixel auf weiﬂ setzen , damit Textur, die sich wiederholt nicht sofort anschlie√üt
    painter.fillRect(width,0,widthPlusEndSpace,height,Qt::white);

    //darunter einige Pixel auf weiﬂ setzen
    painter.fillRect(0,height,widthPlusEndSpace,heightPlusEndSpace,Qt::white);

    int totalFeatureChars = 0;
    SMVTreeWidget *myTreeWidget = static_cast <SMVTreeWidget*> (this->treeWidget());
    ColorManager *cm = myTreeWidget->getColorManager();

    // QColor colorValue(30, 200, 255, 255);
    //if(cm->FCPListContainsFeature(f))
    QColor colorValue = cm->getColorForFeature(f)->getColor();

    for(int j=0; j<featureFractureList->size(); j++){
        FeatureFracture *fracture = &(featureFractureList->at(j));
        Feature *fractionFeature = fracture->getFeature();
        if(fractionFeature == f){
            int l = featureFractureList->at(j).getLength();
            int nb = featureFractureList->at(j).getNumberOfFeaturesAssignedToThisPart();
            int temp = l/nb;
            totalFeatureChars += temp;
        }
    }
    double percentage = 0;
    if (this->getNumberOfTotalChars() > 0){
        percentage = (double)totalFeatureChars/(double)this->getNumberOfTotalChars();
    }

    int widthToDraw = width*percentage;
    if(totalFeatureChars>0 && widthToDraw<1) widthToDraw = 1;

    painter.fillRect(1,0,widthToDraw,50,colorValue);
    colorDistributionListFeatureView->writeToFeatureDistributionList(indexOfFeature,2,widthToDraw);

    if (widthToDraw > 0)
        isColored = true;
    else
        isColored = false;

    return texture;
}

QPixmap STNode::drawFeatureNodeBackgroundImage(Feature *f, int width, int indexOfFeature){
    setToolTip(0,"");
    colorDistributionListFeatureView->writeToFeatureDistributionList(indexOfFeature,1,width);

    //End Space, um nach den eigentlichen 100% Breite noch wei√ü malen zu k√∂nnen
    int widthPlusEndSpace = width + 100;
    int height = 45;
    int heightPlusEndSpace = height;
    QPixmap texture (widthPlusEndSpace,heightPlusEndSpace);
    QPainter painter(&texture);

    SMVTreeWidget *myTreeWidget = static_cast <SMVTreeWidget*> (this->treeWidget());
    ColorManager *cm = myTreeWidget->getColorManager();

    //QColor colorValue(30, 200, 255, 255);
    //if(cm->FCPListContainsFeature(f))
    QColor colorValue = cm->getColorForFeature(f)->getColor();

    //gesamten Knoten in feature-Farbe einf√§rben
    painter.fillRect(1,0,width,height,colorValue);

    //dahinter einige Pixel auf weiﬂ setzen , damit Textur, die sich wiederholt nicht sofort anschlie√üt
    painter.fillRect(width,0,widthPlusEndSpace,height,Qt::white);

    //darunter einige Pixel auf weiﬂ setzen
    painter.fillRect(0,height,widthPlusEndSpace,heightPlusEndSpace,Qt::white);

    isColored = true;
    return texture;

}
//sortOffset = false ->nach length sortieren
void STNode::sortFeatureFractureQList(bool sortOffset){

    bool swapped = true;

    while(swapped){
        swapped = false;
        int i = 0;
        while(!swapped && i+1<featureFractureQList->size()){

                //offset aufsteigend sortieren
                if (sortOffset && featureFractureQList->at(i).offset > featureFractureQList->at(i+1).offset){

                    //Tausche Fractures
                    featureFractureQList->swap(i,i+1);
                    swapped = true;
                }
                //length absteigend sortieren
                if (!sortOffset && featureFractureQList->at(i).length < featureFractureQList->at(i+1).length){

                    //Tausche Fractures
                    featureFractureQList->swap(i,i+1);
                    swapped = true;
                }
        i++;
        }
    }
}

int STNode::getWhiteSpace(int lineCount){


    if (getNodeType()==STNode::FILE){
        //FeatureFractureQList nach offset sortieren
        sortFeatureFractureQList(true);

        int line = 1;
        int i = 0;
        whiteSpace = 0;
        int lastOffset;
        while(i < featureFractureQList->size() && line < lineCount){
            if (line < featureFractureQList->at(i).offset){
                whiteSpace += featureFractureQList->at(i).offset - line;
                line = featureFractureQList->at(i).length + featureFractureQList->at(i).offset;
            }else if (line < (featureFractureQList->at(i).length + featureFractureQList->at(i).offset))
                line = featureFractureQList->at(i).length + featureFractureQList->at(i).offset;
//            whiteSpace = featureFractureQList->at(0).offset;

            i++;
            if (i == featureFractureQList->size()&&(lineCount>line))
                whiteSpace+=lineCount-line;

        }
        //whiteSpace = double(whiteSpace)/(double)lineCount*100;
    }/*else{
        whiteSpace = 0;
        for (int i = 0; i < childCount(); i++){
            whiteSpace += static_cast<STNode*>(child(i))->whiteSpace;
        }
        //whiteSpace = whiteSpace/childCount();
    }*/
    


}


void STNode::addWhiteSpaceToParent(int white){

    if (parent()!=0){
        STNode *parentNode = static_cast<STNode*>(parent());
        parentNode->whiteSpace += white;
        parentNode->addWhiteSpaceToParent(white);
    }
}


STNodeColorDistribution* STNode::getColorDistributionList(){
    return colorDistributionList;
}
STNodeColorDistribution* STNode::getColorDistributionListFeatureView(){
    return colorDistributionListFeatureView;
}

void STNode::calculateFeaturePercentage(){
    if (childCount() == 0){
        for (int i = 0; i < featureList->size();i++){
            int featureLengthSum = 0;
            for (int j = 0; j < featureFractureList->size();j++){
                if (featureFractureList->at(j).feature != 0){
                    if (featureFractureList->at(j).feature->getName()==featureList->at(i).getName()){
                        featureLengthSum += featureFractureList->at(j).getLength();
                    }
                }
            }

            featurePercentage->replace(i,featureLengthSum);
            STNode *item = this;
            while (item->parent()!=0){
                item = static_cast<STNode*>(item->parent());
                item->featurePercentage->replace(i,item->featurePercentage->at(i)+ featurePercentage->at(i));
            }
        }
    }
}

void STNode::setPath(QString p){
    path = p;
}

QString STNode::getPath(){
    return path;
}



