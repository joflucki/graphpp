#ifndef GRAPHDOCKWIDGET_H
#define GRAPHDOCKWIDGET_H

#include <QtWidgets>
#include "graph.h"

class QVertex;

class GraphDockWidget : public QWidget
{
private:
    Graph<QVertex>* selectedGraph = nullptr;

    QLabel *eulerian, *hamiltonian, *connected, *stronglyConnected, *oriented,
    *weighted, *planar, *chromaticNumber, *nbFaces, *nbEdges, *nbVertices;
    void updateLabels();

public:
    void setSelectedGraph(Graph<QVertex> *graph);
    GraphDockWidget(QWidget *parent);
};

#endif // GRAPHDOCKWIDGET_H
