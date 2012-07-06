#include "questiondialog.h"
#include "ui_questiondialog.h"
#include <stdlib.h>


QuestionDialog::QuestionDialog( QString p, QTabWidget *tab, QTreeWidget *package, QTreeWidget *feature,QWidget *f,QListWidget *l, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionDialog)
{

    path = p;
    answerList = QList <QTextEdit*>();
    tabWidget = tab;
    packageView = package;
    featureView = feature;
    finder = f;
    listWidget = l;
    allAnswered = false;
    codeEntered = false;

    //Variablen für LogFile
    currentAction = "";
    currentFile = "";
    startLine = -1;
    endLine = -1;

    ui->setupUi(this);

    heights = QList<int>();
    heights.push_back(ui->lineEdit_account->height()+ui->pushButton_next->height());

    questionList = QList<QTextEdit*>();

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint);

    ui->pushButton_back->setEnabled(false);
    ui->pushButton_next->setEnabled(false);
    connect(ui->pushButton_next,SIGNAL(clicked()),this,SLOT(nextStackedPage()));
    connect(ui->pushButton_back,SIGNAL(clicked()),this,SLOT(previousStackedPage()));
    connect(ui->lineEdit_account,SIGNAL(textEdited(QString)),this,SLOT(firstPageNextEnabled()));
    ui->pushButton_back->hide();

    char *user = getenv("USERNAME");
    userName = "";
    userName += user;
    code = ui->lineEdit_account->text()+"_"+userName;

    QFile file (path + "/questions.txt");
    if (file.exists(path + "/questions.txt")){
        file.open(QIODevice::ReadOnly);
        QString data = static_cast <QString>(file.readAll());
        file.close();
        //data.remove(QRegExp("[\\r\\n]"));
        QString test = "";
        QStringList lines = data.split(';');

        for (int i = 0; i < lines.size(); i++){
            QStringList subquestions = lines.at(i).split('$');
            QWidget *page = new QWidget();
            QVBoxLayout *layout = new QVBoxLayout(page);
            ui->stackedWidget->addWidget(page);
            int h = 0;

            for (int j = 0; j < subquestions.size(); j++){
                QString subquestion = static_cast<QString>(subquestions.at(j));
                int lengthOfAnswer = 0;
                QString question = static_cast<QString>(subquestion.split('|').at(0));
                if (subquestion.split('|').size() > 1)
                    lengthOfAnswer = static_cast<QString>(subquestion.split('|').at(1)).toInt();
//                test += " " + question;
//                ui->textEdit_explanation->setText(test);
                QTextEdit *editQuestion = new QTextEdit(page);
                QTextDocument *doc = new QTextDocument();
                doc->setHtml(question);
                editQuestion->setDocument(doc);
                layout->addWidget(editQuestion);

                questionList.push_back(editQuestion);
                editQuestion->setFixedHeight(doc->size().height());
                editQuestion->setFrameShape(QFrame::NoFrame);
                editQuestion->setTextInteractionFlags(Qt::NoTextInteraction);
                QPalette palette = editQuestion->palette();
                palette.setColor(QPalette::Base,palette.background().color());
                editQuestion->setPalette(palette);
                h+= editQuestion->height()+5;

                if (lengthOfAnswer > 0){
                    QTextEdit *editAnswer = new QTextEdit(page);
                    answerList.push_back(editAnswer);
                    editAnswer->setFixedHeight((lengthOfAnswer * editQuestion->fontMetrics().lineSpacing()) + 10);
                    layout->addWidget(editAnswer);
                    h+= (lengthOfAnswer * editQuestion->fontMetrics().lineSpacing()) + 10;
                }
                layout->setAlignment(Qt::AlignTop);
            }

            h+= ui->pushButton_next->height();
            int top = 0;
            int bottom = 0;
            layout->getContentsMargins(0,&top,0,&bottom);
            heights.push_back(h + top + bottom);

        }

        ui->stackedWidget->removeWidget(ui->stackedWidget->widget(ui->stackedWidget->count()-1));
        setFixedHeight(ui->stackedWidget->currentWidget()->sizeHint().height()+100);
    }
    ui->lineEdit->hide();
}

QuestionDialog::~QuestionDialog()
{
    delete ui;
}

void QuestionDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void QuestionDialog::writeAnswerFile(){
    QFile file(path + "/" + code + "_answers.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream textStream(&file);
    QString answers = "";
    for (int i = 0; i < answerList.size(); i++){
        answers += answerList.at(i)->toPlainText() + "$";
    }
    textStream << answers << endl;
    file.close();
}

void QuestionDialog::firstPageNextEnabled(){
    if (ui->stackedWidget->currentIndex() == 0 && ui->lineEdit_account->text().length() == 0)
        ui->pushButton_next->setEnabled(false);
    if (ui->stackedWidget->currentIndex() == 0 && ui->lineEdit_account->text().length() > 0)
        ui->pushButton_next->setEnabled(true);
}

void QuestionDialog::nextStackedPage(){
    //Öffnen bei letzter bearbeiteter Frage falls Programmabsturz
    bool doLog = true;
    if(ui->stackedWidget->currentIndex() == 0){
        code = ui->lineEdit_account->text()+"_"+ userName;
        QFile file(path + "/" + code + "_log.txt");
        if (file.exists()){
            file.open(QIODevice::ReadOnly);
            QString text = static_cast<QString>(file.readAll());

            if (!text.isEmpty()){
                QFile answerFile(path + "/" + code + "_answers.txt");
                if (answerFile.exists()){
                    answerFile.open(QIODevice::ReadOnly);
                    QString answerText = static_cast<QString>(answerFile.readAll());
                    QStringList answers = answerText.split('$');
                    answerFile.close();
                    for (int i = 0; i < answers.size()-1; i++){
                        answerList.at(i)->setText(static_cast<QString>(answers.at(i)));
                    }

                }
            }

            QStringList lines = text.split("\r\n");
            QString lastLine = static_cast<QString>(lines.at(lines.size()-2));
            QString action = static_cast<QString>(lastLine.split("$").at(2));
            int lastLoggedIndex = 0;
            //ui->lineEdit->setText(static_cast<QString>(lastLine.split("$").first()).remove("task"));
            if (!lastLine.startsWith("code")){
               lastLoggedIndex = static_cast<QString>(lastLine.split("$").first()).remove("task").toInt();
           }
            int currentTask = 0;
            if (action.contains("taskCompleted") && lastLoggedIndex < ui->stackedWidget->count()-1){
                currentTask = lastLoggedIndex + 1;
            }
            if(!action.contains("taskCompleted") && lastLoggedIndex < ui->stackedWidget->count()){
                currentTask = lastLoggedIndex;
            }
            if (currentTask > 1 && currentTask < ui->stackedWidget->count()-1){
                ui->stackedWidget->setCurrentIndex(currentTask);
                doLog = false;
            }
            codeEntered = true;
            hide();
            setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint);
            show();
        }
    }
    if (ui->stackedWidget->currentIndex() != 1 && doLog)
        writeToLog("taskCompleted");
    if (ui->stackedWidget->currentIndex()+1 < ui->stackedWidget->count())
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    if (ui->stackedWidget->currentIndex() == 0 || ui->stackedWidget->currentIndex() == -1)
        ui->pushButton_back->setEnabled(false);
    else
        ui->pushButton_back->setEnabled(true);
    if (ui->pushButton_next->text() == "Fertig!"){
        allAnswered = true;
        close();
    }

    if (ui->stackedWidget->currentIndex() == ui->stackedWidget->count()-1)
        ui->pushButton_next->setText("Fertig!");
    else
        ui->pushButton_next->setText("Weiter");
    writeAnswerFile();

//    if (ui->pushButton_next->text() != "Fertig!"){
//        hide();
//        setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint);
//        show();
//    }
    for (int i = 0; i<questionList.size();i++){
        questionList.at(i)->setFixedHeight(questionList.at(i)->document()->size().height());
    }

    setFixedHeight(ui->stackedWidget->currentWidget()->sizeHint().height()+100);

}

void QuestionDialog::previousStackedPage(){
    if (ui->stackedWidget->currentIndex() > 0)
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
    if (ui->stackedWidget->currentIndex() == 0 || ui->stackedWidget->currentIndex() == -1)
        ui->pushButton_back->setEnabled(false);
    else
        ui->pushButton_back->setEnabled(true);
    if (ui->stackedWidget->currentIndex() == ui->stackedWidget->count()-1)
        ui->pushButton_next->setText("Fertig!");
    else
        ui->pushButton_next->setText("Weiter");
    writeAnswerFile();
}

void QuestionDialog::writeToLog(QString logThis, QString fileName){

    if(!allAnswered){
        currentAction = logThis;

        if (tabWidget->currentIndex()!=-1){
            CodeView *view = static_cast<CodeView*>(tabWidget->widget(tabWidget->currentIndex()));
            if (fileName == "")
                setCurrentFile(view->file->fileName().remove(path));
            else
                setCurrentFile(fileName);

            QPolygonF poly = view->lineNumbersView->mapToScene(view->lineNumbersView->rect());
            QList  <QGraphicsItem*> list = view->lineNumbersScene->items(poly);
            QString start = "";
            QString end = "";
            if (list.size()>0){
                QGraphicsTextItem *item = static_cast<QGraphicsTextItem*>(list.at(list.size()-1));
                start = item->document()->toPlainText();
                end = static_cast<QGraphicsTextItem*>(list.at(0))->document()->toPlainText();
                setStartAndEndLine(start.toInt(),end.toInt());
            }
        }


        //Aufgabe
        QString task = "";
        task = "task" + task.setNum(ui->stackedWidget->currentIndex()-1);
        if (task == "task-1"){
            task = "code";
            if (currentAction == "taskCompleted");
                currentAction = "code";
        }



        //aktuelle Zeit ermitteln
        QDateTime *time = new QDateTime();
        QString currentTimeStamp = "";
        currentTimeStamp = currentTimeStamp.setNum(time->currentDateTime().toTime_t());

        //StartZeit ermitteln
        if (startTime == "")
            startTime = currentTimeStamp;

        //Dauer ermitteln
        QString duration = "";

        duration = duration.setNum(currentTimeStamp.toInt() - startTime.toInt());

        //StartZeile
        QString line_start = "";
        if (startLine > -1)
            line_start = line_start.setNum(startLine);

        //EndZeile
        QString line_end = "";
        if (endLine > -1)
            line_end = line_end.setNum(endLine);


        QFile file(path + "/" + code + "_log.txt");
        file.open(QIODevice::Append);
        QTextStream textStream(&file);

        textStream << task + "$" + currentFile + "$" + currentAction + "$(" + line_start + "$" + line_end + ")$"
                + startTime + "$" + currentTimeStamp + "$" + duration + "\r\n" << endl;
        file.close();
        startTime = currentTimeStamp;
    }
    packageView->setCursor(Qt::ArrowCursor);
    featureView->setCursor(Qt::ArrowCursor);
    finder->setCursor(Qt::ArrowCursor);
    listWidget->setCursor(Qt::ArrowCursor);


}

void QuestionDialog::setCurrentFile(QString currentFileName){
    currentFile = currentFileName;
}

void QuestionDialog::setStartAndEndLine(int start, int end){
    startLine = start;
    endLine = end;
}

void QuestionDialog::closeEvent(QCloseEvent *e){
    if (allAnswered) {
        QDialog::closeEvent(e);
    } else {
        e->ignore();
    }
}


