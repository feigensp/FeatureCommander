#ifndef LOADBUTTON_H
#define LOADBUTTON_H

#include <QToolButton>
#include <QFile>
#include <QDomDocument>
#include "colormanager.h"

class LoadButton : public QToolButton
{
Q_OBJECT
public:
    explicit LoadButton(QWidget *parent = 0,ColorManager *manager = 0);
    void setFileName(QString text);
signals:

public slots:
    void testHide();
    void load();

private:
    ColorManager *colorManager;
    QString fileName;
};

#endif // LOADBUTTON_H
