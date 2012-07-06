#include "mylistwidgetitem.h"

MyListWidgetItem::MyListWidgetItem(const QString &text)
{
    setText(text);
    bgColor = new Color();

}

void MyListWidgetItem::setBGColor(Color *c){
    bgColor = c;
    setBackgroundColor(c->getColor());

    //c->available = false;
}
Color* MyListWidgetItem::getBGColor(){
    return bgColor;
}


