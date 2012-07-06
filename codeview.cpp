#include "codeview.h"


CodeView::CodeView(FeatureTreeWidget *t,STNode *i,QWidget *parent,QFile *f,int opacity)
{

    file = f;
    treeItem = i;
    featureOpacity = opacity;
    justCreated = true;
    featureTree = t;

    //Horizontales Layout
    QHBoxLayout *topLayout = new QHBoxLayout(this);
    setLayout(topLayout);
    topLayout->setMargin(0);
    topLayout->setSpacing(0);

    textEdit = new QTextEdit(this);
    textEdit->setLineWrapMode(QTextEdit::NoWrap);
    textEdit->setAcceptDrops(false);

    QWidget *test = new QWidget(this);
    topLayout->addWidget(test);

    //Scene und View für Balkenansicht erstellen
    sideBarScene = new QGraphicsScene();
    sideBarView = new QGraphicsView(sideBarScene);
    sideBarView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sideBarView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //View für rechte Balkenansicht
    rightSideBarView = new QGraphicsView(sideBarScene);
    rightSideBarView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sideBarView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Scene und View für Zeilennummern erstellen
    lineNumbersScene = new QGraphicsScene();
    lineNumbersView = new QGraphicsView(lineNumbersScene);
    lineNumbersView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lineNumbersView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Scene und View für Textansicht erstellen
    textScene = new QGraphicsScene();
    textView = new QGraphicsView(textScene);

    //Scrollbar von Balkenansicht übernehmen
    lineNumbersView->setVerticalScrollBar(sideBarView->verticalScrollBar());
    //textEdit->setVerticalScrollBar(sideBarView->verticalScrollBar());
    textView->setVerticalScrollBar(sideBarView->verticalScrollBar());



//    sideBarView->setFixedWidth(40);
//    sideBarView->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    lineNumbersView->setBackgroundBrush(QBrush(QColor(230,230,230,255),Qt::SolidPattern));

    topLayout->addWidget(lineNumbersView,0);
    topLayout->addWidget(sideBarView,0);
    //topLayout->addWidget(textEdit);
    topLayout->addWidget(textView,0);
    topLayout->addWidget(rightSideBarView,0);

    //Datei einlesen
    QString text = "";
    if(file->exists()){
        file->open(QIODevice::ReadOnly);
        text = static_cast<QString>(file->readAll());
        file->close();
    }
    textEdit->setPlainText(text);
//    fillLineNumberWidget();

    //Schriftart
    QFont font = QFont (QFont(QString("Courier"),9,4,false));
    textEdit->setFont(font);

    //textedit dem textview hinzufügen

    edit = textScene->addText("no file loaded");
    edit->setAcceptDrops(false);
    textView->setDragMode(QGraphicsView::NoDrag);


    edit->setDocument(textEdit->document());
    edit->setCursor(Qt::IBeamCursor);
    edit->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    edit->setFlag(QGraphicsItem::ItemIsSelectable,false);
    edit->setFlag(QGraphicsItem::ItemIsMovable,false);
    edit->setFlag(QGraphicsItem::ItemIsFocusable,false);


    //edit->setTextInteractionFlags(Qt::TextEditorInteraction);

    //Breite der Zeilennummernansicht
    QString maxNumber = "";
    maxNumber = maxNumber.setNum(textEdit->document()->lineCount());
    lineNumbersView->setFixedWidth((maxNumber.length()+1)*textEdit->fontMetrics().width(' '));


//    //Tab einfügen. WICHTIG: alle Werte, die die Größe, des TextEdits betreffen, erst danach abfragen!
//    //                       (weil das Widget erst dann gezeichnet ist)
//    tabWidget->insertTab(0,this,static_cast<QString>(file->fileName().split("/").last()));
//    tabWidget->setCurrentIndex(0);

    //Größe der sideBarScene exakt an textEdit anpassen
    //ist gleichzeitig das RootItem für alle Fractures (da alle darin enthalten sind)
    root = new SideBarFracture(featureTree,0,0,0,0,0,35,
                               textEdit->document()->size().height(),
                               sideBarScene,
                               textEdit->document()->lineCount(),"");
    //search("bla");
//    MyCPPSyntaxHighlighter *highlighter = new MyCPPSyntaxHighlighter(edit->document());
    Highlighter *highlighter = new Highlighter(edit->document());
    root->setVisible(false);

//    textView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//    sideBarView->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
//    lineNumbersView->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
//    rightSideBarView->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);

}

QGraphicsTextItem *CodeView::getEdit(){
    return edit;
}

void CodeView::setFeatureOpacity(int opacity){
    featureOpacity = opacity;
    updateBackground();

}

void CodeView::updateBackground(){

    QList <QGraphicsItem*> list = textScene->items(0,0,5,textScene->height(),Qt::IntersectsItemBoundingRect);
    for (int i = 0; i < list.size(); i++){
        if (list.at(i)!=edit && static_cast<QGraphicsRectItem*>(list.at(i))->brush().color()!=Qt::white
            && static_cast<QGraphicsRectItem*>(list.at(i))->brush().color()!=Qt::yellow){
            BackgroundFracture *item = static_cast<BackgroundFracture*>(list.at(i));
            if (item->getFeature()!=0){
                item->setColor(featureOpacity);
            }
        }
    }
}

void CodeView::drawBackgroundFractures(){

    int itemWidth = 5;
    int itemSpace = 2;
    int itemPlusSpace = itemWidth + itemSpace;
    int currentX = 3;
    int indent = 0;
    QList <QGraphicsItem*> list = sideBarScene->items(currentX,0,5,textScene->height(),Qt::IntersectsItemBoundingRect);
    while(!list.isEmpty() && (currentX + itemPlusSpace < root->rect().width())){
        list = sideBarScene->items(currentX,0,5,textScene->height(),Qt::IntersectsItemBoundingRect);
        for (int i = 0; i < list.size(); i++){
            if (list.at(i)->parentItem()==0){
                SideBarFracture *item = static_cast<SideBarFracture*>(list.at(i));

                if (item != root && item->getFeature()!=0){
                    int width = textScene->width();
                    //                if (textView->width()>textScene->width())
                    //                    width = textView->width();
                    BackgroundFracture *rect = new BackgroundFracture(featureTree,item->brush().color(),item->getFeature(),indent,item->y(),0,0,width,item->rect().height(),textScene);
                    rect->stackBefore(edit);
                    item->setBGFracture(rect);
                    QGraphicsRectItem *whiteRect = textScene->addRect(rect->rect(),QPen(Qt::white),QBrush(Qt::white));
                    whiteRect->setPos(rect->pos());
                    whiteRect->stackBefore(rect);
                }
            }
        }
        currentX += itemPlusSpace;
        //indent += 5;
    }
    this->layout()->update();
}

void CodeView::updateAllColors(){
    for (int i = 0; i < sideBarScene->items().size();i++){
        if (sideBarScene->items().at(i)->parentItem() == 0){
            SideBarFracture *fracture = static_cast <SideBarFracture*>(sideBarScene->items().at(i));
            fracture->setColor();
        }
    }
    updateBackground();
}

void CodeView::updateColor(Feature *f){
    for (int i = 0; i < sideBarScene->items().size();i++){
        if (sideBarScene->items().at(i)->parentItem() == 0){
            SideBarFracture *fracture = static_cast <SideBarFracture*>(sideBarScene->items().at(i));
            if (fracture->getFeature()==f){
                fracture->setColor();
            }
        }
    }
    for (int i = 0; i < textScene->items().size();i++){
        if (textScene->items().at(i)!=edit){
            BackgroundFracture *fracture = static_cast <BackgroundFracture*>(textScene->items().at(i));
            if (fracture->getFeature() == f){
               fracture->setColor(featureOpacity);
            }
        }
    }
}

void CodeView::fillLineNumberWidget(){
    QString maxNumber = "";
    maxNumber = maxNumber.setNum(textEdit->document()->lineCount());
//    QGraphicsTextItem *number = new QGraphicsTextItem("");
//    number->setHtml("<bdo dir=\"rtl\">Here is some Hebrew text!</bdo>");
//    lineNumbersScene->addItem(number);
//    for (int i = 0; i < textEdit->document()->lineCount();i++){
//
//    }

    for (int i = 0; i < textEdit->document()->lineCount();i++){
        int start = i * textEdit->fontMetrics().lineSpacing();
        QString index = "";
        index = index.setNum(i+1);
        int indexLength = index.length();
        for (int j = 0; j < maxNumber.length()-indexLength;j++){
            index.prepend(" ");
        }
        QGraphicsTextItem *number = new QGraphicsTextItem(index);
        number->setZValue(i+1);
        number->setFont(QFont(QString("Courier"),9,4,false));
        //number->setHtml("<font color=\"grey\">" + index + "</font>");
        number->setPos(0,start);

        lineNumbersScene->addItem(number);
    }

}

void CodeView::addFractureRectangles(){

    for (int i = 0; i < treeItem->featureFractureList->size();i++){
        int start = (treeItem->featureFractureList->at(i).getOffset()-1) * textEdit->fontMetrics().lineSpacing() + textEdit->fontMetrics().descent();
        int length = (treeItem->featureFractureList->at(i).getLength()+1) * textEdit->fontMetrics().lineSpacing();
        FeatureFracture *fracture = &treeItem->featureFractureList->at(i);
        Feature *feature = fracture->getFeature();
        SideBarFracture *rect = new SideBarFracture(featureTree,
                                                    feature,
                                                    3,start,0,0,5,
                                                    length,
                                                    sideBarScene,
                                                    treeItem->featureFractureList->at(i).getLength(),fracture->completeName);

    }

    for (int i = 0; i < sideBarScene->items().size();i++){
        if (sideBarScene->items().at(i)->parentItem() == 0){
            SideBarFracture *fracture = static_cast <SideBarFracture*>(sideBarScene->items().at(i));
            fracture->setColor();
        }
    }


    rightSideBarView->scale(-1, 1);
    rightSideBarView->fitInView(rightSideBarView->sceneRect(),Qt::IgnoreAspectRatio);
//    for (int i = 0; i < rightSideBarView->items().size();i++){
//        if (rightSideBarView->items().at(i)->parentItem()!=0){
//            rightSideBarView->items().at(i)->scale(1,10);
//        }
//    }
}

void CodeView::resizeEvent(QResizeEvent *event){

//    textView->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
//    sideBarView->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
//    lineNumbersView->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
//    rightSideBarView->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);


    
    sideBarView->setFixedWidth(sideBarScene->width());
    rightSideBarView->setFixedWidth(sideBarView->width());
    textView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    lineNumbersView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    rightSideBarView->fitInView(rightSideBarView->sceneRect(),Qt::IgnoreAspectRatio);
//    textView->setFixedHeight(event->size().height()-1);
//
//    sideBarView->setFixedHeight(textView->height());
//
//    if (edit->document()->size().width() > textView->width())
//        sideBarView->setFixedHeight(textView->size().height() - textView->horizontalScrollBar()->size().height());
//    if (edit->document()->size().height() < textView->size().height())
//        sideBarView->setFixedHeight(edit->document()->size().height());
//
//    lineNumbersView->setFixedHeight(sideBarView->height());
//    rightSideBarView->setFixedSize(sideBarView->size());
//    rightSideBarView->fitInView(sideBarScene->itemsBoundingRect(),Qt::IgnoreAspectRatio);

    QWidget::resizeEvent(event);
//    //Start und EndZeile des aktuellen CodeViews updaten
//    QPolygonF poly = lineNumbersView->mapToScene(lineNumbersView->rect());
//    QList  <QGraphicsItem*> list = lineNumbersScene->items(poly);
//    QString start = "";
//    QString end = "";
//    if (list.size()>0){
//        QGraphicsTextItem *item = static_cast<QGraphicsTextItem*>(list.at(list.size()-1));
//        start = item->document()->toPlainText();
//        end = static_cast<QGraphicsTextItem*>(list.at(0))->document()->toPlainText();
////        ui->label_startline->setText("startLine" + start);
////        ui->label_endline->setText("endLine: " + end);
//
//    }

}
