#ifndef SAVECOLORASSIGNMENT_H
#define SAVECOLORASSIGNMENT_H

#include "featuretreewidget.h"
#include "color.h"
#include <QList>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QTextStream>
#include "mytreewidgetitem.h"
#include "mylistwidgetitem.h"
#include "colormanager.h"
#include <QObject>
#include "loadbutton.h"
class MainWindow;

class SaveColorAssignment : public QWidget
{
    Q_OBJECT
public:
    SaveColorAssignment(QWidget *parent = 0,MainWindow *mw = 0,QIcon *icon = 0,QFrame *f = 0,QList<Color*> *c = 0,vector <FeatureColorPair> *fcp = 0,ColorManager *man = 0,QString *path = 0);
private:
    QList <Color*> *colorArray;
    //QListWidget *listWidget;
    //FeatureTreeWidget *featureTree;
    vector <FeatureColorPair> *FCPList;
    QFrame *frame;
    LoadButton *load;
    ColorManager *manager;
public slots:
    void loadC();
signals:

};

#endif // SAVECOLORASSIGNMENT_H
