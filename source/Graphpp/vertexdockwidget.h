#ifndef VERTEXDOCKWIDGET_H
#define VERTEXDOCKWIDGET_H

#include <QtWidgets>
#include "qvertex.h"
#include "selectcolorbutton.h"

class VertexDockWidget: public QWidget
{
private:
    QVertex* selectedVertex = nullptr;

    QLabel *labelName, *labelPositionX, *labelPositionY, *labelTextColor, *labelBackgroundColor, *labelBorderColor;
    QLineEdit *name;
    QSpinBox *positionX, *positionY;
    SelectColorButton *textColorBtn, *backgroundColorBtn, *borderColorBtn;
    void updateVertex();
    void updateFields();

public:
    void setSelectedVertex(QVertex* vertex);
    VertexDockWidget(QWidget *parent);
};

#endif // VERTEXDOCKWIDGET_H
