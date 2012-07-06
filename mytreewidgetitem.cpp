#include "mytreewidgetitem.h"

MyTreeWidgetItem::MyTreeWidgetItem(const QStringList &strings)
{
    setText(0,strings.at(0));
    bgColor = new Color(QColor());
}

void MyTreeWidgetItem::setBGColor(Color *c){
    bgColor = c;
    setBackgroundColor(0,c->getColor());
    c->available = false;

}
Color* MyTreeWidgetItem::getBGColor(){
    return bgColor;
}

void MyTreeWidgetItem::setBackgroundInvalid(){
    bgColor->setAvailable(true);
    setBGColor(new Color(QColor(-1,-1,-1,-1)));
    setBackground(0,Qt::NoBrush);
}

