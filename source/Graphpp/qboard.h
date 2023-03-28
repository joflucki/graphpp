#ifndef QBOARD_H
#define QBOARD_H

#include <QWidget>
#include <QtWidgets>
#include "qvertex.h"
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
    QBoard(QWidget *parent = nullptr);
    virtual ~QBoard();
    void setSelectedTool(Tool selectedTool);

private:
    Graph<QVertex> *graph;
    const int vertexRadius = 5;
    Tool selectedTool = Tool::SELECTOR;

    // useful methods
    void unselectVertices();
    bool hitVertex(QPointF position, QVertex*& hittedVertex);

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
