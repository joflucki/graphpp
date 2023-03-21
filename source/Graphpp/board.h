#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QtWidgets>
#include "displayablevertex.h"
#include "displayableedge.h"

enum Tool
{
    SELECTOR,
    CREATE_VERTEX,
    CREATE_EDGE,
    ERASER,
    HAND,
    CYCLE_GRAPH,
    COMPLETE_GRAPH,
    BIPARTITE_GRAPH
};

class Board : public QWidget
{
public:
    Board(QWidget *parent = nullptr);
    virtual ~Board();
    void setSelectedTool(Tool selectedTool);

private:
    QList<DisplayableVertex*> listVertex;
    QList<DisplayableEdge*> listEdge;
    int vertexRadius = 5;

    Tool selectedTool = Tool::SELECTOR;
    bool hitVertex(QPointF position, DisplayableVertex*& hittedVertex);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void unselectVertices();
    void clickCreateVertex(QMouseEvent *event);
    void clickSelector(QMouseEvent *event);
    void clickCreateEdge(QMouseEvent *event);
};

#endif // BOARD_H
