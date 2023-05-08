#include "qvertex.h"

/// @brief Constructor of QVertex
/// @param QString: name
/// @param QPointF: position
/// @param QColor: color of text
/// @param QColor: color of background
/// @param QColor: color of border
/// @author Plumey Simon, inspired by Bobur
QVertex::QVertex(QString name,
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
QString QVertex::getName()
{
    return this->name;
}
QPointF QVertex::getPosition()
{
    return this->position;
}
QColor QVertex::getTextColor()
{
    return this->textColor;
}
QColor QVertex::getBackgroundColor()
{
    return this->backgroundColor;
}
QColor QVertex::getBorderColor()
{
    return this->borderColor;
}
bool QVertex::isSelected()
{
    return this->selected;
}


// SETTERS
void QVertex::setName(QString name)
{
    this->name = name;
}
void QVertex::setPosition(QPointF position)
{
    this->position = position;
}
void QVertex::setTextColor(QColor color)
{
    this->textColor = color;
}
void QVertex::setBackgroundColor(QColor color)
{
    this->backgroundColor = color;
}
void QVertex::setBorderColor(QColor color)
{
    this->borderColor = color;
}
void QVertex::setSelected(bool selected)
{
    this->selected = selected;
}
