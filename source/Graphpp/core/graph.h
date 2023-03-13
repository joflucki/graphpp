#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include "edge.h"
#include "vertex.h"


class Graph
{
public:
    Graph();
    ~Graph();

    //getters
    std::list<Vertex> getVertices();
    std::list<Edge> getEdges();

    //modifiers
    void addVertex(Vertex *vertex);
    void addEdge(Vertex *source, Vertex *target, int weight = 1);
    void removeVertex(Vertex *vertex);
    void removeEdge(Edge *edge);

    //analysis
    bool isEulerian();
    bool isHamiltonian();
    bool isConnected();
    bool isStronglyConnected();
    bool isOriented();
    bool isWeighted();
    bool isPlanar();
    int getChromaticNumber();
    int getNbFaces();
    int getNbEdges();
    int getNbVertices();
    int getVertexDegree(Vertex *vertex);

protected:
    std::list<Vertex> vertices;
    std::list<Edge> edges;
};

#endif // GRAPH_H
