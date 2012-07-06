#include "savecolorassignment.h"
#include "mainwindow.h"


SaveColorAssignment::SaveColorAssignment(QWidget *parent,MainWindow *mw,QIcon *icon,QFrame *f,QList<Color*> *c,vector <FeatureColorPair> *fcp,ColorManager *man,QString *path) :
                                         QWidget(parent)
{
    //featureTree = f;
    //listWidget = l;
    colorArray = c;
    FCPList = fcp;
    frame = f;
    manager = man;

    load = new LoadButton(parent,manager);
    frame->layout()->addWidget(load);

    load->show();
    connect(load,SIGNAL(pressed()),load,SLOT(testHide()));
    connect(load,SIGNAL(pressed()),mw,SLOT(updateAllColors()));

    QString project = path->split("/").last();

    QDir folder (*path);
    folder.mkdir("savedColorAssignments");

    QString fileStr = *path + "/savedColorAssignments/" + project;
    int num = 1;
    QFile file(fileStr +".txt" );
    QString number = "";
    number = number.setNum(num);
    while (file.exists(fileStr+ number +".txt")){
        number = number.setNum(num);
        file.setFileName(fileStr + number + ".txt");
        num++;
    }
    QFile newFile(fileStr + number + ".txt" );
    load->setIcon(*icon);
    load->setIconSize(QSize(30,30));
    load->setAutoRaise(true);
    load->setToolButtonStyle(Qt::ToolButtonIconOnly);
    load->setFileName(newFile.fileName());


    newFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&newFile);

    QDomDocument doc("savedColorAssignment");
    QDomElement root = doc.createElement("savedColorAssignment");
    doc.appendChild(root);

    //ListWidget Daten schreiben
//    QDomElement listWidgetColors = doc.createElement("listWidget");
//    listWidgetColors.setTagName("ListWidget");
//    root.appendChild(listWidgetColors);
    //root.setTagName("ListWidgetColors");
    //root.setAttribute("attribute",5);

//    for (int i = 0; i < listWidget->count();i++){
//        QDomElement lwColor = doc.createElement("lwColor");
//
//        MyListWidgetItem *item = static_cast<MyListWidgetItem*> (listWidget->item(i));
//        Color *c = item->getBGColor();
//        int r = c->color.red();
//        int g = c->color.green();
//        int b = c->color.blue();
//
//        lwColor.setTagName("color");
//
//        lwColor.setAttribute("index",i);
//
//        lwColor.setAttribute("r",r);
//        lwColor.setAttribute("g",g);
//        lwColor.setAttribute("b",b);
//
//        if (c->isCustom())
//            lwColor.setAttribute("isCustom",1);
//        else
//            lwColor.setAttribute("isCustom",0);
//        listWidgetColors.appendChild(lwColor);
//    }
//    //FeatureTreeWidget Daten schreiben
//    QDomElement featureTreeColors = doc.createElement("featureTree");
//    featureTreeColors.setTagName("featureTree");
//    root.appendChild(featureTreeColors);
//
//    QTreeWidgetItemIterator it (featureTree,QTreeWidgetItemIterator::NoChildren);
//    while(*it){
//        MyTreeWidgetItem *item = static_cast<MyTreeWidgetItem*> (*it);
//        if (item->getBGColor()->color.isValid()){
//            QDomElement ftColor = doc.createElement("ftColor");
//            Color *c = item->getBGColor();
//            int r = c->color.red();
//            int g = c->color.green();
//            int b = c->color.blue();
//
//            ftColor.setTagName("color");
//            ftColor.setAttribute("feature",item->text(0));
//            ftColor.setAttribute("r",r);
//            ftColor.setAttribute("g",g);
//            ftColor.setAttribute("b",b);
//
//
//            if (c->isCustom())
//                ftColor.setAttribute("isCustom",1);
//            else
//                ftColor.setAttribute("isCustom",0);
//            featureTreeColors.appendChild(ftColor);
//        }
//        ++it;
//    }

    //FCPList Daten schreiben
    QDomElement fcpListColors = doc.createElement("FCPList");
    fcpListColors.setTagName("FCPList");
    root.appendChild(fcpListColors);

    for (int i = 0; i < FCPList->size();i++){
        QDomElement fcpColors = doc.createElement("fcpColors");
        FeatureColorPair *fcp = &FCPList->at(i);
        Color *c = fcp->color;
        Feature *f = fcp->feature;

        int r = c->color.red();
        int g = c->color.green();
        int b = c->color.blue();

        fcpColors.setTagName("color");

        fcpColors.setAttribute("index",i);
        fcpColors.setAttribute("feature",f->getName());
        fcpColors.setAttribute("r",r);
        fcpColors.setAttribute("g",g);
        fcpColors.setAttribute("b",b);

        if (c->isCustom())
            fcpColors.setAttribute("isCustom",1);
        else
            fcpColors.setAttribute("isCustom",0);
        //wenn Farbe = Default-Grauwert
        if (c->color==QColor(220, 220, 220, 255) || c->color==QColor(180, 180, 180, 255)){
            fcpColors.setAttribute("isCustom",2);
        }
        fcpListColors.appendChild(fcpColors);
    }

    //ColorArray Daten schreiben
    QDomElement colorArrayColors = doc.createElement("colorArray");
    colorArrayColors.setTagName("colorArray");
    root.appendChild(colorArrayColors);

    for (int i = 0; i < colorArray->size();i++){
        QDomElement caColor = doc.createElement("caColor");
        Color *c = colorArray->at(i);
        int r = c->color.red();
        int g = c->color.green();
        int b = c->color.blue();

        caColor.setTagName("color");

        caColor.setAttribute("index",i);

        caColor.setAttribute("r",r);
        caColor.setAttribute("g",g);
        caColor.setAttribute("b",b);

        if (c->isCustom())
            caColor.setAttribute("isCustom",1);
        else
            caColor.setAttribute("isCustom",0);
        colorArrayColors.appendChild(caColor);
    }

    doc.save(out,10);
    newFile.close();
}

void SaveColorAssignment::loadC(){
    load->setVisible(false);
    load->setIconSize(QSize(50,50));
}
