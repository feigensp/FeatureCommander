#include "featurefracture.h"
#include "stnode.h"

FeatureFracture::FeatureFracture(Feature* f, int chars, int charOffset, int nrOfFeaturesAssignedToThisPart)
{
    feature = f;
    length = chars;
    offset = charOffset;
    numberOfFeaturesAssignedToThisPart = nrOfFeaturesAssignedToThisPart;
    completeName = "";

}

FeatureFracture::FeatureFracture(const FeatureFracture &f){
    feature = f.feature;
    length = f.length;
    offset = f.offset;
    numberOfFeaturesAssignedToThisPart = f.numberOfFeaturesAssignedToThisPart;
    completeName = f.completeName;
}

FeatureFracture::FeatureFracture(Feature* f)
{
    feature = f;
    length = 0;
    offset = 0;
    numberOfFeaturesAssignedToThisPart = 0;
    completeName = "";
}

FeatureFracture::~FeatureFracture(){};

Feature* FeatureFracture::getFeature(){
    return feature;
}

void FeatureFracture::setLength(int chars){
    length = chars;
}

int FeatureFracture::getLength(){
    return length;
}

void FeatureFracture::setOffset(int charOffset){
    offset = charOffset;
}

int FeatureFracture::getOffset(){
    return offset;
}

void FeatureFracture::setNumberOfFeaturesAssignedToThisPart(int n){
    numberOfFeaturesAssignedToThisPart = n;
}

int FeatureFracture::getNumberOfFeaturesAssignedToThisPart(){
    return numberOfFeaturesAssignedToThisPart;
}

void FeatureFracture::assignToNode(QTreeWidgetItem *n){
    assignedNode = static_cast <STNode*> (n);
}

QTreeWidgetItem* FeatureFracture::getAssignedNode(){
    return assignedNode;
}
