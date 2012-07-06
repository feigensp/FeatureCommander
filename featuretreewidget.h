#ifndef FEATURETREEWIDGET_H
#define FEATURETREEWIDGET_H

#include <QTreeWidget>
//#include "mainwindow.h"
#include "feature.h"
#include "colormanager.h"
#include "mytreewidgetitem.h"
#include "mylistwidgetitem.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class MainWindow;

//! [0]
class FeatureTreeWidget : public QTreeWidget
{
     Q_OBJECT
public:
    QTreeWidgetItem *root;
    QListWidget *listWidget;
    ColorManager *colorManager;
    FeatureTreeWidget(QWidget *parent = 0, QFile *file = 0,QListWidget *listWidget = 0 ,ColorManager *colorManager = 0, MainWindow *mw = 0);
    void addChildren(QTreeWidgetItem *item, QStringList children);
    void createFeatureList ();
    vector <Feature>* getFeatureList();
    QList <QTreeWidgetItem*> findBackGroundColor(QColor background,QTreeWidgetItem *item, QList <QTreeWidgetItem*> *list);
    void setColorManager(ColorManager *cm);
    MainWindow *mainWindow;
    void redrawListWidget();
    void setCheckboxes(QTreeWidgetItem *item);
    void updateChildrenCheckboxes(QTreeWidgetItem *item);
    Feature* getCorrespondingFeature(QString featureName);
    void unselect();
    void updateEditorGeometries();
    void assignColorFromSMVTreeWidget(QString featureName);
    QTreeWidgetItem *getItemFromFeatureName(QString featureName);


protected:
    void dropEvent(QDropEvent *event);
    void dragMoveEvent (QDragMoveEvent *event);
    QTreeWidgetItem* findTreeWidgetItem(QTreeWidgetItem *item, QString name);

private:
    vector <Feature> *featureList;


public slots:
    void removeColorAssignment();
    void updateCheckboxes(QTreeWidgetItem *item);
    void assignAutomatically();
    void removeColorAssignmentFromSelection();
signals:

};
//! [0]

#endif // FEATURETREEWIDGET_H
