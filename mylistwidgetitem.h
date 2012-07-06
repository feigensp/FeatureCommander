#ifndef MYLISTWIDGETITEM_H
#define MYLISTWIDGETITEM_H

#include <QListWidgetItem>
#include "color.h"
#include <QMenu>

class MyListWidgetItem : public QListWidgetItem
{
public:
    MyListWidgetItem(const QString &text);
    void setBGColor(Color *c);
    Color* getBGColor();


private:
    Color *bgColor;
};

#endif // MYLISTWIDGETITEM_H
