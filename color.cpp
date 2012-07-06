#include "color.h"

Color::Color(QColor c){
        color = c;
        available = true;
        custom = false;
}
Color::Color(){
        color = QColor();
        available = true;
        custom = false;
}

void Color::setIsChildFeature(bool yesOrNo){
    isChild = yesOrNo;
}

bool Color::isAvailable(){
    return available;
}

void Color::setAvailable(bool a){
    available = a;
}

QColor Color::getColor(){
    return color;
}
bool Color::isCustom(){
    return custom;
}

//Buggy??
bool Color::operator ==(Color c){

    return (this->color.convertTo(QColor::Rgb) == c.color.convertTo(QColor::Rgb));
}

void Color::setParentName(QString name){
    this->parent = name;
}

QString Color::getParentName(){
    return this->parent;
}

void Color::setCustom(bool c){
    custom = c;
}
