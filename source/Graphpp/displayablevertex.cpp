#include "displayablevertex.h"

DisplayableVertex::DisplayableVertex(QString name,
                                     QPointF position,
                                     QColor textColor,
                                     QColor backgroundColor,
                                     QColor borderColor)
{
    this->name = name;
    this->position = position;
    this->textColor = textColor;
    this->backgroundColor = backgroundColor;
    this->borderColor = borderColor;
}

// GETTERS
QString DisplayableVertex::getName()
{
    return this->name;
}
QPointF DisplayableVertex::getPosition()
{
    return this->position;
}
QColor DisplayableVertex::getTextColor()
{
    return this->textColor;
}
QColor DisplayableVertex::getBackgroundColor()
{
    return this->backgroundColor;
}
QColor DisplayableVertex::getBorderColor()
{
    return this->borderColor;
}
bool DisplayableVertex::isSelected()
{
    return this->selected;
}


// SETTERS
void DisplayableVertex::setName(QString name)
{
    this->name = name;
}
void DisplayableVertex::setPosition(QPointF position)
{
    this->position = position;
}
void DisplayableVertex::setTextColor(QColor color)
{
    this->textColor = color;
}
void DisplayableVertex::setBackgroundColor(QColor color)
{
    this->backgroundColor = color;
}
void DisplayableVertex::setBorderColor(QColor color)
{
    this->borderColor = color;
}
void DisplayableVertex::setSelected(bool selected)
{
    this->selected = selected;
}
