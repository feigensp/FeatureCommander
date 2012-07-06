#include "colormanager.h"

ColorManager* ColorManager::aktColormanager = 0;

ColorManager::ColorManager(vector < Feature> *fList, int colorCount)
{
    aktColormanager = this;
    colorArray = new QList <Color*>;
    defaultGrey1 = new Color(QColor(220, 220, 220, 255)); //silver
    defaultGrey2 = new Color(QColor(180, 180, 180, 255)); //grey
    white = new Color(QColor(255, 255, 255, 255));
    maxColorCount = 200;//muss noch ge�ndert werden
    dummyToDoMod2 = 0;
    featureList = fList;
    FCPList = new vector <FeatureColorPair>();
    fillColorArray(colorCount);
    initializeFCPList();
}

ColorManager::ColorManager(){

}

ColorManager::~ColorManager(){
    delete colorArray;
    delete defaultGrey1;
    delete defaultGrey2;
    delete white;
    delete FCPList;
}

void ColorManager::setMaxColorCount(int i){
    maxColorCount = i;
}

int ColorManager::getMaxColorCount(){
    return maxColorCount;
}

void ColorManager::fillColorArray(int n){
    colorArray->clear();
    int colorsToCreate = 0;

    if(n>maxColorCount)
        colorsToCreate = maxColorCount;
    else colorsToCreate = n;


    //der Hue-Wert befindet sich im Intervall von 0 bis 360 Grad
    //360 an colorsToCreate Farben aufteilen
    double degree = 360.0/(double)colorsToCreate;
    double currentDegree = 0;
    for(int i=0; i<colorsToCreate; i++){
        QColor color(0, 0, 0);
        color.convertTo(QColor::Hsv);
        color.setHsv(currentDegree, 170, 255);
        Color *myColor = new Color(color);

        myColor->setCustom(false);
        colorArray->push_back(myColor);

        currentDegree += degree;
    }

}

void ColorManager::initializeFCPList(){


    for(int i=0; i<featureList->size(); i++){
        featureList->at(i).index = i;
        if(dummyToDoMod2%2 == 0){
            FCPList->push_back(FeatureColorPair(&(featureList->at(i)), defaultGrey1));
        }
        else{
            FCPList->push_back(FeatureColorPair(&(featureList->at(i)), defaultGrey2));
        }
        dummyToDoMod2++;
    }

}

Color* ColorManager::getColorForFeature(Feature *f){
    for (int i = 0; i<FCPList->size(); i++){
        if(FCPList->at(i).feature == f) return FCPList->at(i).color;
    }
    std::cout << "FCPListSize:  " << FCPList->size() << endl;
    std::cout << "Feature "<< f->getName().toStdString()<< "existiert nicht in der Feature-Color-Pair-liste." << std::endl;
    return white;
}

Feature* ColorManager::getFeatureForColor(Color *c){
    if (!c->isAvailable()){
        for (int i = 0; i<FCPList->size(); i++){
            if(FCPList->at(i).color == c)
                return FCPList->at(i).feature;
        }
    }
    std::cout << "Farbe existiert nicht in der Feature-Color-Pair-liste." << std::endl;
    return 0;
}

bool ColorManager::setColorForFeature(Feature *f, Color *c){

    //wenn Farbe bereits vergeben, setze die Farbe des alten Features zurück
    //if(this->getFeatureForColor(c) != 0){
    if (!c->isAvailable()){
        std::cout << "zurück setzen." << std::endl;
        this->deleteColorForFeature(this->getFeatureForColor(c));
    }
    //if(this->FCPListContainsColor(c))
    if(!colorArray->contains(c)){
        std::cout << "Color existiert nicht im ColorArray." << std::endl;
        return false;
    }

    //if(FCPListContainsColor(c)){
    if(!c->isAvailable()){
        std::cout << "Color ist bereits vergeben." << std::endl;
        return false;
    }
    int posFeature = FCPListContainsFeature(f);
    if(posFeature>=0){
        FCPList->at(posFeature).color = c;
        //FCPList->erase(posFeature);
        //FCPList->insert(posFeature, FeatureColorPair(f, c));
        c->setAvailable(false);
        return true;
    }

    c->setAvailable(false);
    FCPList->push_back(FeatureColorPair(f, c));
    return true;

}

bool ColorManager::deleteColorForFeature(Feature *f){
    int posFeature = FCPListContainsFeature(f);
    if(posFeature<0){
        std::cout << "Farbe kann für Feature nicht gelöscht werden, da Feature nicht in der Pair-Liste vorkommt." << std::endl;
        return false;
    }
    if(dummyToDoMod2%2 == 0){
        FCPList->at(posFeature).color = defaultGrey1;
    }
    else{
        FCPList->at(posFeature).color = defaultGrey2;
    }

    dummyToDoMod2++;
    return true;
}

bool ColorManager::FCPListContainsPair(FeatureColorPair *p){
    for(int i=0; i<FCPList->size(); i++){
        if(FCPList->at(i) == *p) return true;
    }
    return false;
}

bool ColorManager::FCPListContainsColor(Color *c){
    for(int i = 0; i<FCPList->size(); i++){
        FeatureColorPair fcp = FCPList->at(i);
        if(fcp.color == c)
            return true;
    }
    return false;
}

int ColorManager::FCPListContainsFeature(Feature *f){
    for(int i=0; i<FCPList->size(); i++){
        FeatureColorPair fcp = FCPList->at(i);
        QString name = fcp.feature->getName();
        if (name == f->getName())
            return i;
    }
    return -1;
}

//vector <Color>* ColorManager::fillHierarchicalColorList(int n, double start, double end, vector <Color> *hierarchy)
//{
//    int colorsToCreate = n;
//
//    //der Hue-Wert befindet sich im Intervall von 0 bis 360 Grad
//    //360 an colorsToCreate Farben aufteilen
//    double range = end - start;
//    double degree = range/(double)(colorsToCreate);
//    double currentDegree = start;
//    double saturation = 255;
//    double value = 245;
//    double valueDegree = 145/(double)(colorsToCreate);
//    double saturationDegree = 100/(double)(colorsToCreate);
//
//
//    for(int i = 0; i < colorsToCreate; i++){
//        QColor color(0, 0, 0);
//        color.convertTo(QColor::Hsv);
//        if (degree > 15)
//            color.setHsv(currentDegree, 255, 240);
//        else
//            color.setHsv(currentDegree, saturation, value);
//        Color myColor(color);
//        hierarchy->push_back(myColor);
//        currentDegree += degree;
//            saturation-=saturationDegree;
//            value-=valueDegree;
//
//    }
//    return hierarchy;
//}

//vector <Color>* ColorManager::getHierarchicalColorList(QColor c, int colorCount){
////    vector <Color> *hierarchicalColorList = new vector <Color>();
////    //Elternfarbe hat Value von 1
////    //Kinderfarben können Value von 0.9 bis 0 haben
////    double valuePercentage = (c->getColor().value()-0.1)/colorCount;
////    double currentValue = 0.0;
////    for(int i=0; i<colorCount; i++){
////        QColor childQColor(255, 255, 255);
////        childQColor.setHsv(c->getColor().hue(), c->getColor().saturation(), currentValue, 255);
////        hierarchicalColorList->push_back(Color(childQColor));
////        currentValue += valuePercentage;
////    }
//    int colorArrayPosition = colorArray->indexOf(new Color(c));
//
//    vector <Color> *hierarchicalColorList = new vector<Color> ();
//    if (colorArrayPosition >= 0 && colorArrayPosition < colorArray->size()-1)
//        hierarchicalColorList = fillHierarchicalColorList(colorCount,c.hue(),
//                 colorArray->at(colorArrayPosition + 1).color.hue(),hierarchicalColorList);
//    else if (colorArrayPosition >= 0)
//        hierarchicalColorList = fillHierarchicalColorList(colorCount,c.hue(),360,hierarchicalColorList);
//
//    return hierarchicalColorList;
//}
