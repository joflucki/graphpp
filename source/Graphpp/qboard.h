#ifndef QBOARD_H
#define QBOARD_H

#include <QWidget>
#include <QtWidgets>
#include "qvertex.h"
#include "vertexdockwidget.h"
#include "graph.h"

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
    QBoard(VertexDockWidget *vertexDockWidget, QWidget *parent = nullptr);
    virtual ~QBoard();
    void setSelectedTool(Tool selectedTool);
    Graph<QVertex> *graph;

private:
    const int vertexRadius = 5;
    Tool selectedTool = Tool::SELECTOR;

    // used to update dockWidget when a vertex is selected
    VertexDockWidget *vertexDockWidget;

    // useful methods
    void unselectVertices();
    bool hitVertex(QPointF position, QVertex*& hittedVertex);
    bool hitSegment(QPointF hitPoint, QPointF p1, QPointF p2, double margin);

    // click behaviours methods
    void clickCreateVertex(QMouseEvent *event);
    void clickSelector(QMouseEvent *event);
    void clickCreateEdge(QMouseEvent *event);
    void clickCycleGraph(QMouseEvent *event);
    void clickCompleteGraph(QMouseEvent *event);
    void clickBipartiteGraph(QMouseEvent *event);

    // move behaviours methods
    void moveEraser(QMouseEvent *event);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

};

#endif // QBOARD_H
