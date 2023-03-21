#ifndef DISPLAYABLEEDGE_H
#define DISPLAYABLEEDGE_H
#include <QString>
#include <QColor>
#include "displayablevertex.h"

class DisplayableEdge
{
public:
    DisplayableEdge(QString name,
                    DisplayableVertex* source,
                    DisplayableVertex* target,
                    QColor textColor = Qt::black,
                    QColor borderColor = Qt::black);

    // only for dev
    DisplayableVertex* source;
    DisplayableVertex* target;

    //getters
    QString getName();
    QColor getTextColor();
    QColor getBorderColor();


    //setters
    void setName(QString name);
    void setTextColor(QColor color);
    void setBorderColor(QColor color);

private:
    QString name = "";
    QColor textColor;
    QColor borderColor;
};

#endif // DISPLAYABLEEDGE_H
