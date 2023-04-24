#ifndef SELECTCOLORBUTTON_H
#define SELECTCOLORBUTTON_H

#include <QPushButton>
#include <QColor>
/**
 * @brief A simple button to select color
 * This code comes from here: https://stackoverflow.com/questions/18257281/qt-color-picker-widget
 * @author Alexis Wilke
 */
class SelectColorButton : public QPushButton
{
    Q_OBJECT
public:
    SelectColorButton( QWidget* parent );

    void setColor( const QColor& color );
    const QColor& getColor() const;

public slots:
    void updateColor();
    void changeColor();

signals:
    void colorChanged();

private:
    QColor color;
};

#endif // SELECTCOLORBUTTON_H
