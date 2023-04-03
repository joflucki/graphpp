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
    std::unordered_map<T*, std::list<Edge<T>*>> adjacencyList;

    //modifiers
    void addVertex(T *vertex); //OK, à tester
    void addEdge(T *source, T *target, int weight = 1); //OK, à tester
    void addDoubleEdge(T *vertex1, T *vertex2, int weight = 1); //OK, à tester
    void removeVertex(T *vertex); //A tester
    void removeEdge(Edge<T> *edge); //A tester

    //analysis
    bool isEulerian();
    bool isHamiltonian();
    bool isConnected();
    bool isStronglyConnected();
    bool isOriented(); //OK, à tester
    bool isWeighted(); //OK, à tester
    bool isPlanar();
    int getChromaticNumber();
    int getNbFaces();
    int getNbEdges(); //OK, à tester
    int getNbVertices(); //OK, à tester
    int getVertexIndegree(T *vertex); //OK, à tester
    int getVertexOutdegree(T *vertex); //OK, à tester
};

template <typename T> Graph<T>::Graph()
{
    this->adjacencyList = std::unordered_map<T*, std::list<Edge<T>*>>();
}

template <typename T> void Graph<T>::addVertex(T *vertex)
{
    if (this->adjacencyList.find(vertex) == this->adjacencyList.end())
    {
        //vertex does not exist in map
        //std::pair<T*, std::list<Edge<T>>> newAdjacencyList = new std::pair<T*, std::list<Edge<T>>> (vertex, new std::list<Edge<T>>);
        //this->adjacencyList.insert(newAdjacencyList);

        this->adjacencyList.insert(std::make_pair(vertex, std::list<Edge<T>*>()));
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
            std::list<Edge<T>*> sourceAdjacencyList = this->adjacencyList[source];
            Edge<T> *newEdge = new Edge(*target, weight);
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
    if(this->adjacencyList.find(vertex) != this->adjacencyList.end())
    {
        for (auto const& edge : this->adjacencyList[vertex])
        {
            delete edge;
        }
        for (auto const& otherVertex : this->adjacencyList)
        {
            for (auto const& edgeFromOtherVertex : this->adjacencyList[otherVertex.first])
            {
                if(edgeFromOtherVertex->getTarget() == vertex)
                {
                    this->adjacencyList[otherVertex.first].remove(edgeFromOtherVertex);
                    delete edgeFromOtherVertex;
                }
            }
        }

        this->adjacencyList.extract(vertex);
    }
}

template <typename T> void Graph<T>::removeEdge(Edge<T> *edge)
{
    for (auto const& vertex : this->adjacencyList)
    {
        for (auto const& edge1 : this->adjacencyList[vertex])
        {
            if(edge1 == edge)
            {
                this->adjacencyList[vertex].erase(edge1);
                delete edge1;
            }
        }
    }
}

template <typename T> bool Graph<T>::isEulerian()
{
    return false;
}

template <typename T> bool Graph<T>::isHamiltonian()
{
    return false;
}

template <typename T> bool Graph<T>::isConnected()
{
    return false;
}

template <typename T> bool Graph<T>::isStronglyConnected()
{
    return false;
}

template <typename T> bool Graph<T>::isOriented()
{
    bool isOriented = false;
    for (auto const& vertex1 : this->adjacencyList)
    {
        for (auto const& edge1 : this->adjacencyList[vertex1])
        {
            bool hasOppositeEdge = false;
            for (auto const& edge2 : this->adjacencyList[edge1->getTarget()])
            {
                if(edge2->getTarget() == vertex1)
                {
                    hasOppositeEdge = true;
                }
            }
            if(!hasOppositeEdge)
            {
                isOriented = true;
            }
        }
    }
    return isOriented;
}

template <typename T> bool Graph<T>::isWeighted()
{
    bool isWeighted = false;
    for (auto const& vertex : this->adjacencyList)
    {
        for (auto const& edge : this->adjacencyList[vertex])
        {
            if(edge->getWeight() != 1)
            {
                isWeighted = true;
            }
        }
    }
    return isWeighted;
}

template <typename T> bool Graph<T>::isPlanar()
{
    return false;
}

template <typename T> int Graph<T>::getChromaticNumber()
{
    return 0;
}

template <typename T> int Graph<T>::getNbFaces()
{
    return 0;
}

template <typename T> int Graph<T>::getNbEdges()
{
    int sizeSum = 0;
    for (auto const& vertex : this->adjacencyList)
    {
        sizeSum += this->adjacencyList[vertex].size();
    }
    return sizeSum;
}

template <typename T> int Graph<T>::getNbVertices()
{
    return this->adjacencyList.size();
}

template <typename T> int Graph<T>::getVertexIndegree(T *vertex)
{
    int indegree = 0;
    if(this->adjacencyList.find(vertex) != this->adjacencyList.end())
    {
        for (auto const& otherVertex : this->adjacencyList)
        {
            for (auto const& edgeFromOtherVertex : this->adjacencyList[otherVertex])
            {
                if(edgeFromOtherVertex->getTarget() == vertex)
                {
                    indegree++;
                }
            }
        }
    }
    return indegree;
}

template <typename T> int Graph<T>::getVertexOutdegree(T *vertex)
{
    if(this->adjacencyList.find(vertex) != this->adjacencyList.end())
    {
        return this->adjacencyList[vertex].size();
    }
}

#endif // GRAPH_H
