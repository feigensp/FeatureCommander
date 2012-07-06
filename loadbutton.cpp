#include "loadbutton.h"

LoadButton::LoadButton(QWidget *parent, ColorManager *manager) :
    QToolButton(parent)
{
    setParent(parent);
    colorManager = manager;
    setToolTip("load ColorAssignment");
}
void LoadButton::setFileName(QString text){
    fileName = text;
}

void LoadButton::testHide(){
    load();
}

void LoadButton::load(){
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
    deleteLater();
}
