#ifndef QVERTEX_H
#define QVERTEX_H
#include <QString>
#include <QColor>
#include <QPointF>

class QVertex
{
public:
    QVertex(QString name,
                      QPointF position,
                      QColor textColor = Qt::black,
                      QColor backgroundColor = Qt::black,
                      QColor borderColor = Qt::black);

    //getters
    QString getName();
    QPointF getPosition();
    QColor getTextColor();
    QColor getBackgroundColor();
    QColor getBorderColor();
    bool isSelected();

    //setters
    void setName(QString name);
    void setPosition(QPointF position);
    void setTextColor(QColor color);
    void setBackgroundColor(QColor color);
    void setBorderColor(QColor color);
    void setSelected(bool selected);

private:
    QString name = "";
    QPointF position;
    QColor textColor;
    QColor backgroundColor;
    QColor borderColor;
    bool selected = false;
};

#endif // QVERTEX_H
