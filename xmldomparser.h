#ifndef XMLDOMPARSER_H
#define XMLDOMPARSER_H

#include <QTreeWidget>
#include <QDomElement>
#include "stnode.h"
#include <QList>
#include "feature.h"
#include "featurefracture.h"
#include <vector>
#include "smvtreewidget.h"
#include <QFile>
#include "stnodecolordistribution.h"
#include "itemdelegate.h"


class XmlDomParser
{
public:

            //SMVTreeWidget
    XmlDomParser(SMVTreeWidget *treePV, SMVTreeWidget *treeFV, vector <Feature> *list);
    ~XmlDomParser();


    /*
    * - Einlesen des xml-Files
    * - Anfügen der Knoten STNodes an das QTreeWidget
    * - Zuweisen einer FeatureFractureList an alle Knoten des Baums
    */
    bool readFile(QString &fileName);

    /*
    *- Ermitteln der Zeichengesamtzanzahl für Java-Files (Zählen direkt in der Datei)
    *- Berechnen der Zeichengesamtzanzahl für alle andere Knoten
    */
    void countTotalCharsAndAssignToSTNodes(QString &dirName);

    /*
    * -Zeichnen des Hintergrunds für jeden Knoten
    */
    void generateSTNodeTextures(int width);
    void updateSTNodeTextures(Feature *feature);

    void calculateWhiteSpaceForAllSTNodes();
    void fillFeatureViewTreeWidget(MainWindow *mw);

    //Methode gibt Speicher frei: delete aller STNodes (inkl. FF-Lists) des Baums
    //für den Fall, dass delete QTreeWidget seine Items nicht als STNodes sondern als QTreeWidgetItems löscht
    //ist noch zu überarbeiten
    void freeMemory();

private:
    //TreeWidget, das anhand des xml-Files aufgebaut wird

    SMVTreeWidget *treeWidgetPackageView;
    SMVTreeWidget *treeWidgetFeatureView;

    //Liste aller im Projekt vorkommenen Features
    vector <Feature> *featureList;

    // Methode liest Project-Tag ein um handelt es
    void parseProject(const QDomElement &projectElement, STNode *parent);
    // Methode liest Folder-Tag ein um handelt es
    void parseFolder(const QDomElement &folderElement, STNode *parent);
    void parseFile(const QDomElement &fileElement, STNode *parent);
    void parseFeature(const QDomElement &domParent, const QDomElement &featureElement, STNode *parent);
    void parseFragment(const QDomElement &fragmentElement, STNode *parent);

    //Methode löscht leere Ordner
    void deleteEmptyFolders(STNode *root);

    //Methode reduziert den treeWidgetFeatureView sodass, nur STNodes am Baum hängen, die zum konkreten Feature gehören
    void reduceTreeWidgetFeatureView();
    void removeChildren(STNode *currentNode);

    bool isLineBased;

    ////////statische Hilfsmethoden

    //Testen, ob sich element in Vektor v befindet
    template <typename T>
    static bool containsElement (vector <T> v, T element);

    //Methode liefert der Dateipfad der Java-Datei des Names nodeName
    //Ermittlung der Pfades anhand des RootDirectory
    static QString getcorrespondingJavaFileName(QString &nodeName, QString &rootSourceDir);

    int getTotalCharCountOfFile(QString &javaFileName);

    //static
    Feature* getCorrespondingFeature(QString featureName);
    QList <Feature*>* getCorrespondingFeatures(QString featureName);

};

#endif // XMLDOMPARSER_H
