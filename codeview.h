#ifndef CODEVIEW_H
#define CODEVIEW_H

#include <QTextEdit>
#include <QPlainTextEdit>
#include <QFile>
#include <QTabWidget>
#include <QBoxLayout>
#include <QGraphicsView>
#include "stnode.h"
#include <QGraphicsRectItem>
#include <QScrollBar>
#include "featurefracture.h"
#include <vector>
#include "sidebarfracture.h"
#include <QGraphicsLinearLayout>
#include <QGraphicsWidget>
#include "backgroundfracture.h"
#include "mycppsyntaxhighlighter.h"
#include "featuretreewidget.h"
#include "highlighter.h"

class CodeView : public QWidget
{
    Q_OBJECT
public:
    CodeView(FeatureTreeWidget *t,STNode *i,QWidget *parent = 0,QFile *f = 0, int opacity = 100);
    void resizeEvent(QResizeEvent *event);
    void updateColor(Feature *f = 0);
    void updateAllColors();
    void updateBackground();
    void setFeatureOpacity(int opacity);
    QPixmap *backgroundPix;
    void fillLineNumberWidget();
    void addFractureRectangles();
    void drawBackgroundFractures();
    QGraphicsTextItem *getEdit();
    QGraphicsScene *textScene;
    QGraphicsView *textView;
    QTextEdit *textEdit;
    QFile *file;
    QGraphicsView *lineNumbersView;
    QGraphicsScene *lineNumbersScene;
    QGraphicsTextItem *edit;
    bool justCreated;
private:
    SideBarFracture *root;
    QGraphicsView *sideBarView;
    QGraphicsScene *sideBarScene;
    QGraphicsView *rightSideBarView;
    FeatureTreeWidget *featureTree;




    int featureOpacity;
    STNode *treeItem;
};

#endif // CODEVIEW_H
