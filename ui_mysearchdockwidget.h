/********************************************************************************
** Form generated from reading UI file 'mysearchdockwidget.ui'
**
** Created: Tue 25. May 11:03:33 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYSEARCHDOCKWIDGET_H
#define UI_MYSEARCHDOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MySearchDockWidget
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_find;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_find;
    QPushButton *pushButton_find;
    QFrame *frame_radiobuttons;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton_current;
    QRadioButton *radioButton_open;
    QRadioButton *radioButton_project;
    QListWidget *listWidget_results;

    void setupUi(QDockWidget *MySearchDockWidget)
    {
        if (MySearchDockWidget->objectName().isEmpty())
            MySearchDockWidget->setObjectName(QString::fromUtf8("MySearchDockWidget"));
        MySearchDockWidget->resize(400, 300);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_find = new QFrame(dockWidgetContents);
        frame_find->setObjectName(QString::fromUtf8("frame_find"));
        frame_find->setFrameShape(QFrame::StyledPanel);
        frame_find->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_find);
        gridLayout->setContentsMargins(3, 3, 3, 3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setVerticalSpacing(3);
        lineEdit_find = new QLineEdit(frame_find);
        lineEdit_find->setObjectName(QString::fromUtf8("lineEdit_find"));

        gridLayout->addWidget(lineEdit_find, 0, 0, 1, 1);

        pushButton_find = new QPushButton(frame_find);
        pushButton_find->setObjectName(QString::fromUtf8("pushButton_find"));

        gridLayout->addWidget(pushButton_find, 0, 1, 1, 1);


        verticalLayout_3->addWidget(frame_find);

        frame_radiobuttons = new QFrame(dockWidgetContents);
        frame_radiobuttons->setObjectName(QString::fromUtf8("frame_radiobuttons"));
        frame_radiobuttons->setFrameShape(QFrame::StyledPanel);
        frame_radiobuttons->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_radiobuttons);
        verticalLayout->setSpacing(3);
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radioButton_current = new QRadioButton(frame_radiobuttons);
        radioButton_current->setObjectName(QString::fromUtf8("radioButton_current"));
        radioButton_current->setChecked(true);

        verticalLayout->addWidget(radioButton_current);

        radioButton_open = new QRadioButton(frame_radiobuttons);
        radioButton_open->setObjectName(QString::fromUtf8("radioButton_open"));

        verticalLayout->addWidget(radioButton_open);

        radioButton_project = new QRadioButton(frame_radiobuttons);
        radioButton_project->setObjectName(QString::fromUtf8("radioButton_project"));

        verticalLayout->addWidget(radioButton_project);


        verticalLayout_3->addWidget(frame_radiobuttons);

        listWidget_results = new QListWidget(dockWidgetContents);
        listWidget_results->setObjectName(QString::fromUtf8("listWidget_results"));
        listWidget_results->setAutoFillBackground(true);
        listWidget_results->setTextElideMode(Qt::ElideMiddle);
        listWidget_results->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        listWidget_results->setResizeMode(QListView::Adjust);

        verticalLayout_3->addWidget(listWidget_results);

        MySearchDockWidget->setWidget(dockWidgetContents);

        retranslateUi(MySearchDockWidget);

        QMetaObject::connectSlotsByName(MySearchDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *MySearchDockWidget)
    {
        MySearchDockWidget->setWindowTitle(QApplication::translate("MySearchDockWidget", "DockWidget", 0, QApplication::UnicodeUTF8));
        pushButton_find->setText(QApplication::translate("MySearchDockWidget", "Find", 0, QApplication::UnicodeUTF8));
        radioButton_current->setText(QApplication::translate("MySearchDockWidget", "search current file", 0, QApplication::UnicodeUTF8));
        radioButton_open->setText(QApplication::translate("MySearchDockWidget", "search all open files", 0, QApplication::UnicodeUTF8));
        radioButton_project->setText(QApplication::translate("MySearchDockWidget", "search all project files", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MySearchDockWidget: public Ui_MySearchDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYSEARCHDOCKWIDGET_H
