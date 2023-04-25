#ifndef VERTEXDOCKWIDGET_H
#define VERTEXDOCKWIDGET_H

#include <QtWidgets>
#include "qvertex.h"
#include "selectcolorbutton.h"

class VertexDockWidget: public QWidget
{
    Q_OBJECT
private:
    QVertex* selectedVertex = nullptr;

    QLabel *labelName, *labelPositionX, *labelPositionY, *labelTextColor, *labelBackgroundColor, *labelBorderColor;
    QLineEdit *name;
    QSpinBox *positionX, *positionY;
    SelectColorButton *textColorBtn, *backgroundColorBtn, *borderColorBtn;
    void updateFields();
    void updateVertex();

public:
    void setSelectedVertex(QVertex* vertex);
    VertexDockWidget(QWidget *parent);

signals:
    void vertexUpdated();
};

#endif // VERTEXDOCKWIDGET_H
