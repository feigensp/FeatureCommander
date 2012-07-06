#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include "featuretreewidget.h"
#include <QString>
#include "xmldomparser.h"
#include <QVector>
#include "mylistwidgetitem.h"
#include "savecolorassignment.h"
#include "codeview.h"
#include "questiondialog.h"

namespace Ui {
    class MainWindow;
    //kommentar
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    static QString path;
    static MainWindow* myMainWindow;
    ColorManager *colorManager;
    FeatureTreeWidget *t; //Feature Model
    XmlDomParser *parser;
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QVector <QListWidgetItem*> selectedListWidgetItems;
    QColorDialog *dialog;
    QListWidgetItem *lastSelectedListWidgetItem;
    QTreeWidgetItem *lastSelectedTreeWidgetItem;
    void drawSaveButtonIcon();

    void updateSMVTreeTexture(Feature *feature);
    void updateTextEditFileNode(STNode *node);
    int checkBoxWidth;
    QuestionDialog *questionDialog;
    void setFilePath();
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void removeColorAssignment(MyTreeWidgetItem *item);
    void closeEvent(QCloseEvent *event);


public slots:
    void highlightColor(QListWidgetItem *item);
//    void highlightTreeWidget(QTreeWidgetItem *item, int column);
    void explorerToggled(bool toggled);
    void showColorArray();
    void customColorDialog();
    void closeCustomColorDialog();
    void showListWidgetContextMenu(QPoint p);
    void showFeatureModelContextMenu(QPoint p);
    void deleteColorFromColorArray();
    void resetListWidget();
    void saveColors();
    void loadColors();
    void openFile(QTreeWidgetItem *item);
    void closeTab(int tab);
    void showFeatureFractureList(QTreeWidgetItem* item);
    void updateTabColors(int currentIndex);
    void setFeatureOpacity(int opacity);
    void removeColorAssignment();
    void updateAllColors();
    //Finder-Slots
    void search();
    void removeFinds();
    void openFileFromListWidget(QListWidgetItem *item);
    void resetLastSearch();
    void writeToLogFileOpened();
    void writeToLogSaturationChanged();
    void searchInFeatureModel();
//    void showTimeMessage();
protected:
    void changeEvent(QEvent *e);
    void initializeListWidget();

private:
    Ui::MainWindow *ui;
    bool featureModelshown;
    bool colorPickerShown;
    bool saveLoadShown;

    //Finder (FeatureModel)
    QTreeWidgetItem *lastFeatureModelItem;
    QString lastFeatureSearch;
    //Finder
    QString lastSearch;
    QList <QGraphicsRectItem*> *finds;
    int findsIndex;
    CodeView *lastCodeView;
    QList <QTreeWidgetItem*> *fileNodes;
    int findLine(QTextCursor cursor,int findPos);
    int calculateXPos(QTextCursor cursor,QTextDocument *doc,QFontMetrics metrics);
    bool searchCurrentFile();
    int time;
};


#endif // MAINWINDOW_H
