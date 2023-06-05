#ifndef GRAPHDOCKWIDGET_H
#define GRAPHDOCKWIDGET_H

#include <QtWidgets>
#include "graph.h"

class QVertex;

/// @brief QWidget displaying all informations about graph analysis. Like eulerian, oriented,...
/// @author Plumey Simon
/// @date spring 2023
class GraphDockWidget : public QWidget
{
private:
    Graph<QVertex>* selectedGraph = nullptr;

    QLabel *eulerian, *hamiltonian, *connected, *stronglyConnected, *oriented,
    *weighted, *chromaticNumber, *nbEdges, *nbVertices;
    void updateLabels();

public:
    void setSelectedGraph(Graph<QVertex> *graph);
    GraphDockWidget(QWidget *parent);
};

#endif // GRAPHDOCKWIDGET_H
