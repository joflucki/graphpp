#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <unordered_map>
#include "edge.h"
// TODO delete me
#include <qDebug>


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

template <typename T> Graph<T>::Graph()
{
    this->adjacencyList = new std::unordered_map<T*, std::list<Edge<T>>>;
}

template <typename T> void Graph<T>::addVertex(T *vertex)
{
    if (this->adjacencyList.find(vertex) == this->adjacencyList.end())
    {
        //vertex does not exist in map
        std::pair<T*, std::list<Edge<T>>> newAdjacencyList = new std::pair<T*, std::list<Edge<T>>> (vertex, new std::list<Edge<T>>);
        this->adjacencyList.insert(newAdjacencyList);
    }
    else
    {
        qDebug() << "ERROR : cannot add vertex : vertex already in map" << Qt::endl; //TODO throw error
    }
}

template <typename T> void Graph<T>::addEdge(T *source, T *target, int weight)
{
    if(this->adjacencyList.find(source) != this->adjacencyList.end())
    {
        if(this->adjacencyList.find(target) != this->adjacencyList.end())
        {
            std::list<Edge<T>> sourceAdjacencyList = this->adjacencyList[source];
            Edge<T> newEdge = new Edge(target, weight);
            sourceAdjacencyList.push_back(newEdge);
            this->adjacencyList[source] = sourceAdjacencyList;
        }
        else
        {
            qDebug() << "ERROR : cannot add edge : target does not exist" << Qt::endl; //TODO throw error
        }
    }
    else
    {
        qDebug() << "ERROR : cannot add edge : source does not exist" << Qt::endl; //TODO throw error
    }
}

template <typename T> void Graph<T>::addDoubleEdge(T *vertex1, T *vertex2, int weight)
{
    this->addEdge(vertex1, vertex2, weight);
    this->addEdge(vertex2, vertex1, weight);
}

template <typename T> void Graph<T>::removeVertex(T *vertex)
{

}

template <typename T> void Graph<T>::removeEdge(Edge<T> *edge)
{

}

#endif // GRAPH_H
