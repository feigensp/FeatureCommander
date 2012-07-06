/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu 5. Jul 20:07:52 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "smvtreewidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionPackage_and_FeatureView;
    QAction *actionFeature_Model;
    QAction *actionSave_Load;
    QAction *actionColorPicker;
    QAction *actionQuestions;
    QAction *actionColorSaves;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_7;
    QFrame *frame_central;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QFrame *frame_slider;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *toolButton_light;
    QSlider *horizontalSlider;
    QToolButton *toolButton_dark;
    QFrame *line_2;
    QToolButton *toolButton_finder;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QWidget *tab_2;
    QMenuBar *menuBar;
    QMenu *menuAnsicht;
    QMenu *menuColorSaves;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget_left;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton_features;
    QRadioButton *radioButton_packages;
    QSpacerItem *horizontalSpacer_2;
    QStackedWidget *stackedWidget;
    QWidget *page_packageView;
    QGridLayout *gridLayout_6;
    SMVTreeWidget *treeWidget_packageView;
    QWidget *page_featureView;
    QGridLayout *gridLayout;
    SMVTreeWidget *treeWidget_featureView;
    QDockWidget *dockWidget_featureModel;
    QWidget *dockWidgetContents_3;
    QVBoxLayout *verticalLayout;
    QFrame *frame_featureModel;
    QVBoxLayout *verticalLayout_10;
    QFrame *frame_featureSearch;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEdit_featureSearch;
    QToolButton *toolButton_featureSearch;
    QDockWidget *dockWidget_colors;
    QWidget *dockWidgetContents_4;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_radio;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_resetColors;
    QToolButton *toolButton_auto;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *toolButton_2;
    QToolButton *toolButton_removeAssignment;
    QListWidget *listWidget;
    QDockWidget *dockWidget_colorAssignments;
    QWidget *dockWidgetContents_5;
    QGridLayout *gridLayout_5;
    QFrame *line;
    QToolButton *toolButton_save;
    QFrame *frame_loadButtons;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QDockWidget *dockWidget_finder;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_7;
    QFrame *frame_find;
    QGridLayout *gridLayout_4;
    QLineEdit *lineEdit_find;
    QPushButton *pushButton_find;
    QLabel *label_2;
    QFrame *frame_options;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame_radiobuttons;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *radioButton_current;
    QRadioButton *radioButton_project;
    QFrame *frame_wholeCase;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *checkBox_wholeWords;
    QCheckBox *checkBox_caseSensitive;
    QListWidget *listWidget_results;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents_6;
    QVBoxLayout *verticalLayout_9;
    QListWidget *listWidget_3;
    QListWidget *listWidget_2;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton;
    QLabel *label_startline;
    QLabel *label_endline;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(900, 770);
        MainWindow->setIconSize(QSize(15, 15));
        MainWindow->setTabShape(QTabWidget::Rounded);
        actionPackage_and_FeatureView = new QAction(MainWindow);
        actionPackage_and_FeatureView->setObjectName(QString::fromUtf8("actionPackage_and_FeatureView"));
        actionPackage_and_FeatureView->setCheckable(true);
        actionPackage_and_FeatureView->setChecked(true);
        actionFeature_Model = new QAction(MainWindow);
        actionFeature_Model->setObjectName(QString::fromUtf8("actionFeature_Model"));
        actionFeature_Model->setCheckable(true);
        actionFeature_Model->setChecked(true);
        actionSave_Load = new QAction(MainWindow);
        actionSave_Load->setObjectName(QString::fromUtf8("actionSave_Load"));
        actionSave_Load->setCheckable(true);
        actionSave_Load->setChecked(true);
        actionColorPicker = new QAction(MainWindow);
        actionColorPicker->setObjectName(QString::fromUtf8("actionColorPicker"));
        actionColorPicker->setCheckable(true);
        actionColorPicker->setChecked(true);
        actionQuestions = new QAction(MainWindow);
        actionQuestions->setObjectName(QString::fromUtf8("actionQuestions"));
        actionQuestions->setCheckable(false);
        actionQuestions->setChecked(false);
        actionColorSaves = new QAction(MainWindow);
        actionColorSaves->setObjectName(QString::fromUtf8("actionColorSaves"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_7 = new QHBoxLayout(centralWidget);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        frame_central = new QFrame(centralWidget);
        frame_central->setObjectName(QString::fromUtf8("frame_central"));
        frame_central->setFrameShape(QFrame::NoFrame);
        frame_central->setFrameShadow(QFrame::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_central);
        verticalLayout_5->setSpacing(2);
        verticalLayout_5->setContentsMargins(1, 1, 1, 1);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label = new QLabel(frame_central);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_5->addWidget(label);

        frame_slider = new QFrame(frame_central);
        frame_slider->setObjectName(QString::fromUtf8("frame_slider"));
        frame_slider->setFrameShape(QFrame::NoFrame);
        frame_slider->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_slider);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        toolButton_light = new QToolButton(frame_slider);
        toolButton_light->setObjectName(QString::fromUtf8("toolButton_light"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/opacity1.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_light->setIcon(icon);
        toolButton_light->setIconSize(QSize(25, 25));
        toolButton_light->setCheckable(false);
        toolButton_light->setChecked(false);
        toolButton_light->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_light);

        horizontalSlider = new QSlider(frame_slider);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy);
        horizontalSlider->setMaximum(255);
        horizontalSlider->setValue(170);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        toolButton_dark = new QToolButton(frame_slider);
        toolButton_dark->setObjectName(QString::fromUtf8("toolButton_dark"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/opacity2.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_dark->setIcon(icon1);
        toolButton_dark->setIconSize(QSize(25, 25));
        toolButton_dark->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_dark);

        line_2 = new QFrame(frame_slider);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        toolButton_finder = new QToolButton(frame_slider);
        toolButton_finder->setObjectName(QString::fromUtf8("toolButton_finder"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/lupe.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_finder->setIcon(icon2);
        toolButton_finder->setIconSize(QSize(25, 25));
        toolButton_finder->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_finder);


        verticalLayout_5->addWidget(frame_slider);

        tabWidget = new QTabWidget(frame_central);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tab_2->setEnabled(true);
        tabWidget->addTab(tab_2, QString());

        verticalLayout_5->addWidget(tabWidget);


        horizontalLayout_7->addWidget(frame_central);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 900, 21));
        menuAnsicht = new QMenu(menuBar);
        menuAnsicht->setObjectName(QString::fromUtf8("menuAnsicht"));
        menuColorSaves = new QMenu(menuBar);
        menuColorSaves->setObjectName(QString::fromUtf8("menuColorSaves"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget_left = new QDockWidget(MainWindow);
        dockWidget_left->setObjectName(QString::fromUtf8("dockWidget_left"));
        dockWidget_left->setMinimumSize(QSize(300, 242));
        dockWidget_left->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidget_left->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame = new QFrame(dockWidgetContents_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 3, -1, 3);
        radioButton_features = new QRadioButton(frame);
        radioButton_features->setObjectName(QString::fromUtf8("radioButton_features"));
        radioButton_features->setChecked(false);

        horizontalLayout_2->addWidget(radioButton_features);

        radioButton_packages = new QRadioButton(frame);
        radioButton_packages->setObjectName(QString::fromUtf8("radioButton_packages"));
        radioButton_packages->setChecked(true);

        horizontalLayout_2->addWidget(radioButton_packages);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_3->addWidget(frame);

        stackedWidget = new QStackedWidget(dockWidgetContents_2);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        stackedWidget->setMinimumSize(QSize(300, 0));
        page_packageView = new QWidget();
        page_packageView->setObjectName(QString::fromUtf8("page_packageView"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(page_packageView->sizePolicy().hasHeightForWidth());
        page_packageView->setSizePolicy(sizePolicy2);
        gridLayout_6 = new QGridLayout(page_packageView);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        treeWidget_packageView = new SMVTreeWidget(page_packageView);
        treeWidget_packageView->setObjectName(QString::fromUtf8("treeWidget_packageView"));
        treeWidget_packageView->setFrameShape(QFrame::StyledPanel);
        treeWidget_packageView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        treeWidget_packageView->setSelectionMode(QAbstractItemView::NoSelection);
        treeWidget_packageView->header()->setVisible(false);

        gridLayout_6->addWidget(treeWidget_packageView, 0, 0, 1, 1);

        stackedWidget->addWidget(page_packageView);
        page_featureView = new QWidget();
        page_featureView->setObjectName(QString::fromUtf8("page_featureView"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(page_featureView->sizePolicy().hasHeightForWidth());
        page_featureView->setSizePolicy(sizePolicy3);
        gridLayout = new QGridLayout(page_featureView);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        treeWidget_featureView = new SMVTreeWidget(page_featureView);
        treeWidget_featureView->setObjectName(QString::fromUtf8("treeWidget_featureView"));
        sizePolicy3.setHeightForWidth(treeWidget_featureView->sizePolicy().hasHeightForWidth());
        treeWidget_featureView->setSizePolicy(sizePolicy3);
        treeWidget_featureView->setMinimumSize(QSize(0, 0));
        treeWidget_featureView->setFrameShape(QFrame::StyledPanel);
        treeWidget_featureView->setDragDropMode(QAbstractItemView::DropOnly);
        treeWidget_featureView->setSelectionMode(QAbstractItemView::NoSelection);
        treeWidget_featureView->setUniformRowHeights(true);
        treeWidget_featureView->setHeaderHidden(true);
        treeWidget_featureView->header()->setVisible(false);

        gridLayout->addWidget(treeWidget_featureView, 0, 0, 1, 1);

        stackedWidget->addWidget(page_featureView);

        verticalLayout_3->addWidget(stackedWidget);

        dockWidget_left->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_left);
        dockWidget_featureModel = new QDockWidget(MainWindow);
        dockWidget_featureModel->setObjectName(QString::fromUtf8("dockWidget_featureModel"));
        dockWidget_featureModel->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidget_featureModel->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        verticalLayout = new QVBoxLayout(dockWidgetContents_3);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_featureModel = new QFrame(dockWidgetContents_3);
        frame_featureModel->setObjectName(QString::fromUtf8("frame_featureModel"));
        frame_featureModel->setFrameShape(QFrame::NoFrame);
        frame_featureModel->setFrameShadow(QFrame::Raised);
        verticalLayout_10 = new QVBoxLayout(frame_featureModel);
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));

        verticalLayout->addWidget(frame_featureModel);

        frame_featureSearch = new QFrame(dockWidgetContents_3);
        frame_featureSearch->setObjectName(QString::fromUtf8("frame_featureSearch"));
        frame_featureSearch->setFrameShape(QFrame::NoFrame);
        frame_featureSearch->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_featureSearch);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(2, 0, 2, 0);
        lineEdit_featureSearch = new QLineEdit(frame_featureSearch);
        lineEdit_featureSearch->setObjectName(QString::fromUtf8("lineEdit_featureSearch"));

        horizontalLayout_6->addWidget(lineEdit_featureSearch);

        toolButton_featureSearch = new QToolButton(frame_featureSearch);
        toolButton_featureSearch->setObjectName(QString::fromUtf8("toolButton_featureSearch"));
        toolButton_featureSearch->setIcon(icon2);
        toolButton_featureSearch->setIconSize(QSize(20, 20));
        toolButton_featureSearch->setAutoRaise(true);

        horizontalLayout_6->addWidget(toolButton_featureSearch);


        verticalLayout->addWidget(frame_featureSearch);

        dockWidget_featureModel->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_featureModel);
        dockWidget_colors = new QDockWidget(MainWindow);
        dockWidget_colors->setObjectName(QString::fromUtf8("dockWidget_colors"));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QString::fromUtf8("dockWidgetContents_4"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents_4);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 1, 2, 1);
        frame_radio = new QFrame(dockWidgetContents_4);
        frame_radio->setObjectName(QString::fromUtf8("frame_radio"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(frame_radio->sizePolicy().hasHeightForWidth());
        frame_radio->setSizePolicy(sizePolicy4);
        frame_radio->setFrameShape(QFrame::NoFrame);
        frame_radio->setFrameShadow(QFrame::Raised);
        frame_radio->setLineWidth(1);
        gridLayout_3 = new QGridLayout(frame_radio);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(5);
        gridLayout_3->setContentsMargins(9, 0, -1, 0);
        pushButton_resetColors = new QPushButton(frame_radio);
        pushButton_resetColors->setObjectName(QString::fromUtf8("pushButton_resetColors"));

        gridLayout_3->addWidget(pushButton_resetColors, 1, 6, 1, 1);

        toolButton_auto = new QToolButton(frame_radio);
        toolButton_auto->setObjectName(QString::fromUtf8("toolButton_auto"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/spectrum_small.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_auto->setIcon(icon3);
        toolButton_auto->setIconSize(QSize(30, 30));
        toolButton_auto->setAutoRaise(true);
        toolButton_auto->setArrowType(Qt::NoArrow);

        gridLayout_3->addWidget(toolButton_auto, 1, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        toolButton_2 = new QToolButton(frame_radio);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_2->setIcon(icon4);
        toolButton_2->setIconSize(QSize(30, 30));
        toolButton_2->setAutoRaise(true);

        gridLayout_3->addWidget(toolButton_2, 1, 5, 1, 1);

        toolButton_removeAssignment = new QToolButton(frame_radio);
        toolButton_removeAssignment->setObjectName(QString::fromUtf8("toolButton_removeAssignment"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/crossShadow.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_removeAssignment->setIcon(icon5);
        toolButton_removeAssignment->setIconSize(QSize(30, 30));
        toolButton_removeAssignment->setAutoRaise(true);

        gridLayout_3->addWidget(toolButton_removeAssignment, 1, 4, 1, 1);


        verticalLayout_2->addWidget(frame_radio);

        listWidget = new QListWidget(dockWidgetContents_4);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/leer.png"), QSize(), QIcon::Normal, QIcon::On);
        icon6.addFile(QString::fromUtf8(":/images/lupe.png"), QSize(), QIcon::Selected, QIcon::Off);
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setBackground(brush);
        __qlistwidgetitem->setIcon(icon6);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/leer.png"), QSize(), QIcon::Normal, QIcon::On);
        QBrush brush1(QColor(200, 40, 30, 255));
        brush1.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setBackground(brush1);
        __qlistwidgetitem1->setIcon(icon7);
        QBrush brush2(QColor(80, 90, 200, 255));
        brush2.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidget);
        __qlistwidgetitem2->setBackground(brush2);
        __qlistwidgetitem2->setIcon(icon7);
        QBrush brush3(QColor(255, 67, 252, 255));
        brush3.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(listWidget);
        __qlistwidgetitem3->setBackground(brush3);
        __qlistwidgetitem3->setIcon(icon7);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/leer.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon8.addFile(QString::fromUtf8(":/images/lupe.png"), QSize(), QIcon::Selected, QIcon::Off);
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::NoBrush);
        QBrush brush5(QColor(255, 184, 3, 255));
        brush5.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(listWidget);
        __qlistwidgetitem4->setBackground(brush5);
        __qlistwidgetitem4->setForeground(brush4);
        __qlistwidgetitem4->setIcon(icon8);
        QBrush brush6(QColor(255, 247, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(listWidget);
        __qlistwidgetitem5->setBackground(brush6);
        __qlistwidgetitem5->setIcon(icon8);
        QBrush brush7(QColor(164, 221, 6, 255));
        brush7.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem6 = new QListWidgetItem(listWidget);
        __qlistwidgetitem6->setBackground(brush7);
        __qlistwidgetitem6->setIcon(icon8);
        QBrush brush8(QColor(13, 184, 1, 255));
        brush8.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem7 = new QListWidgetItem(listWidget);
        __qlistwidgetitem7->setBackground(brush8);
        __qlistwidgetitem7->setIcon(icon8);
        QBrush brush9(QColor(10, 176, 252, 255));
        brush9.setStyle(Qt::SolidPattern);
        QListWidgetItem *__qlistwidgetitem8 = new QListWidgetItem(listWidget);
        __qlistwidgetitem8->setBackground(brush9);
        __qlistwidgetitem8->setIcon(icon8);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy5);
        listWidget->setMinimumSize(QSize(50, 50));
        QPalette palette;
        QBrush brush10(QColor(190, 190, 190, 0));
        brush10.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush10);
        QBrush brush11(QColor(226, 226, 226, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush11);
        QBrush brush12(QColor(190, 190, 190, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush12);
        listWidget->setPalette(palette);
        listWidget->setFocusPolicy(Qt::WheelFocus);
        listWidget->setAcceptDrops(true);
        listWidget->setDragEnabled(true);
        listWidget->setDragDropMode(QAbstractItemView::InternalMove);
        listWidget->setDefaultDropAction(Qt::CopyAction);
        listWidget->setGridSize(QSize(30, 30));
        listWidget->setViewMode(QListView::IconMode);
        listWidget->setUniformItemSizes(false);
        listWidget->setBatchSize(100);
        listWidget->setWordWrap(false);

        verticalLayout_2->addWidget(listWidget);

        dockWidget_colors->setWidget(dockWidgetContents_4);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_colors);
        dockWidget_colorAssignments = new QDockWidget(MainWindow);
        dockWidget_colorAssignments->setObjectName(QString::fromUtf8("dockWidget_colorAssignments"));
        dockWidget_colorAssignments->setFloating(false);
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QString::fromUtf8("dockWidgetContents_5"));
        gridLayout_5 = new QGridLayout(dockWidgetContents_5);
        gridLayout_5->setSpacing(2);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(2, 1, 2, 1);
        line = new QFrame(dockWidgetContents_5);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line, 0, 1, 1, 1);

        toolButton_save = new QToolButton(dockWidgetContents_5);
        toolButton_save->setObjectName(QString::fromUtf8("toolButton_save"));
        sizePolicy.setHeightForWidth(toolButton_save->sizePolicy().hasHeightForWidth());
        toolButton_save->setSizePolicy(sizePolicy);
        toolButton_save->setBaseSize(QSize(0, 0));
        toolButton_save->setIconSize(QSize(30, 30));
        toolButton_save->setAutoRaise(true);
        toolButton_save->setArrowType(Qt::NoArrow);

        gridLayout_5->addWidget(toolButton_save, 0, 0, 1, 1);

        frame_loadButtons = new QFrame(dockWidgetContents_5);
        frame_loadButtons->setObjectName(QString::fromUtf8("frame_loadButtons"));
        frame_loadButtons->setLayoutDirection(Qt::RightToLeft);
        frame_loadButtons->setFrameShape(QFrame::NoFrame);
        frame_loadButtons->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_loadButtons);
        horizontalLayout_4->setSpacing(3);
        horizontalLayout_4->setContentsMargins(3, 3, 3, 3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        gridLayout_5->addWidget(frame_loadButtons, 0, 2, 1, 1);

        dockWidget_colorAssignments->setWidget(dockWidgetContents_5);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_colorAssignments);
        dockWidget_finder = new QDockWidget(MainWindow);
        dockWidget_finder->setObjectName(QString::fromUtf8("dockWidget_finder"));
        dockWidget_finder->setFloating(false);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_7 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        frame_find = new QFrame(dockWidgetContents);
        frame_find->setObjectName(QString::fromUtf8("frame_find"));
        frame_find->setFrameShape(QFrame::NoFrame);
        frame_find->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_find);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(3, 3, 3, 3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(6);
        gridLayout_4->setVerticalSpacing(3);
        lineEdit_find = new QLineEdit(frame_find);
        lineEdit_find->setObjectName(QString::fromUtf8("lineEdit_find"));

        gridLayout_4->addWidget(lineEdit_find, 0, 0, 1, 1);

        pushButton_find = new QPushButton(frame_find);
        pushButton_find->setObjectName(QString::fromUtf8("pushButton_find"));

        gridLayout_4->addWidget(pushButton_find, 0, 1, 1, 1);


        verticalLayout_7->addWidget(frame_find);

        label_2 = new QLabel(dockWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_7->addWidget(label_2);

        frame_options = new QFrame(dockWidgetContents);
        frame_options->setObjectName(QString::fromUtf8("frame_options"));
        frame_options->setFrameShape(QFrame::NoFrame);
        frame_options->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_options);
        horizontalLayout_3->setSpacing(3);
        horizontalLayout_3->setContentsMargins(3, 3, 3, 3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        frame_radiobuttons = new QFrame(frame_options);
        frame_radiobuttons->setObjectName(QString::fromUtf8("frame_radiobuttons"));
        frame_radiobuttons->setFrameShape(QFrame::StyledPanel);
        frame_radiobuttons->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_radiobuttons);
        verticalLayout_6->setSpacing(3);
        verticalLayout_6->setContentsMargins(3, 3, 3, 3);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        radioButton_current = new QRadioButton(frame_radiobuttons);
        radioButton_current->setObjectName(QString::fromUtf8("radioButton_current"));
        radioButton_current->setChecked(true);

        verticalLayout_6->addWidget(radioButton_current);

        radioButton_project = new QRadioButton(frame_radiobuttons);
        radioButton_project->setObjectName(QString::fromUtf8("radioButton_project"));

        verticalLayout_6->addWidget(radioButton_project);


        horizontalLayout_3->addWidget(frame_radiobuttons);

        frame_wholeCase = new QFrame(frame_options);
        frame_wholeCase->setObjectName(QString::fromUtf8("frame_wholeCase"));
        frame_wholeCase->setFrameShape(QFrame::NoFrame);
        frame_wholeCase->setFrameShadow(QFrame::Raised);
        verticalLayout_8 = new QVBoxLayout(frame_wholeCase);
        verticalLayout_8->setSpacing(3);
        verticalLayout_8->setContentsMargins(3, 3, 3, 3);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        checkBox_wholeWords = new QCheckBox(frame_wholeCase);
        checkBox_wholeWords->setObjectName(QString::fromUtf8("checkBox_wholeWords"));

        verticalLayout_8->addWidget(checkBox_wholeWords);

        checkBox_caseSensitive = new QCheckBox(frame_wholeCase);
        checkBox_caseSensitive->setObjectName(QString::fromUtf8("checkBox_caseSensitive"));

        verticalLayout_8->addWidget(checkBox_caseSensitive);


        horizontalLayout_3->addWidget(frame_wholeCase);


        verticalLayout_7->addWidget(frame_options);

        listWidget_results = new QListWidget(dockWidgetContents);
        listWidget_results->setObjectName(QString::fromUtf8("listWidget_results"));
        listWidget_results->setTextElideMode(Qt::ElideMiddle);
        listWidget_results->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        listWidget_results->setResizeMode(QListView::Adjust);

        verticalLayout_7->addWidget(listWidget_results);

        dockWidget_finder->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_finder);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents_6 = new QWidget();
        dockWidgetContents_6->setObjectName(QString::fromUtf8("dockWidgetContents_6"));
        verticalLayout_9 = new QVBoxLayout(dockWidgetContents_6);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        listWidget_3 = new QListWidget(dockWidgetContents_6);
        listWidget_3->setObjectName(QString::fromUtf8("listWidget_3"));

        verticalLayout_9->addWidget(listWidget_3);

        listWidget_2 = new QListWidget(dockWidgetContents_6);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));

        verticalLayout_9->addWidget(listWidget_2);

        frame_2 = new QFrame(dockWidgetContents_6);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_2);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButton = new QPushButton(frame_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_5->addWidget(pushButton);

        label_startline = new QLabel(frame_2);
        label_startline->setObjectName(QString::fromUtf8("label_startline"));

        horizontalLayout_5->addWidget(label_startline);

        label_endline = new QLabel(frame_2);
        label_endline->setObjectName(QString::fromUtf8("label_endline"));

        horizontalLayout_5->addWidget(label_endline);


        verticalLayout_9->addWidget(frame_2);

        dockWidget->setWidget(dockWidgetContents_6);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

        menuBar->addAction(menuAnsicht->menuAction());
        menuBar->addAction(menuColorSaves->menuAction());
        menuAnsicht->addAction(actionPackage_and_FeatureView);
        menuAnsicht->addAction(actionFeature_Model);
        menuAnsicht->addAction(actionColorPicker);
        menuAnsicht->addAction(actionSave_Load);
        menuAnsicht->addAction(actionQuestions);
        menuColorSaves->addAction(actionColorSaves);

        retranslateUi(MainWindow);
        QObject::connect(actionColorPicker, SIGNAL(toggled(bool)), dockWidget_colors, SLOT(setVisible(bool)));
        QObject::connect(actionFeature_Model, SIGNAL(toggled(bool)), dockWidget_featureModel, SLOT(setVisible(bool)));
        QObject::connect(actionPackage_and_FeatureView, SIGNAL(toggled(bool)), dockWidget_left, SLOT(setVisible(bool)));
        QObject::connect(actionSave_Load, SIGNAL(toggled(bool)), dockWidget_colorAssignments, SLOT(setVisible(bool)));
        QObject::connect(dockWidget_colorAssignments, SIGNAL(visibilityChanged(bool)), actionSave_Load, SLOT(setChecked(bool)));
        QObject::connect(dockWidget_colors, SIGNAL(visibilityChanged(bool)), actionColorPicker, SLOT(setChecked(bool)));
        QObject::connect(dockWidget_featureModel, SIGNAL(visibilityChanged(bool)), actionFeature_Model, SLOT(setChecked(bool)));
        QObject::connect(actionSave_Load, SIGNAL(triggered()), MainWindow, SLOT(showMaximized()));

        tabWidget->setCurrentIndex(0);
        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "FeatureCommander", 0, QApplication::UnicodeUTF8));
        actionPackage_and_FeatureView->setText(QApplication::translate("MainWindow", "Package and FeatureView", 0, QApplication::UnicodeUTF8));
        actionFeature_Model->setText(QApplication::translate("MainWindow", "Feature Model", 0, QApplication::UnicodeUTF8));
        actionSave_Load->setText(QApplication::translate("MainWindow", "Save / Load", 0, QApplication::UnicodeUTF8));
        actionColorPicker->setText(QApplication::translate("MainWindow", "ColorPicker", 0, QApplication::UnicodeUTF8));
        actionQuestions->setText(QApplication::translate("MainWindow", "show Questions Dialog", 0, QApplication::UnicodeUTF8));
        actionColorSaves->setText(QApplication::translate("MainWindow", "ColorSaves", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Source Code Viewer", 0, QApplication::UnicodeUTF8));
        toolButton_light->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        horizontalSlider->setToolTip(QApplication::translate("MainWindow", "opacity of codebackground", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_dark->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_finder->setToolTip(QApplication::translate("MainWindow", "search", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_finder->setText(QApplication::translate("MainWindow", "search", 0, QApplication::UnicodeUTF8));
        toolButton_finder->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QString());
        menuAnsicht->setTitle(QApplication::translate("MainWindow", "Show", 0, QApplication::UnicodeUTF8));
        menuColorSaves->setTitle(QApplication::translate("MainWindow", "Load", 0, QApplication::UnicodeUTF8));
        dockWidget_left->setWindowTitle(QApplication::translate("MainWindow", "Explorer", 0, QApplication::UnicodeUTF8));
        radioButton_features->setText(QApplication::translate("MainWindow", "Features", 0, QApplication::UnicodeUTF8));
        radioButton_packages->setText(QApplication::translate("MainWindow", "File Structure", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_packageView->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Filestructure", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget_featureView->headerItem();
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "Features", 0, QApplication::UnicodeUTF8));
        dockWidget_featureModel->setWindowTitle(QApplication::translate("MainWindow", "Feature Model", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_featureSearch->setToolTip(QApplication::translate("MainWindow", "search Feature Model", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_featureSearch->setText(QString());
        dockWidget_colors->setWindowTitle(QApplication::translate("MainWindow", "Colors", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_resetColors->setToolTip(QApplication::translate("MainWindow", "reset all Colors", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_resetColors->setText(QApplication::translate("MainWindow", "reset", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_auto->setToolTip(QApplication::translate("MainWindow", "assign random colors to selected Features", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_auto->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_2->setToolTip(QApplication::translate("MainWindow", "add custom color to palette", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_2->setText(QApplication::translate("MainWindow", "add custom Color", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_removeAssignment->setToolTip(QApplication::translate("MainWindow", "remove colors from selected Features", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_removeAssignment->setText(QString());
        toolButton_removeAssignment->setShortcut(QApplication::translate("MainWindow", "Del", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        listWidget->setSortingEnabled(__sortingEnabled);

#ifndef QT_NO_TOOLTIP
        listWidget->setToolTip(QApplication::translate("MainWindow", "drag color onto feature", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        dockWidget_colorAssignments->setWindowTitle(QApplication::translate("MainWindow", "ColorAssignments", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_save->setToolTip(QApplication::translate("MainWindow", "save ColorAssignment", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_save->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        dockWidget_finder->setWindowTitle(QApplication::translate("MainWindow", "Finder", 0, QApplication::UnicodeUTF8));
        pushButton_find->setText(QApplication::translate("MainWindow", "Find", 0, QApplication::UnicodeUTF8));
        pushButton_find->setShortcut(QApplication::translate("MainWindow", "Return", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "search:", 0, QApplication::UnicodeUTF8));
        radioButton_current->setText(QApplication::translate("MainWindow", "current file", 0, QApplication::UnicodeUTF8));
        radioButton_project->setText(QApplication::translate("MainWindow", "all project files", 0, QApplication::UnicodeUTF8));
        checkBox_wholeWords->setText(QApplication::translate("MainWindow", "whole Words only", 0, QApplication::UnicodeUTF8));
        checkBox_caseSensitive->setText(QApplication::translate("MainWindow", "case sensitive", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "update", 0, QApplication::UnicodeUTF8));
        label_startline->setText(QApplication::translate("MainWindow", "startLine:", 0, QApplication::UnicodeUTF8));
        label_endline->setText(QApplication::translate("MainWindow", "endline:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
