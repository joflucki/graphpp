#include "displayableedge.h"

DisplayableEdge::DisplayableEdge(QString name,
                                 DisplayableVertex* source,
                                 DisplayableVertex* target,
                                 QColor textColor,
                                 QColor borderColor)
{
    this->name = name;
    this->source = source;
    this->target = target;
    this->textColor = textColor;
    this->borderColor = borderColor;
}

// GETTERS
QString DisplayableEdge::getName()
{
    return this->name;
}
QColor DisplayableEdge::getTextColor()
{
    return this->textColor;
}
QColor DisplayableEdge::getBorderColor()
{
    return this->borderColor;
}


// SETTERS
void DisplayableEdge::setName(QString name)
{
    this->name = name;
}
void DisplayableEdge::setTextColor(QColor color)
{
    this->textColor = color;
}
void DisplayableEdge::setBorderColor(QColor color)
{
    this->borderColor = color;
}
