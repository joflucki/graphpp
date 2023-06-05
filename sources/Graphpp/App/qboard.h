#ifndef QBOARD_H
#define QBOARD_H

#include <QWidget>
#include <QtWidgets>
#include "qvertex.h"
#include "vertexdockwidget.h"
#include <graph.h>
#include "qmemento.h"

class QCaretaker;

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

/// @brief QBoard is a widget on which we paint the graph. Like a whiteboard.
/// @author Plumey Simon & Jonas Flückiger
/// @date spring 2023
class QBoard : public QWidget
{
public:
    QBoard(VertexDockWidget *vertexDockWidget, QWidget *parent = nullptr);
    virtual ~QBoard();
    void setSelectedTool(Tool selectedTool);
    void exportToPng(QString path);
    void exportToDOT(QString path);
    void saveToFile(QString path);
    void openFile(QString path);
    void highlightMinimumDistanceGraph();
    void highlightMinimumSpanningTree();
    Graph<QVertex> *graph;
    Graph<QVertex>* highlightedGraph;

    // methods for undo/redo function
    QMemento save();
    void restore(QMemento memento);
    QCaretaker* getQCaretaker();

private:
    const int vertexRadius = 5;
    Tool selectedTool = Tool::SELECTOR;
    Edge<QVertex>* selectedEdge;

    QTransform transform; // actual transform matrix

    // used to update dockWidget when a vertex is selected
    VertexDockWidget *vertexDockWidget;

    // used for hand tool
    bool isDragging = false;
    QPointF lastMousePos;

    // undo redo function
    QCaretaker* qCaretaker;

    // useful methods
    void paint(QPainter &painter);
    void unselectVertices();
    bool hitVertex(QPointF position, QVertex *&hittedVertex);
    bool hitSegment(QPointF hitPoint, QPointF p1, QPointF p2, double margin);
    void zoom(qreal scaleFactor, const QPointF &fixedViewPos);
    void translate(const QPointF &delta);
    QPointF convertRelativToTransform(QPointF globalPosition);
    void askEdgeNewWeight(QVertex* source, Edge<QVertex>* edge);


    // click behaviours methods
    void clickCreateVertex(QPointF clickPos);
    void clickSelector(QPointF clickPos);
    void clickCreateEdge(QPointF clickPos);
    void clickCycleGraph(QPointF clickPos);
    void clickCompleteGraph(QPointF clickPos);
    void clickBipartiteGraph(QPointF clickPos);
    void createRoundedVertices(QVertex *arrayVertices[], int nbOfVertices, double radius, QPointF center);
    void createLineOfVertices(QVertex *arrayVertices[], int nbOfVertices, int width, int offsetY, QPointF center);

    // move behaviours methods
    void moveEraser(QPointF clickPos);
    void moveHand(QPointF clickPos);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
};

#endif // QBOARD_H
