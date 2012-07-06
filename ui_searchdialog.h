/********************************************************************************
** Form generated from reading UI file 'searchdialog.ui'
**
** Created: Wed 19. May 18:01:25 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHDIALOG_H
#define UI_SEARCHDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SearchDialog
{
public:
    QFormLayout *formLayout;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit_find;
    QDialogButtonBox *buttonBox;
    QListWidget *listWidget_results;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton_current;
    QRadioButton *radioButton_open;
    QRadioButton *radioButton_project;

    void setupUi(QDialog *SearchDialog)
    {
        if (SearchDialog->objectName().isEmpty())
            SearchDialog->setObjectName(QString::fromUtf8("SearchDialog"));
        SearchDialog->resize(356, 249);
        formLayout = new QFormLayout(SearchDialog);
        formLayout->setContentsMargins(3, 3, 3, 3);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setHorizontalSpacing(3);
        formLayout->setVerticalSpacing(3);
        frame = new QFrame(SearchDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setContentsMargins(3, 3, 3, 3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setVerticalSpacing(3);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_find = new QLineEdit(frame);
        lineEdit_find->setObjectName(QString::fromUtf8("lineEdit_find"));

        gridLayout->addWidget(lineEdit_find, 0, 1, 1, 1);


        formLayout->setWidget(0, QFormLayout::LabelRole, frame);

        buttonBox = new QDialogButtonBox(SearchDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(0, QFormLayout::FieldRole, buttonBox);

        listWidget_results = new QListWidget(SearchDialog);
        listWidget_results->setObjectName(QString::fromUtf8("listWidget_results"));

        formLayout->setWidget(2, QFormLayout::LabelRole, listWidget_results);

        frame_2 = new QFrame(SearchDialog);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setSpacing(3);
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radioButton_current = new QRadioButton(frame_2);
        radioButton_current->setObjectName(QString::fromUtf8("radioButton_current"));
        radioButton_current->setChecked(true);

        verticalLayout->addWidget(radioButton_current);

        radioButton_open = new QRadioButton(frame_2);
        radioButton_open->setObjectName(QString::fromUtf8("radioButton_open"));

        verticalLayout->addWidget(radioButton_open);

        radioButton_project = new QRadioButton(frame_2);
        radioButton_project->setObjectName(QString::fromUtf8("radioButton_project"));

        verticalLayout->addWidget(radioButton_project);


        formLayout->setWidget(1, QFormLayout::LabelRole, frame_2);


        retranslateUi(SearchDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SearchDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SearchDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SearchDialog);
    } // setupUi

    void retranslateUi(QDialog *SearchDialog)
    {
        SearchDialog->setWindowTitle(QApplication::translate("SearchDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SearchDialog", "Find", 0, QApplication::UnicodeUTF8));
        radioButton_current->setText(QApplication::translate("SearchDialog", "search current file", 0, QApplication::UnicodeUTF8));
        radioButton_open->setText(QApplication::translate("SearchDialog", "search all open files", 0, QApplication::UnicodeUTF8));
        radioButton_project->setText(QApplication::translate("SearchDialog", "search all project files", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SearchDialog: public Ui_SearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHDIALOG_H
