#include <QColorDialog>
#include "selectcolorbutton.h"

SelectColorButton::SelectColorButton( QWidget* parent )
    : QPushButton(parent)
{
    connect( this, &QPushButton::clicked, this, &SelectColorButton::changeColor);
}

void SelectColorButton::updateColor()
{
    setStyleSheet( "background-color: " + color.name() );
}

void SelectColorButton::changeColor()
{
    QColor newColor = QColorDialog::getColor(color, parentWidget());
    if ( newColor != color )
    {
        setColor( newColor );
        emit colorChanged();
    }
}

void SelectColorButton::setColor( const QColor& color )
{
    this->color = color;
    updateColor();
}

const QColor& SelectColorButton::getColor() const
{
    return color;
}
