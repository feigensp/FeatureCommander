#include "feature.h"
#include "colormanager.h"
#include <string>
using namespace std;

Feature::Feature(QString featureName){
    name = featureName;
}

Feature::~Feature(){}

QString Feature::getName(){
    return name;
}
Color* Feature::getColor(){
    return ColorManager::aktColormanager->getColorForFeature(this);
}

bool Feature::operator ==(Feature *f){
    return (this->name == f->getName());
}

bool Feature::operator ==(Feature &f){
    return (this->name == f.getName());
}

const bool Feature::operator <(Feature &f){
    return (this->name < f.getName());
}
