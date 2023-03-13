#ifndef DISPLAYABLEEDGE_H
#define DISPLAYABLEEDGE_H
#include <QString>
#include <QColor>

class DisplayableEdge
{
public:
    DisplayableEdge();

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
