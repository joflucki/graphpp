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
    void addEdge(Vertex *source, Vertex *target, int weight = 1);
    void addVertex();
    int getDegree(Vertex* vertex);
    bool isStronglyConnected();
    bool isConnected();
    bool isOriented();
    bool isWeighted();
    int getNbVertices();
    int getNbEdges();
    int getChromaticNumber();
    bool isPlanar();
    int getNbFaces();




protected:
    std::list<Vertex> vertices;
    std::list<Edge> edges;


};

#endif // GRAPH_H
