#ifndef COLOR_H
#define COLOR_H

#include <QColor>

class Color
{
public:
    QColor color;
    bool isChild;


    Color(QColor c);
    Color();
    void setAvailable(bool a);
    bool operator==(Color c);
    QColor getColor();
    void setIsChildFeature(bool yesOrNo);
    bool isAvailable();
    void setParentName(QString name);
    QString getParentName();
    bool isCustom();
    void setCustom(bool c);
    bool available;

private:
    QString parent;

    bool custom;

};

#endif // COLOR_H
