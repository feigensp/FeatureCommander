#ifndef STNODE_H
#define STNODE_H

#include <QTreeWidgetItem>
#include "feature.h"
#include "featurefracture.h"
#include <vector>
#include "stnodecolordistribution.h"
#include <QList>

class STNode : public QTreeWidgetItem
{
public:
    STNode(QTreeWidgetItem * parent, int type = Type);
    STNode(const QTreeWidgetItem &other);
    STNode( STNode &other, bool dummi);
    STNode *clone() const;


    enum NodeType {NON, PROJECT, FOLDER, FILE, FEATURE, FRAGMENT, FEATUREROOT};
    void setNodeType(NodeType t);
    NodeType getNodeType();

    void setFeatureList(vector <Feature> * FList);
    vector <Feature>* getFeatureList();
    void setFeatureFractureList(vector <FeatureFracture> *FFList);
    vector <FeatureFracture>* getFeatureFractureList();
    STNodeColorDistribution* getColorDistributionList();
    STNodeColorDistribution* getColorDistributionListFeatureView();
    //Methode addToFeatureFractureList fügt zur FFList ein Element hinzu
    //numberOfFeaturesAssignedToThisPart ist größer als 1, falls diesem Codeteil mehrere Features zugeordnet werden
    //Aufruf durch File-Knoten
    void addToFeatureFractureList(Feature *f, int chars, int charOffset, int numberOfFeaturesAssignedToThisPart);
    //Aufruf durch Folder-Knoten
    void addToFeatureFractureList(FeatureFracture ff);

    //Methode sollte von allen nicht-Kind-Knoten aufgerufen werden
    void calculateNumberOfTotalChars ();

    void setNumberOfTotalChars(int i);
    int getNumberOfTotalChars();
    int getWhiteSpace(int lineCount = 0);
    long whiteSpace;
    void addWhiteSpaceToParent(int white);
    //besseren Sortieralgorithmus!
    void sortFeatureFractureQList(bool sortOffset);

    QPixmap drawBackgroundImagePackageView(int width);
    QPixmap drawBackgroundImageFeatureView(Feature *f, int width, int indexOfFeature);
    QPixmap drawFeatureNodeBackgroundImage(Feature *f, int width, int indexOfFeature);

    QPixmap backgroundSave;
    bool isColored;

    //alle STNodes des Typs Project, File und Folder besitzen diese Liste, nicht Feature und Fragment
    vector <FeatureFracture> *featureFractureList;

    //Gesamtanteil des jeweiligen Features f�r diesen Knoten
    //Index = Index der featurelist
    QList <int> *featurePercentage;
    void calculateFeaturePercentage();

    QList <FeatureFracture>* getFeatureFractureQList();
    QList <FeatureFracture> *featureFractureQList;

    void setPath(QString p);
    QString getPath();
private:


    //speichert die Positionen der Features in der Hintergrundtextur (f�r bessere Performance)
    STNodeColorDistribution *colorDistributionList;
    STNodeColorDistribution *colorDistributionListFeatureView;

    NodeType type;

    //Anzahl der Codezeichen in der Datei/im Verzeichnis insgesamt
    int totalChars;

    //Liste aller im Projekt vorkommenen Features
    //Wird gebraucht, damit File-, Folder- und Project-Nodes ihren Hintergrund zeichnen können
    vector <Feature> *featureList;
    QString path;

};

#endif // STNODE_H
