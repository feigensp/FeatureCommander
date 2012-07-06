#ifndef MYTREEWIDGETITEM_H
#define MYTREEWIDGETITEM_H

#include <QTreeWidgetItem>
#include "color.h"

class MyTreeWidgetItem : public QTreeWidgetItem
{
public:

    MyTreeWidgetItem(const QStringList &strings);
    void setBGColor(Color *c);
    Color* getBGColor();
    void setBackgroundInvalid();

private:
    Color *bgColor;
};

#endif // MYTREEWIDGETITEM_H
