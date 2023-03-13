#ifndef DISPLAYABLEVERTEX_H
#define DISPLAYABLEVERTEX_H
#include <QString>
#include <QColor>
#include <QPointF>

class DisplayableVertex
{
public:
    DisplayableVertex();

    //getters
    QString getName();
    QPointF getPosition();
    QColor getTextColor();
    QColor getBackgroundColor();
    QColor getBorderColor();

    //setters
    void setName(QString name);
    void setPosition(QPointF position);
    void setTextColor(QColor color);
    void setBackgroundColor(QColor color);
    void setBorderColor(QColor color);

private:
    QString name = "";
    QPointF position;
    QColor textColor;
    QColor backgroundColor;
    QColor borderColor;
};

#endif // DISPLAYABLEVERTEX_H
