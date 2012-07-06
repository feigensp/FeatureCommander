#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QApplication>
#include <QTreeView>
#include <QStandardItemModel>
#include <QItemDelegate>
#include <QPainter>
#include <QTreeWidget>
#include <QCheckBox>
#include "featuretreewidget.h"


//passt die Darstellung der einzelnen Items im TreeWidget an
class ItemDelegate : public QItemDelegate
{
public:

    ItemDelegate(QTreeWidget *tW, bool w, int c = 0);
    //rowHeight anpassen
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    //Highlighting anpassen
    void drawBackground(QPainter *painter, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const;
    QTreeWidget *treeWidget;
    //Workaround, weil drawBackground nicht virtual -> wird ursprünglich in subclass nicht aufgerufen
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    bool isSMVTreeWidget;
    int checkBoxWidth;

    QModelIndex *hoverItem;
    int rowHeight;

    void setRowHeight(int r);
    void setHoverItem(QModelIndex *item);

};

#endif // ITEMDELEGATE_H
