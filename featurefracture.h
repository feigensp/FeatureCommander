#ifndef FEATUREFRACTURE_H
#define FEATUREFRACTURE_H

#include "feature.h"
#include <QTreeWidgetItem>


/*
*Klasse Featureanteil
*Jeder STNode enthält eine Liste von Feature-Fractures.
*/
class FeatureFracture
{
public:
    FeatureFracture(Feature *f);
    FeatureFracture(Feature *f, int chars, int charOffset, int numberOfFeaturesAssignedToThisPart);
    FeatureFracture(const FeatureFracture &f);
    ~FeatureFracture();

    Feature* getFeature();
    void setLength(int chars);
    int getLength();
    void setOffset(int charOffset);
    int getOffset();
    void setNumberOfFeaturesAssignedToThisPart(int n);
    int getNumberOfFeaturesAssignedToThisPart();

    void assignToNode(QTreeWidgetItem *n);
    QTreeWidgetItem* getAssignedNode();
    int offset;
    int length;
    Feature *feature;
    QString completeName;
private:
    //Feature *feature;
    //int length;
    //int offset;

    int numberOfFeaturesAssignedToThisPart;

    //QTreeWidgetItem(STNode), dem das FF zugewiesen wird (vielleicht nicht nötig)
    QTreeWidgetItem *assignedNode;

};

#endif // FEATUREFRACTURE_H
