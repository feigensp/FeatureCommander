/********************************************************************************
** Form generated from reading UI file 'finderdialog.ui'
**
** Created: Tue 25. May 23:49:41 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDERDIALOG_H
#define UI_FINDERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FinderDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame_dialogContents;
    QVBoxLayout *verticalLayout_2;
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
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FinderDialog)
    {
        if (FinderDialog->objectName().isEmpty())
            FinderDialog->setObjectName(QString::fromUtf8("FinderDialog"));
        FinderDialog->setWindowModality(Qt::ApplicationModal);
        FinderDialog->resize(400, 300);
        FinderDialog->setModal(true);
        horizontalLayout = new QHBoxLayout(FinderDialog);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame_dialogContents = new QFrame(FinderDialog);
        frame_dialogContents->setObjectName(QString::fromUtf8("frame_dialogContents"));
        frame_dialogContents->setFrameShape(QFrame::StyledPanel);
        frame_dialogContents->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_dialogContents);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame_find = new QFrame(frame_dialogContents);
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


        verticalLayout_2->addWidget(frame_find);

        frame_radiobuttons = new QFrame(frame_dialogContents);
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


        verticalLayout_2->addWidget(frame_radiobuttons);

        listWidget_results = new QListWidget(frame_dialogContents);
        listWidget_results->setObjectName(QString::fromUtf8("listWidget_results"));
        listWidget_results->setTextElideMode(Qt::ElideMiddle);
        listWidget_results->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        listWidget_results->setResizeMode(QListView::Adjust);

        verticalLayout_2->addWidget(listWidget_results);


        horizontalLayout->addWidget(frame_dialogContents);

        buttonBox = new QDialogButtonBox(FinderDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        retranslateUi(FinderDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FinderDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FinderDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FinderDialog);
    } // setupUi

    void retranslateUi(QDialog *FinderDialog)
    {
        FinderDialog->setWindowTitle(QApplication::translate("FinderDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton_find->setText(QApplication::translate("FinderDialog", "Find", 0, QApplication::UnicodeUTF8));
        radioButton_current->setText(QApplication::translate("FinderDialog", "search current file", 0, QApplication::UnicodeUTF8));
        radioButton_open->setText(QApplication::translate("FinderDialog", "search all open files", 0, QApplication::UnicodeUTF8));
        radioButton_project->setText(QApplication::translate("FinderDialog", "search all project files", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FinderDialog: public Ui_FinderDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDERDIALOG_H
