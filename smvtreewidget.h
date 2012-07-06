#ifndef SMVTREEWIDGET_H
#define SMVTREEWIDGET_H


#include <QTreeWidget>
#include <QWidget>
#include <iostream>

#include "colormanager.h"
#include "stnode.h"
#include "itemdelegate.h"

class MainWindow;
class SMVTreeWidget : public QTreeWidget
{
    Q_OBJECT

private:
    ColorManager *colorManager;

public:
    SMVTreeWidget(QWidget *parent=0);
    //~SMVTreeWidget();
    //SMVTreeWidget(SMVTreeWidget *tree);
    void copyTree1(SMVTreeWidget *copy);
    static void copyTree(STNode *rootOrigTree, STNode *rootCopyTree);
    static void copyNode(STNode *original, STNode *copyNodesParent);
    void setColorManager(ColorManager *cm);
    ColorManager* getColorManager();
    //void setMainWindow(MainWindow *mw);
    //MainWindow* getMainWindow();
    void resizeEvent(QResizeEvent *event);
    void resize(int width, int height = 0);
    void leaveEvent(QEvent *event);
    bool isFeatureView;
    FeatureTreeWidget *featureTreeWidget;
    void setFeatureTreeWidget(FeatureTreeWidget *f);
    void dropEvent(QDropEvent *event);




public slots:
    void openFile(QTreeWidgetItem * item, int i);
    void updateTexture();
    void hoverEnter(QModelIndex index);
    void resizeRowHeight(QModelIndex index);
//    void expandItem ( const QTreeWidgetItem * item );
    //void updateTextures();

signals:

};

#endif // SMVTREEWIDGET_H
