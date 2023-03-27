#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <unordered_map>
#include "edge.h"


template <typename T> class Graph
{
public:
    Graph();
    ~Graph();

    //attributes
    std::unordered_map<T*, std::list<Edge<T>>> adjacencyList;

    //modifiers
    void addVertex(T *vertex);
    void addEdge(T *source, T *target, int weight = 1);
    void addDoubleEdge(T *vertex1, T *vertex2, int weight = 1);
    void removeVertex(T *vertex);
    void removeEdge(Edge<T> *edge);

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
    int getVertexDegree(T *vertex);
};

#endif // GRAPH_H
