#ifndef MYCPPSYNTAXHIGHLIGHTER_H
#define MYCPPSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextDocument>

class MyCPPSyntaxHighlighter : public QSyntaxHighlighter
{
public:
    MyCPPSyntaxHighlighter(QTextDocument *parent);
    void highlightBlock(const QString &text);
    void highlightWord(int i,QString text, QString word, QColor color);
};

#endif // MYCPPSYNTAXHIGHLIGHTER_H
