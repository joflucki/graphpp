#ifndef QBOARD_H
#define QBOARD_H

#include <QWidget>
#include <QtWidgets>
#include "qvertex.h"

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

class QBoard : public QWidget
{
public:
    QBoard(QWidget *parent = nullptr);
    virtual ~QBoard();
    void setSelectedTool(Tool selectedTool);

private:
    Graph<QVertex> graph;
    QList<QVertex*> listVertex;

    int vertexRadius = 5;
    Tool selectedTool = Tool::SELECTOR;
    bool hitVertex(QPointF position, QVertex*& hittedVertex);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void unselectVertices();
    void clickCreateVertex(QMouseEvent *event);
    void clickSelector(QMouseEvent *event);
    void clickCreateEdge(QMouseEvent *event);

    void moveEraser(QMouseEvent *event);
};

#endif // QBOARD_H
