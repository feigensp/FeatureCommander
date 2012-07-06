#ifndef QUESTIONDIALOG_H
#define QUESTIONDIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextDocument>
#include <QTextEdit>
#include <QTextStream>
#include <QDateTime>
#include <QTabWidget>
#include "codeview.h"
#include <QListWidget>


namespace Ui {
    class QuestionDialog;
}

class QuestionDialog : public QDialog {
    Q_OBJECT
public:
    QuestionDialog(QString p, QTabWidget *tab, QTreeWidget *package, QTreeWidget *feature,QWidget *f,QListWidget *l,QWidget *parent = 0);
    ~QuestionDialog();
    void closeEvent(QCloseEvent *e);
    bool allAnswered;
    bool codeEntered;
public slots:
    void nextStackedPage();
    void previousStackedPage();
    void firstPageNextEnabled();
    void writeAnswerFile();
    void writeToLog(QString logThis, QString fileName = "");
    void setCurrentFile(QString currentFileName);
    void setStartAndEndLine(int start, int end);


protected:
    void changeEvent(QEvent *e);

private:
    Ui::QuestionDialog *ui;
    QString path;
    QList <QTextEdit*> answerList;

    QString userName;
    QString code;
    QString currentFile;
    QString currentAction;
    int startLine;
    int endLine;
    QTabWidget *tabWidget;
    QTreeWidget *packageView;
    QTreeWidget *featureView;
    QWidget *finder;
    QListWidget *listWidget;
    QList<int> heights;
    QList <QTextEdit*> questionList;
    QString startTime;



};

#endif // QUESTIONDIALOG_H
