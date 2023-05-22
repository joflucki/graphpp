#ifndef VERTEXDOCKWIDGET_H
#define VERTEXDOCKWIDGET_H

#include <QtWidgets>
#include "qvertex.h"
#include "selectcolorbutton.h"
#include "graph.h"

class VertexDockWidget: public QWidget
{
    Q_OBJECT
private:
    QVertex* selectedVertex = nullptr;
    Graph<QVertex>* selectedGraph = nullptr;

    QLabel *labelName, *labelPositionX, *labelPositionY, *labelTextColor,
    *labelBackgroundColor, *labelBorderColor, *labelInDegree, *labelOutDegree;
    QLabel *inDegree, *outDegree;
    QLineEdit *name;
    QSpinBox *positionX, *positionY;
    SelectColorButton *textColorBtn, *backgroundColorBtn, *borderColorBtn;
    void updateFields();
    void updateVertex();

public:
    void setSelectedVertex(QVertex* vertex);
    void setSelectedGraph(Graph<QVertex> *graph);
    VertexDockWidget(QWidget *parent);

signals:
    void vertexUpdated();
};

#endif // VERTEXDOCKWIDGET_H
