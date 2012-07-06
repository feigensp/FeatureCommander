#include "textedit.h"
#include "codeview.h"
TextEdit::TextEdit(QWidget *parent)
{
    this->setParent(parent);
    bg = QPixmap();
    bgRect = QRect();

}

void TextEdit::scrollContentsBy(int dx, int dy){

    bgRect.translate(-1*dx,-1*dy);
    QTextEdit::scrollContentsBy(dx, dy);
}

void TextEdit::paintEvent(QPaintEvent *e){
    QTextEdit::paintEvent(e);

    if(&bg){
        bg = bg.scaled(viewport()->rect().width(),bg.height(),Qt::IgnoreAspectRatio);

        // neue Palette, die neuberechneten Hintergrund enthält
        QPalette tmp = QPalette();
        tmp.setBrush(QPalette::Base,QBrush(bg.copy(bgRect)));
        setPalette(tmp);
    }
}
