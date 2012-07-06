#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "featuretreewidget.h"
#include <QtGui>
#include <vector>
#include "feature.h"
#include "smvtreewidget.h"
#include "xmldomparser.h"
#include <QDir>
#include <QString>
#include <QFileDialog>
#include <iostream>


QString MainWindow::path = QString();
MainWindow* MainWindow::myMainWindow = 0 ;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    myMainWindow = this;
    path = QFileDialog::getExistingDirectory(this,QString("Open project folder"));

    ui->setupUi(this);

    ui->treeWidget_featureView->isFeatureView = true;

    //CheckboxBreite fürs Highlighting des FeatureTreeWidgets
    QCheckBox *checkbox = new QCheckBox(ui->tabWidget->widget(0));
    checkbox->show();
    checkBoxWidth = checkbox->iconSize().width();

    //Laden des Models
    QFile *file = new QFile(path + "/model.m");
    t = new FeatureTreeWidget(this,file, ui->listWidget, 0, this);
    ui->frame_featureModel->layout()->addWidget(t);
    t->setContextMenuPolicy(Qt::CustomContextMenu);

    t->createFeatureList();
    vector <Feature> *featureList = t->getFeatureList();

    colorManager = new ColorManager(featureList,featureList->size());

    t->setColorManager(colorManager);
    //ui->plainTextEdit->setColorManager(colorManager);
    ui->treeWidget_packageView->setColorManager(colorManager);
    ui->treeWidget_featureView->setColorManager(colorManager);
    ui->treeWidget_packageView->setFeatureTreeWidget(t);
    ui->treeWidget_featureView->setFeatureTreeWidget(t);

    //Mouse Tracking einschalten, damit Hover möglich ist
//    ui->treeWidget_packageView->setMouseTracking(true);
//    ui->treeWidget_featureView->setMouseTracking(true);

    parser = new XmlDomParser(ui->treeWidget_packageView, ui->treeWidget_featureView, featureList);
    QString xmlFileName = path + "/annotations.xml";

    parser->readFile(xmlFileName);
    parser->countTotalCharsAndAssignToSTNodes(path);
    parser->fillFeatureViewTreeWidget(this);

    initializeListWidget();

    dialog = new QColorDialog(this);


    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    
    saveLoadShown = false;
    colorPickerShown = false;
    featureModelshown = false;

    //Finder
    ui->dockWidget_finder->hide();
    ui->dockWidget_finder->setFloating(true);
    lastSearch = "";
    finds = new QList <QGraphicsRectItem*>();
    fileNodes = new QList <QTreeWidgetItem*>();
    findsIndex = 0;
    lastCodeView = 0;
    connect(ui->pushButton_find,SIGNAL(pressed()),this,SLOT(search()));
    connect(ui->listWidget_results,SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(openFileFromListWidget(QListWidgetItem*)));
    connect(ui->radioButton_project, SIGNAL(toggled(bool)),this,SLOT(resetLastSearch()));
    connect(ui->checkBox_caseSensitive, SIGNAL(toggled(bool)),this,SLOT(resetLastSearch()));
    connect(ui->checkBox_wholeWords, SIGNAL(toggled(bool)),this,SLOT(resetLastSearch()));


    //SIGNALS and SLOTS
    //connect(ui->listWidget,SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(highlightColor(QListWidgetItem*)));
    connect(ui->radioButton_features,SIGNAL(toggled(bool)),this,SLOT(explorerToggled(bool)));
    connect(ui->toolButton_auto,SIGNAL(clicked()),t,SLOT(assignAutomatically()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(showColorArray()));
    connect(ui->toolButton_2,SIGNAL(clicked()),this,SLOT(customColorDialog()));
    connect(this->dialog,SIGNAL(finished(int)),this,SLOT(closeCustomColorDialog()));
    connect(ui->listWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showListWidgetContextMenu(QPoint)));
    connect(t,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showFeatureModelContextMenu(QPoint)));
    connect(ui->pushButton_resetColors,SIGNAL(clicked()),this,SLOT(resetListWidget()));
    connect(ui->toolButton_save,SIGNAL(clicked()),this,SLOT(saveColors()));
    connect(ui->treeWidget_packageView,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(openFile(QTreeWidgetItem*)));
    connect(ui->treeWidget_featureView,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(openFile(QTreeWidgetItem*)));
    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));
    connect(ui->treeWidget_packageView,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(showFeatureFractureList(QTreeWidgetItem*)));
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(updateTabColors(int)));
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(setFeatureOpacity(int)));
    connect(ui->toolButton_finder,SIGNAL(clicked()),ui->dockWidget_finder,SLOT(show()));
    connect(ui->toolButton_finder,SIGNAL(clicked()),ui->dockWidgetContents,SLOT(setFocus()));
    connect(ui->toolButton_finder,SIGNAL(clicked()),ui->frame_find,SLOT(setFocus()));
    connect(ui->toolButton_finder,SIGNAL(clicked()),ui->lineEdit_find,SLOT(setFocus()));
    connect(ui->toolButton_removeAssignment,SIGNAL(clicked()),t,SLOT(removeColorAssignmentFromSelection()));
    connect(ui->horizontalSlider,SIGNAL(sliderReleased()),this,SLOT(writeToLogSaturationChanged()));
    connect(ui->toolButton_featureSearch,SIGNAL(clicked()),this,SLOT(searchInFeatureModel()));
    connect(ui->dockWidget_finder,SIGNAL(visibilityChanged(bool)),this,SLOT(removeFinds()));
    connect(ui->actionColorSaves,SIGNAL(triggered()),this,SLOT(loadColors()));

    //ui->lineEdit_find->setParent(ui->dockWidget_finder);
    lastSelectedListWidgetItem = new QListWidgetItem();
    lastSelectedTreeWidgetItem = new QTreeWidgetItem();

    ui->treeWidget_packageView->expandToDepth(1);
    ui->treeWidget_featureView->expandAll();
    for (int i = 0; i < ui->treeWidget_featureView->topLevelItemCount(); i++){
        ui->treeWidget_featureView->collapseItem(ui->treeWidget_featureView->topLevelItem(i));
    }
    ui->treeWidget_featureView->setIndentation(12);
    ui->treeWidget_packageView->setIndentation(12);

    ui->pushButton_resetColors->hide();
    ui->dockWidget->hide();
    questionDialog = new QuestionDialog(path, ui->tabWidget,ui->treeWidget_packageView, ui->treeWidget_featureView,ui->dockWidget_finder,ui->listWidget_results);
//    questionDialog->show();
//    connect(ui->actionQuestions,SIGNAL(triggered()),questionDialog,SLOT(show()));

    lastFeatureModelItem = t->topLevelItem(0);
    lastFeatureSearch = "";
    showMaximized();
    //setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

//    time = 0;
//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(showTimeMessage()));
//    timer->start(900000);

//    QDir folder (*path * "/savedColorAssignments");
//    folder.

//    ui->listWidget_2->hide();
//    ui->pushButton->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete t;
    delete colorManager;
    delete parser;
}

void MainWindow::closeEvent(QCloseEvent *event){
    questionDialog->allAnswered = true;
    questionDialog->close();
    QMainWindow::closeEvent(event);
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Return){
        if (!ui->dockWidget_finder->hasFocus())
            searchInFeatureModel();
    }
    QMainWindow::keyPressEvent(event);
}

//void MainWindow::showTimeMessage(){
//    if (!questionDialog->codeEntered){
//        questionDialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint);
//        questionDialog->show();
//    }
//    QMessageBox *msg = new QMessageBox(questionDialog);
//    time += 15;
//    QString message = "";
//    message = message.setNum(time);
//    message+= " Minuten sind um!";
//    msg->information(this,"",message);
//    if (!questionDialog->codeEntered){
//        questionDialog->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint);
//        questionDialog->show();
//    }
//}

void MainWindow::setFeatureOpacity(int opacity){
    if (ui->tabWidget->currentIndex()>-1){
        CodeView *view = static_cast<CodeView*>(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
        view->setFeatureOpacity(opacity);
    }
}

void MainWindow::writeToLogSaturationChanged(){
    if (ui->tabWidget->currentIndex()>-1){
        CodeView *view = static_cast<CodeView*>(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
        QString fileName = view->file->fileName().remove(path);
        QString sat = "";
        sat = sat.setNum(ui->horizontalSlider->value());
        questionDialog->writeToLog("saturationChanged(" + sat + ")",fileName);
    }
}

void MainWindow::showFeatureFractureList(QTreeWidgetItem* item){
//    STNode *node = static_cast<STNode*> (item);
//    ui->listWidget_3->clear();
//    for (int i = 0; i< node->getFeatureFractureList()->size();i++){
//        QString offset = "";
//        offset= offset.setNum(node->getFeatureFractureList()->at(i).getOffset());
//        QString length = "";
//        length= length.setNum(node->getFeatureFractureList()->at(i).getLength());
//        ui->listWidget_3->addItem(offset + " " + length);
//    }
}

void MainWindow::closeTab(int tab){
    QString fileName = "";
    if (ui->tabWidget->currentIndex()!=-1){
        CodeView *view = static_cast<CodeView*>(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
        fileName = view->file->fileName().remove(path);

    }
    questionDialog->writeToLog("fileClosed",fileName);
    ui->tabWidget->removeTab(tab);
}

void MainWindow::openFile(QTreeWidgetItem *item){
    STNode *stItem = static_cast<STNode*>(item);
    if (stItem->getNodeType()==STNode::FILE){
        bool exists = false;
        for (int i = 0; i < ui->tabWidget->count();i++){
            if (ui->tabWidget->tabText(i) == stItem->text(0)){
                CodeView *view = static_cast<CodeView*>(ui->tabWidget->widget(i));
                if (view->file->fileName() == stItem->getPath()){
                    exists = true;
                    ui->tabWidget->setCurrentIndex(i);
                    break;
                }
            }
        }
        if (!exists){
            ui->treeWidget_packageView->setCursor(Qt::WaitCursor);
            ui->treeWidget_featureView->setCursor(Qt::WaitCursor);
            QFile *file = new QFile(stItem->getPath());
            CodeView *codeView = new CodeView(t,stItem,this,file,ui->horizontalSlider->value());
            //Tab einfügen. WICHTIG: alle Werte, die die Größe, des TextEdits betreffen, erst danach abfragen!
            //                       (weil das Widget erst dann gezeichnet ist)
            int i = ui->tabWidget->addTab(codeView,item->text(0));
            ui->tabWidget->setCurrentIndex(i);

            //QGraphicsItems zeichnen (darf erst nach dem Zeichnen des CodeViews gemacht werden, weil sonst manche Größen nicht stimmen)
            codeView->addFractureRectangles();
            codeView->fillLineNumberWidget();
            codeView->drawBackgroundFractures();
            QTimer *timer = new QTimer(this);
            timer->setSingleShot(true);
            connect(timer, SIGNAL(timeout()), this, SLOT(writeToLogFileOpened()));

            timer->start(10);
        }
    }

}

void MainWindow::writeToLogFileOpened(){
    QString fileName = "";
    if (ui->tabWidget->currentIndex()!=-1){
        CodeView *view = static_cast<CodeView*>(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
        fileName = view->file->fileName().remove(path);
        view->justCreated = false;
    }
    questionDialog->writeToLog("fileOpened",fileName);

}

void MainWindow::saveColors(){
    SaveColorAssignment save(this,this,&ui->toolButton_save->icon(),ui->frame_loadButtons,colorManager->colorArray,colorManager->FCPList,colorManager,&path);

}

void MainWindow::loadColors(){

    QString fileName = QFileDialog::getOpenFileName(this,"Open saved Color Assignment",path + "/savedColorAssignments");

    if (!fileName.isNull()){

        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            std::cerr << "Error: Cannot read file "
                    << ": " << qPrintable(file.errorString())
                    << std::endl;
        }

        QString errorStr;
        int errorLine;
        int errorColumn;

        QDomDocument doc;
        if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            std::cerr << "Error: Parse error at line " << errorLine << ", "
                    << "column " << errorColumn << ": "
                    << qPrintable(errorStr) << std::endl;
            ui->listWidget_3->addItem(fileName);
        }


        QDomElement root = doc.documentElement();
        if (root.tagName() != "savedColorAssignment") {
            std::cerr << "Error: File is not a savedColorAssignment file" << std::endl;
        }

        QDomNode fcpList = (QDomNode)root.firstChild();
        QDomNode colorArray = (QDomNode)fcpList.nextSibling();

        colorManager->colorArray->clear();
        QDomElement colorArrayChild = colorArray.firstChild().toElement();
        while(!colorArrayChild.isNull()){
            QColor color = QColor(colorArrayChild.attribute("r").toInt(),colorArrayChild.attribute("g").toInt(),colorArrayChild.attribute("b").toInt());
            colorManager->colorArray->push_back(new Color(color));
            colorArrayChild = colorArrayChild.nextSiblingElement("color");
        }

        for (int i = 0; i < colorManager->featureList->size();i++){
            QDomElement fcpListChild = fcpList.childNodes().at(i).toElement();
            QColor qcolor = QColor(fcpListChild.attribute("r").toInt(),fcpListChild.attribute("g").toInt(),fcpListChild.attribute("b").toInt());
            Color *color = 0;
            for (int j = 0; j < colorManager->colorArray->size(); j++){
                if (qcolor == colorManager->colorArray->at(j)->getColor()){
                    color = colorManager->colorArray->at(j);
                }
            }
            if (color !=0)
                colorManager->setColorForFeature(&colorManager->featureList->at(i),color);
            else
                colorManager->deleteColorForFeature(&colorManager->featureList->at(i));
        }
        this->updateAllColors();
        questionDialog->writeToLog("loadColorAssignment<" + fileName +">");
    }else{
        QMessageBox *msg = new QMessageBox(this);
        msg->information(this,"Error","File could not be loaded!");
    }
}

void MainWindow::updateAllColors(){
    for (int i = 0; i < colorManager->featureList->size();i++){
        this->parser->updateSTNodeTextures(&colorManager->featureList->at(i));
    }
    QTreeWidgetItemIterator it(t,QTreeWidgetItemIterator::NoChildren);
    int featureIndex = 0;
    while(*it){
        MyTreeWidgetItem *item = static_cast<MyTreeWidgetItem*>(*it);
        Color *color = colorManager->getColorForFeature(&colorManager->featureList->at(featureIndex));
        if (color->color == QColor(220, 220, 220, 255) || color->color == QColor(180, 180, 180, 255)){
            item->setBackgroundInvalid();
            if (t->itemWidget(item,1)!=0)
                t->itemWidget(item,1)->hide();
        }
        else{
            item->setBGColor(color);
            if (t->itemWidget(item,1)!=0)
                t->itemWidget(item,1)->show();
            else{
                QToolButton *deleteButton = new QToolButton(this);
                deleteButton->setFont(QFont(QString("MS Shell Dlg 2"),9,10,false));
                //deleteButton->setFixedSize(15,18);
                deleteButton->setFixedWidth(16);
                QIcon icon = QIcon();
                icon.addPixmap(QPixmap(QString(":/images/cross.png")),QIcon::Normal,QIcon::On);
                deleteButton->setIcon(icon);
                deleteButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
                t->setItemWidget(item,1,deleteButton);
                connect(deleteButton,SIGNAL(clicked()),t,SLOT(removeColorAssignment()));
            }

        }
        featureIndex++;
        ++it;
    }
    ui->treeWidget_packageView->resize(ui->treeWidget_packageView->size().width());
    ui->treeWidget_featureView->resize(ui->treeWidget_featureView->size().width());
    drawSaveButtonIcon();
    if (ui->tabWidget->currentIndex()!=-1){
        CodeView *view = static_cast<CodeView*>(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
        view->updateAllColors();
    }
    t->redrawListWidget();
}

void MainWindow::customColorDialog(){

    dialog->setOption(QColorDialog::DontUseNativeDialog,true);
    for (int i = 0;i < dialog->customCount();i++){
        dialog->setCustomColor(i,qRgb(255,255,255));
    }

    dialog->show();
//    //this->colorManager->colorArray->push_back();
}

void MainWindow::closeCustomColorDialog(){
    for (int i = 0;i < dialog->customCount();i++){
        if (dialog->customColor(i)!=qRgb(255,255,255)){
            QColor qcolor = dialog->customColor(i);
            Color *newColor = new Color(qcolor);
            newColor->setCustom(true);
            colorManager->colorArray->push_back(newColor);
        }
    }

    t->redrawListWidget();
}

//nur zum Testen
void MainWindow::showColorArray(){
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();

    for (int i = 0; i<colorManager->colorArray->size();i++){
        QListWidgetItem *item = new QListWidgetItem(QString());
        Color *color = colorManager->colorArray->at(i);
        item->setBackgroundColor(color->color);
        if (color->available)
            item->setText("available");
        ui->listWidget_3->addItem(item);
    }

    for (int i = 0; i<colorManager->featureList->size();i++){
        QListWidgetItem *item = new QListWidgetItem(QString());
        Color *color = colorManager->featureList->at(i).getColor();
        item->setBackgroundColor(color->color);
        item->setText(colorManager->featureList->at(i).getName());
        ui->listWidget_2->addItem(item);
    }

}

void MainWindow::explorerToggled(bool toggled){
    if (toggled == false){
        ui->stackedWidget->setCurrentIndex(0);
        questionDialog->writeToLog("select<FeatureView>");
    }
    else{
        ui->stackedWidget->setCurrentIndex(1);
        questionDialog->writeToLog("select<PackageView>");
    }
}

void MainWindow::highlightColor(QListWidgetItem *item)
{
    QColor color = item->backgroundColor();
    color.setAlpha(170);
    QPalette palette = ui->listWidget->palette();
    palette.setColor(QPalette::Highlight,color);
    ui->listWidget->setPalette(palette);
}

void MainWindow::showListWidgetContextMenu(QPoint p){
    QMenu *menu = new QMenu(ui->listWidget);

    QAction *actionDeleteColor = new QAction(QIcon(QPixmap(QString(":/images/cross.png"))),QString("delete"),menu);
    lastSelectedListWidgetItem = ui->listWidget->itemAt(p);
    menu->addAction(actionDeleteColor);
    connect(actionDeleteColor,SIGNAL(triggered()),this,SLOT(deleteColorFromColorArray()));
    menu->exec(ui->listWidget->mapToGlobal(p));
    menu->show();

}

void MainWindow::showFeatureModelContextMenu(QPoint p){
    QMenu *menu = new QMenu(t);
    MyTreeWidgetItem *item = static_cast<MyTreeWidgetItem*>(t->itemAt(p));
    if (item->getBGColor()->getColor().isValid()){
        QAction *actionDeleteColor = new QAction(QIcon(QPixmap(QString(":/images/cross.png"))),QString("remove ColorAssignment"),menu);
        lastSelectedTreeWidgetItem = t->itemAt(p);
        menu->addAction(actionDeleteColor);
        connect(actionDeleteColor,SIGNAL(triggered()),this,SLOT(removeColorAssignment()));
    }
    QAction *actionAssignColor = new QAction(QIcon(QPixmap(QString(":/images/spectrum_small.png"))),QString("assign Color"),menu);
    lastSelectedTreeWidgetItem = t->itemAt(p);
    menu->addAction(actionAssignColor);
    t->unselect();
    item->setSelected(true);
    connect(actionAssignColor,SIGNAL(triggered()),t,SLOT(assignAutomatically()));
    menu->exec(t->mapToGlobal(p));
    menu->show();

}

void MainWindow::deleteColorFromColorArray(){
    Color *c = static_cast <MyListWidgetItem*>(lastSelectedListWidgetItem)->getBGColor();
    colorManager->colorArray->takeAt(colorManager->colorArray->indexOf(c,0));
    t->redrawListWidget();
}

void MainWindow::removeColorAssignment(){
    removeColorAssignment(static_cast<MyTreeWidgetItem*>(lastSelectedTreeWidgetItem));
}

void MainWindow::removeColorAssignment(MyTreeWidgetItem *item){
    questionDialog->writeToLog("deleteColor<1>");
    MyListWidgetItem *listItem = new MyListWidgetItem(QString(""));
    listItem->setBGColor(item->getBGColor());
    //Icon wichtig, damit Item überhaupt angezeigt wird!

    Feature *f = t->getCorrespondingFeature(item->text(0));
    colorManager->deleteColorForFeature(f);
    QIcon icon = QIcon();
    icon.addPixmap(QPixmap(QString(":/images/leer.png")),QIcon::Normal,QIcon::On);
    listItem->setIcon(icon);
    ui->listWidget->addItem(listItem);

    item->setBackgroundInvalid();
    t->itemWidget(item,1)->hide();
    t->redrawListWidget();
    updateSMVTreeTexture(f);
}

void MainWindow::initializeListWidget()
{
    ui->listWidget->clear();
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    for (int i = 0;i < this->colorManager->colorArray->size();i++)
    {
        MyListWidgetItem *item = new MyListWidgetItem(QString());
        Color color = Color(*colorManager->colorArray->at(i));
        if (!colorManager->FCPListContainsColor(new Color(color.color))){
            item->setBGColor(colorManager->colorArray->at(i));
            QIcon icon = QIcon();
            icon.addPixmap(QPixmap(QString(":/images/leer.png")),QIcon::Normal,QIcon::On);
            item->setIcon(icon);

            ui->listWidget->addItem(item);
        }
    }
    drawSaveButtonIcon();
}

void MainWindow::resetListWidget(){

    QTreeWidgetItemIterator it(t,QTreeWidgetItemIterator::NoChildren);
    while(*it){
        MyTreeWidgetItem *item = static_cast<MyTreeWidgetItem*>(*it);
        if (item->getBGColor()->color.isValid()){
            MyListWidgetItem *listItem = new MyListWidgetItem(QString(""));
            listItem->setBGColor(item->getBGColor());
            //Icon wichtig, damit Item überhaupt angezeigt wird!

            Feature *f = t->getCorrespondingFeature(item->text(0));
            colorManager->deleteColorForFeature(f);
            QIcon icon = QIcon();
            icon.addPixmap(QPixmap(QString(":/images/leer.png")),QIcon::Normal,QIcon::On);
            listItem->setIcon(icon);
            ui->listWidget->addItem(listItem);

            item->setBackgroundInvalid();
            t->itemWidget(item,1)->hide();

            updateSMVTreeTexture(f);
        }
        ++it;
    }

    this->colorManager->fillColorArray(colorManager->FCPList->size());
    t->redrawListWidget();
}

void MainWindow::drawSaveButtonIcon(){
    //Icon für Save-Button generieren
    int validColors = 0;
    QList <QColor> colors = QList <QColor>();
    int i = 0;
    while(validColors < 5 && i < t->getFeatureList()->size()){
        if (t->getFeatureList()->at(i).getColor()->getColor()!= QColor(220, 220, 220, 255)
            && t->getFeatureList()->at(i).getColor()->getColor()!= QColor(180, 180, 180, 255))
            {
            colors.push_back(t->getFeatureList()->at(i).getColor()->getColor());
            validColors++;
        }
        i++;
    }
    //QPixmap texture (30,30);
    QPixmap texture = QPixmap(QString(":/images/schatten.png"));
    QPainter painter(&texture);
    painter.setPen(Qt::white);
    QBrush brush(Qt::white,Qt::SolidPattern);
//    painter.setBrush(brush);
//    painter.drawRect(0,0,30,30);
    if (colors.size() > 0){
        painter.setPen(colors.at(0));
        brush.setColor(colors.at(0));
        painter.setBrush(brush);
        painter.drawRect(0,0,14,14);
        if (colors.size()>1){
            painter.setPen(colors.at(1));
            brush.setColor(colors.at(1));
            painter.setBrush(brush);
            painter.drawRect(15,0,14,14);
            if (colors.size()>2){
                painter.setPen(colors.at(2));
                brush.setColor(colors.at(2));
                painter.setBrush(brush);
                painter.drawRect(0,15,14,14);
                if (colors.size()>3){
                    painter.setPen(colors.at(3));
                    brush.setColor(colors.at(3));
                    painter.setBrush(brush);
                    painter.drawRect(15,15,14,14);
                }
            }
        }
    }
    QIcon icon (texture);
    ui->toolButton_save->setIcon(icon);
}

void MainWindow::updateSMVTreeTexture(Feature *feature){
    //this->parser->generateSTNodeTextures();
    this->parser->updateSTNodeTextures(feature);
    ui->treeWidget_packageView->resize(ui->treeWidget_packageView->size().width());
    ui->treeWidget_featureView->resize(ui->treeWidget_featureView->size().width());
    drawSaveButtonIcon();
    if (ui->tabWidget->currentIndex()!=-1){
        CodeView *view = static_cast<CodeView*>(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
        view->updateColor(feature);
    }
    //ui->plainTextEdit->processBackground();
}

void MainWindow::updateTabColors(int currentIndex){
    if (currentIndex != -1){
        CodeView *view = static_cast<CodeView*>(ui->tabWidget->widget(currentIndex));
        removeFinds();
        view->updateAllColors();
        if (view->justCreated == false)
            questionDialog->writeToLog("selectionChanged",view->file->fileName().remove(path));
    }
}

void MainWindow::updateTextEditFileNode(STNode *node){
    //ui->plainTextEdit->setFileNode(node);

//    myTextEdit *textEdit = new myTextEdit(this);
//    ui->tabWidget->addTab(textEdit,QString("test"));
//    textEdit->setFileNode(node);
}

void MainWindow::showEvent(QShowEvent *event){
    QMainWindow::showEvent(event);
    if (saveLoadShown)
        ui->dockWidget_colorAssignments->show();
    if (colorPickerShown)
        ui->dockWidget_colors->show();
    if (featureModelshown)
        ui->dockWidget_featureModel->show();
}

void MainWindow::hideEvent(QHideEvent *event){
    saveLoadShown = ui->dockWidget_colorAssignments->isVisible();
    featureModelshown = ui->dockWidget_featureModel->isVisible();
    colorPickerShown = ui->dockWidget_colors->isVisible();
    QMainWindow::hideEvent(event);
//    ui->dockWidget_colorAssignments->setVisible(saveShown);
//    ui->dockWidget_featureModel->setVisible(featureShown);
//    ui->dockWidget_colors->setVisible(colorShown);
}

//Finder-Functions
void MainWindow::search(){

    fileNodes->clear();
    ui->listWidget_results->clear();

    if (ui->radioButton_current->isChecked()){
        searchCurrentFile();
        if (ui->lineEdit_find->text() != "")
            questionDialog->writeToLog("search<current>(" + ui->lineEdit_find->text() + ")");
    }else{
        if (ui->lineEdit_find->text() != "")
            questionDialog->writeToLog("search<project>(" + ui->lineEdit_find->text() + ")");
        QTreeWidgetItemIterator it(ui->treeWidget_packageView,QTreeWidgetItemIterator::NoChildren);
        while(*it){

            QString fileName = (*it)->text(0);
            QString dir = "/" + (*it)->text(0);

            QTreeWidgetItem *pathItem = (*it);
            while(pathItem->parent()){
                pathItem = pathItem->parent();
                if (pathItem->parent())
                    dir.prepend("/"+pathItem->text(0));
            }

            dir = dir.remove(0,1);
            dir = path + "/" + dir;

            QFile *file = new QFile(dir);
            QString text = "";
            if(file->exists()){
                file->open(QIODevice::ReadOnly);
                text = static_cast<QString>(file->readAll());
                file->close();
            }
            int count = 0;
            text.prepend(" ");
            text.append(" ");
            QRegExp search = QRegExp(ui->lineEdit_find->text());
            if (ui->checkBox_wholeWords->isChecked())
                search = QRegExp("[\\W\\n\\r]" + ui->lineEdit_find->text() + "[\\W\\n\\r]");

            if (ui->checkBox_caseSensitive->isChecked()){
                search.setCaseSensitivity(Qt::CaseSensitive);
                count = text.count(search);
            }
            if (!ui->checkBox_caseSensitive->isChecked()){
                search.setCaseSensitivity(Qt::CaseInsensitive);
                count = text.count(search);
            }

            QString cnt = "";
            cnt = cnt.setNum(count);
            if (count!= 0){
                ui->listWidget_results->addItem(cnt + "x at ..." + dir.remove(0,path.length()));
                fileNodes->push_back((*it));
            }
            ++it;
        }
    }
}

void MainWindow::openFileFromListWidget(QListWidgetItem *item){

    bool exists = false;
    for (int i = 0; i < ui->tabWidget->count();i++){
        if (ui->tabWidget->tabText(i) == item->text().split("/").last()){
            CodeView *view = static_cast<CodeView*>(ui->tabWidget->widget(i));
            if (view->file->fileName() == path + item->text().split("x at ...").last()){
                exists = true;
                ui->tabWidget->setCurrentIndex(i);
                break;
            }
        }
    }
    if (!exists){
        ui->dockWidget_finder->setCursor(Qt::WaitCursor);
        ui->listWidget_results->setCursor(Qt::WaitCursor);
        QString dir = path + item->text().split("x at ...").last();
        QFile *file = new QFile(dir);
        CodeView *codeView = new CodeView(t,static_cast<STNode*>(fileNodes->at(ui->listWidget_results->currentRow())),this,file,ui->horizontalSlider->value());

        //Tab einfügen. WICHTIG: alle Werte, die die Größe, des TextEdits betreffen, erst danach abfragen!
        //                       (weil das Widget erst dann gezeichnet ist)
        int i = ui->tabWidget->addTab(codeView,item->text().split("/").last());
        ui->tabWidget->setCurrentIndex(i);

        //QGraphicsItems zeichnen (darf erst nach dem Zeichnen des CodeViews gemacht werden, weil sonst manche Größen nicht stimmen)
        codeView->addFractureRectangles();
        codeView->fillLineNumberWidget();
        codeView->drawBackgroundFractures();

        QTimer *timer = new QTimer(this);
        timer->setSingleShot(true);
        connect(timer, SIGNAL(timeout()), this, SLOT(writeToLogFileOpened()));
        timer->start(10);
        ui->radioButton_current->setChecked(true);
    }
}

bool MainWindow::searchCurrentFile(){
    //searchflags setzten
    QFlags<QTextDocument::FindFlag> flgs;
    if (ui->checkBox_caseSensitive->isChecked() && ui->checkBox_wholeWords->isChecked())
        flgs = QTextDocument::FindCaseSensitively | QTextDocument::FindWholeWords;
    else if (!ui->checkBox_caseSensitive->isChecked() && ui->checkBox_wholeWords->isChecked())
        flgs = QTextDocument::FindWholeWords;
    else if (ui->checkBox_caseSensitive->isChecked() && !ui->checkBox_wholeWords->isChecked())
        flgs = QTextDocument::FindCaseSensitively;
    else if (!ui->checkBox_caseSensitive->isChecked() && !ui->checkBox_wholeWords->isChecked())
        flgs = 0;
    
    if (ui->tabWidget->currentIndex() != -1){
        if(ui->lineEdit_find->text()!=lastSearch){
            if (lastCodeView!=0 && !finds->isEmpty()){
                for (int i = 0; i < finds->size();i++){
                    lastCodeView->textScene->removeItem(finds->at(i));
                }
            }
            CodeView *currentView = static_cast<CodeView*>(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
            QGraphicsTextItem *edit = currentView->getEdit();
            QTextCursor cursor = QTextCursor(edit->document());
            finds->clear();
            while(!cursor.isNull()){
                cursor = edit->document()->find(ui->lineEdit_find->text(),cursor,flgs);
                if (!cursor.isNull()){
                    int lineHeight = currentView->textEdit->fontMetrics().lineSpacing();

                    //reale Länge des Wortes berechnen
                    cursor.movePosition(QTextCursor::EndOfWord,QTextCursor::KeepAnchor);
                    //cursor.setPosition(cursor.position()+ (ui->lineEdit_find->text().length()),QTextCursor::KeepAnchor);
                    int lengthOfWord = currentView->textEdit->fontMetrics().width(cursor.selectedText());

                    //reale x-Position berechnen
                    int xPos = calculateXPos(cursor,edit->document(),currentView->textEdit->fontMetrics());
                    //reale y-Position berechnen
                    int line = findLine(cursor,cursor.anchor())*lineHeight;

                    //zeichnen
                    finds->push_back(currentView->textScene->addRect(0,0,
                                                                     lengthOfWord,
                                                                     lineHeight,
                                                                     QPen(Qt::yellow),
                                                                     QBrush(Qt::yellow)));
                    finds->last()->setPos(xPos,line + currentView->textEdit->fontMetrics().descent()+2);
                    finds->last()->stackBefore(edit);
                }
            }
            if (finds->isEmpty()){
                QMessageBox *msg = new QMessageBox(this);
                msg->information(this,"",ui->lineEdit_find->text()+" not found!");
            }
            lastSearch = ui->lineEdit_find->text();
            lastCodeView = currentView;
            if (!finds->isEmpty()){
                findsIndex = 0;
                currentView->textView->centerOn(finds->at(findsIndex));
                findsIndex++;
            }
        }
        else if(!finds->isEmpty()){
            CodeView *currentView = static_cast<CodeView*>(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
            if (currentView == lastCodeView){
                if (findsIndex < finds->size()){
                    currentView->textView->centerOn(finds->at(findsIndex));
                    findsIndex++;
                }else{
                    findsIndex = 0;
                    currentView->textView->centerOn(finds->at(findsIndex));
                    findsIndex++;
                }
            }
        }
        else if (finds->isEmpty()){
            QMessageBox *msg = new QMessageBox(this);
            msg->information(this,"",ui->lineEdit_find->text()+" not found!");

        }
    }
}

int MainWindow::findLine(QTextCursor cursor,int findPos){
    bool moved = cursor.movePosition(QTextCursor::Start,QTextCursor::MoveAnchor);
    int line = 0;
    int currentPos = 0;
    while(currentPos < findPos && moved){
        moved = cursor.movePosition(QTextCursor::Down,QTextCursor::MoveAnchor);
        currentPos = cursor.position();
        line++;
    }
    cursor.setPosition(findPos);
    if (cursor.columnNumber()>0)
        return line - 1;
    else
        return line;
}

int MainWindow::calculateXPos(QTextCursor cursor,QTextDocument *doc,QFontMetrics metrics){
    cursor.movePosition(QTextCursor::StartOfLine,QTextCursor::KeepAnchor);
    return metrics.width(cursor.selectedText()) + 3;
}

void MainWindow::removeFinds(){
    if (lastCodeView!=0 && !finds->isEmpty()){
        for (int i = 0; i < finds->size();i++){
            lastCodeView->textScene->removeItem(finds->at(i));
        }
    }
    finds->clear();
    lastSearch = "";
}

void MainWindow::resetLastSearch(){
    lastSearch = "";
}

void MainWindow::setFilePath(){
    QTreeWidgetItemIterator it(ui->treeWidget_packageView,QTreeWidgetItemIterator::NoChildren);
    while(*it){
        STNode *item = static_cast<STNode*>(*it);
        QString dir = "/" + item->text(0);

        QTreeWidgetItem *pathItem = item;
        while(pathItem->parent()){
            pathItem = pathItem->parent();
            if (pathItem->parent())
                dir.prepend("/"+pathItem->text(0));
        }

        dir = dir.remove(0,1);
        dir = path + "/" + dir;
        item->setPath(dir);
        ++it;
    }
}

void MainWindow::searchInFeatureModel(){
    if (ui->lineEdit_featureSearch->text() != ""){
        if (lastFeatureSearch != ui->lineEdit_featureSearch->text())
            lastFeatureModelItem = t->topLevelItem(0);
        bool found = false;
        for (int i = 0; i < 2; i++){
            QTreeWidgetItemIterator it(lastFeatureModelItem, QTreeWidgetItemIterator::All);
            while(*it){
                //QTreeWidgetItem *item = static_cast<QTreeWidgetItem*>(*it);
                if ((*it)->text(0).contains(ui->lineEdit_featureSearch->text(),Qt::CaseInsensitive)){
                    found = true;
                    t->scrollToItem((*it));
                    t->unselect();
                    (*it)->setSelected(true);
                    ++it;
                    if (*it)
                        lastFeatureModelItem = (*it);
                    else
                        lastFeatureModelItem = t->topLevelItem(0);
                    break;
                }
                ++it;
            }
            if (found)
                break;
            else
                lastFeatureModelItem = t->topLevelItem(0);
        }

        lastFeatureSearch = ui->lineEdit_featureSearch->text();
        QString fileName = "";
        if (ui->tabWidget->currentIndex()!=-1){
            CodeView *view = static_cast<CodeView*>(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
            fileName = view->file->fileName().remove(path);
        }
        questionDialog->writeToLog("search<feature>(" + ui->lineEdit_featureSearch->text() + ")",fileName);
    }
}

