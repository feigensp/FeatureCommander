#include "mycppsyntaxhighlighter.h"

MyCPPSyntaxHighlighter::MyCPPSyntaxHighlighter(QTextDocument *parent ): QSyntaxHighlighter(parent)
{
    setDocument(parent);

}
void MyCPPSyntaxHighlighter::highlightBlock(const QString &text){
    //Comments
    enum { NormalState = -1, InsideCStyleComment, InsideQuote };
    int state = previousBlockState();
    int start = 0;
    int startQuote = 0;
    QColor commentColor = Qt::darkGreen;//QColor (100,170,100,255);
    QColor commandColor = Qt::darkBlue;
    QColor dataTypeColor = Qt::darkMagenta;
    QColor includeColor = Qt::darkRed;
    for (int i = 0; i < text.length(); ++i) {

        if (state == InsideCStyleComment) {
            if (text.mid(i, 2) == "*/") {
                state = NormalState;
                setFormat(start, i - start + 2, commentColor);
            }
        } else {

            if (text.at(i)=='"' && state == InsideQuote){
                setFormat(startQuote, i - startQuote + 1, commentColor);
                state = NormalState;
            }
            if (text.mid(i, 2) == "//") {
                setFormat(i, text.length() - i, commentColor);
                break;
            } else if (text.mid(i, 2) == "/*") {
                start = i;
                state = InsideCStyleComment;
            }
            if (text.at(i)=='"' && state == NormalState){
                startQuote = i;
                state = InsideQuote;
            }

            highlightWord(i,text,"if",commandColor);
            highlightWord(i,text,"for",commandColor);
            highlightWord(i,text,"while",commandColor);
            highlightWord(i,text,"do",commandColor);
            highlightWord(i,text,"until",commandColor);
            highlightWord(i,text,"double",dataTypeColor);
            highlightWord(i,text,"float",dataTypeColor);
            highlightWord(i,text,"int",dataTypeColor);
            highlightWord(i,text,"long",dataTypeColor);
            highlightWord(i,text,"unsigned",dataTypeColor);
            highlightWord(i,text,"void",dataTypeColor);
            highlightWord(i,text,"char",dataTypeColor);
//            highlightWord(i,text,"#include",includeColor);
//            highlightWord(i,text,"#ifdef",includeColor);
//            highlightWord(i,text,"#ifndef",includeColor);
//            highlightWord(i,text,"#define",includeColor);
//            highlightWord(i,text,"#endif",includeColor);
//            highlightWord(i,text,"#else",includeColor);
//            highlightWord(i,text,"#error",includeColor);
//            highlightWord(i,text,"#if",includeColor);
            if (text.at(i)=='#'){
                int end = text.indexOf(QRegExp("[\\W\\n\\r]"),i+1);
                setFormat(i, end - i, includeColor);
            }


        }
    }
    if (state == InsideCStyleComment)
        setFormat(start, text.length() - start, commentColor);

    setCurrentBlockState(state);
}
void MyCPPSyntaxHighlighter::highlightWord(int i,QString text, QString word, QColor color){

    if (text.mid(i, word.length()+2).contains(QRegExp("\\W" + word + "\\W"))){
        setFormat(i+1, word.length(), color);
    }
    if (i == 0 && text.mid(i, word.length()+1).contains(QRegExp(word + "\\W"))){
        setFormat(i, word.length(), color);
    }
    if (text.length()==word.length() && text.contains(word))
        setFormat(0, word.length(), color);

}


