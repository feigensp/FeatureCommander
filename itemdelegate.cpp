#include "itemdelegate.h"
#include "smvtreewidget.h"

ItemDelegate::ItemDelegate(QTreeWidget *tW,bool w,int c)
{
    isSMVTreeWidget = w;
    treeWidget = tW;
    checkBoxWidth = c;
    hoverItem = 0;
    rowHeight = 29;
}

QSize ItemDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    if (hoverItem != 0 && index == *hoverItem)
       return QSize(rowHeight,rowHeight);
    if (isSMVTreeWidget)
       return QSize(rowHeight,rowHeight);
    else
       return QSize(20,20);

}
void ItemDelegate::setHoverItem(QModelIndex *item){
    hoverItem = item;
}
void ItemDelegate::setRowHeight(int r){
    rowHeight = r;
}

void ItemDelegate::drawBackground(QPainter *painter,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const
{
    if (isSMVTreeWidget && option.showDecorationSelected && (option.state & QStyle::State_Selected)) {
        QVariant valueBackground = index.data(Qt::BackgroundRole);
        QVariant valueText = index.data(Qt::EditRole);
        if (qVariantCanConvert<QBrush>(valueBackground) && qVariantCanConvert<QString>(valueText)) {
            QPointF oldBO = painter->brushOrigin();
            painter->setPen(Qt::red);
            painter->setBrushOrigin(option.rect.topLeft());
            painter->fillRect(option.rect, qvariant_cast<QBrush>(valueBackground));
            QRect rect = option.rect;
            rect.setX(rect.x()+3);
            painter->setPen(Qt::black);
            //painter->setBrush(QBrush(Qt::red,Qt::SolidPattern));
            painter->drawText(rect,qvariant_cast<QString>(valueText),QTextOption(Qt::AlignVCenter));

            painter->setBrushOrigin(oldBO);
        }
    }else if (!isSMVTreeWidget && option.showDecorationSelected && (option.state & QStyle::State_Selected)) {
        QVariant valueBackground = index.data(Qt::BackgroundRole);
        QVariant valueText = index.data(Qt::EditRole);
        if (qVariantCanConvert<QString>(valueText)) {
            QPointF oldBO = painter->brushOrigin();
            QPen pen = QPen(QColor(0,0,0,80));
            pen.setWidth(2);
            painter->setPen(pen);
            QRect rect = option.rect;
            //mit Checkboxen
            //rect.setX(rect.x()+21);
            //ohne
            rect.setX(rect.x());
            rect.setRight(rect.right()-1);
            painter->setBrushOrigin(rect.topLeft());

            if (qVariantCanConvert<QBrush>(valueBackground)){
                painter->setBrush(qvariant_cast<QBrush>(valueBackground));
                painter->drawRoundedRect(rect,2,2);
            }else{
                painter->setBrush(Qt::NoBrush);
                painter->drawRoundedRect(rect,2,2);

            }
            //painter->drawRoundedRect(rect,2,2);
            rect.setX(rect.x()+2);
            painter->setPen(Qt::black);
            //painter->setBrush(QBrush(Qt::red,Qt::SolidPattern));
            painter->drawText(rect,qvariant_cast<QString>(valueText),QTextOption(Qt::AlignVCenter));
            painter->setBrushOrigin(oldBO);
        }
    }

}

void ItemDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    QItemDelegate::paint(painter,option,index);
    drawBackground(painter, option, index);

}

