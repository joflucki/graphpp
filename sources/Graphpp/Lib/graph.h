#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <list>
#include <unordered_map>
#include <cmath>
#include <stack>
#include <algorithm>
#include "edge.h"

template <typename T>
class Graph
{
public:
    Graph();
    ~Graph();

    // attributes
    std::unordered_map<T *, std::list<Edge<T> *>> adjacencyList;

    // modifiers
    void addVertex(T *vertex);
    void addEdge(T *source, T *target, int weight = 1);
    void addDoubleEdge(T *vertex1, T *vertex2, int weight = 1);
    void removeVertex(T *vertex);
    void removeEdge(Edge<T> *edge);

    // analysis
    bool isEulerian();
    bool isHamiltonian();
    bool isConnected();
    bool isStronglyConnected();
    bool isOriented(); // Not
    bool isWeighted(); // OK
    bool isPlanar();
    int getChromaticNumber();
    int getNbFaces();
    int getNbEdges();                  // OK
    int getNbVertices();               // OK
    int getVertexIndegree(T *vertex);  // OK, à tester
    int getVertexOutdegree(T *vertex); // OK, à tester
};

/// @brief Initializes a new graph
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T>
Graph<T>::Graph()
{
    this->adjacencyList = std::unordered_map<T *, std::list<Edge<T> *>>();
}

/// @brief Adds a vertex to the graph
/// @param A vertex
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T>
void Graph<T>::addVertex(T *vertex)
{
    if (this->adjacencyList.find(vertex) == this->adjacencyList.end())
    {
        this->adjacencyList.insert(std::make_pair(vertex, std::list<Edge<T> *>()));
    }
    else
    {
        // TODO error
        // qDebug() << "ERROR : cannot add vertex : vertex already in map" << Qt::endl; //TODO throw error
    }
}

/// @brief Adds an edge between two vertices
/// @param Source vertex
/// @param Target vertex
/// @param The weight of the edge
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T>
void Graph<T>::addEdge(T *source, T *target, int weight)
{
    if (this->adjacencyList.find(source) != this->adjacencyList.end())
    {
        if (this->adjacencyList.find(target) != this->adjacencyList.end())
        {
            Edge<T> *newEdge = new Edge(target, weight);
            this->adjacencyList[source].push_back(newEdge);
        }
        else
        {
            // qDebug() << "ERROR : cannot add edge : target does not exist" << Qt::endl; //TODO throw error
        }
    }
    else
    {
        // qDebug() << "ERROR : cannot add edge : source does not exist" << Qt::endl; //TODO throw error
    }
}

/// @brief Adds two edges in opposite directions between two vertices
/// @param A vertex
/// @param Another vertex
/// @param The weight of the edge
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T>
void Graph<T>::addDoubleEdge(T *vertex1, T *vertex2, int weight)
{
    this->addEdge(vertex1, vertex2, weight);
    this->addEdge(vertex2, vertex1, weight);
}

/// @brief Removes a vertex and its linked edges from the graph
/// @param A vertex
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T>
void Graph<T>::removeVertex(T *vertex)
{
    // Remove all edges related to the vertex
    for (auto &vertexPair : this->adjacencyList)
    {
        auto &edgeList = vertexPair.second;
        auto edgeIt = edgeList.begin();
        while (edgeIt != edgeList.end())
        {
            if ((*edgeIt)->getTarget() == vertex)
            {
                delete *edgeIt;
                edgeIt = edgeList.erase(edgeIt);
            }
            else
            {
                ++edgeIt;
            }
        }
    }

    // Remove the vertex from the map
    adjacencyList.erase(vertex);
    delete vertex;
}

/// @brief Removes an edge from the graph
/// @param An edge
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T>
void Graph<T>::removeEdge(Edge<T> *edge)
{
    for (auto &vertex : this->adjacencyList)
    {
        auto it = vertex.second.begin();
        while (it != vertex.second.end())
        {
            if (*it == edge)
            {
                it = vertex.second.erase(it);
                delete edge;
                edge = nullptr;
            }
            else
            {
                ++it;
            }
        }
    }
}

/// @brief Returns whether the graph is eulerian or not
/// @author Damien Tschan
/// @date 08.05.2023
template <typename T>
bool Graph<T>::isEulerian()
{
    bool eulerian = true;
    for (auto &vertex : this->adjacencyList)
    {
        if(this->getVertexIndegree(vertex.first) % 2 != 0 || this->getVertexOutdegree(vertex.first) % 2 != 0)
        {
            return false;
        }
    }
    return true && this->isConnected();
}

/// @brief Returns whether the graph is hamiltonian or not
/// @author TODO
/// @date
template <typename T>
bool Graph<T>::isHamiltonian()
{
    return false;
}

/// @brief Returns whether the graph is connected or not
/// @author Damien Tschan
/// @date 08.05.2023
template <typename T>
bool Graph<T>::isConnected()
{
    if(this->adjacencyList.size() >= 1)
    {
        T *vertex = this->adjacencyList.begin()->first;

        std::list<T*> visited;
        std::list<T*> toVisit;

        toVisit.push_back(vertex);

        while (!toVisit.empty())
        {
            T *currentVertex = *toVisit.begin();
            visited.push_back(currentVertex);

            for (auto &adjacentVertex : this->adjacencyList[currentVertex])
            {
                bool notVisited = std::find(visited.begin(), visited.end(), adjacentVertex->getTarget()) == visited.end();
                bool notEncountered = std::find(toVisit.begin(), toVisit.end(), adjacentVertex->getTarget()) == toVisit.end();
                if(notVisited && notEncountered)
                {
                     toVisit.push_back(adjacentVertex->getTarget());
                }
            }

            toVisit.remove(currentVertex);
        }

        return visited.size() == this->adjacencyList.size();
    }
    else
    {
        return true;
    }
}

/// @brief Returns whether the graph is strongly connected or not
/// @author Damien Tschan
/// @date 24.04.2023
template <typename T>
bool Graph<T>::isStronglyConnected()
{
    return this->getNbVertices() * log2(this->getNbVertices()) < this->getNbEdges();
}

/// @brief Returns whether the graph is oriented or not
/// @author Damien Tschan
/// @date 24.04.2023
///
/// As oriented graphs are not supported by this version of the app, isOriented() will always return false.
template <typename T>
bool Graph<T>::isOriented()
{
    /*std::list<std::pair<bool,std::pair<T*,T*>>> edgeList;
    for (auto & vertex : this->adjacencyList)
    {
        for(auto const& edge : vertex.second)
        {
            edgeList.push_back(std::make_pair(false, std::make_pair(vertex.first, edge->getTarget())));
        }
    }
    for (auto & edge1 : edgeList)
    {
        if(edge1.first == false)
        {
            for (auto & edge2 : edgeList)
            {
                if(edge2.first == false)
                {
                    if(edge1.second.first == edge2.second.second && edge2.second.first == edge1.second.second)
                    {
                        edge1.first = true;
                        edge2.first = true;
                    }
                }
            }
        }
    }
    bool oriented = false;
    for (auto const& edge : edgeList)
    {
        if(edge.first == false)
        {
            oriented = true;
        }
    }
    return oriented;*/
    return false;
}

/// @brief Returns whether the graph is weighted or not
/// @author Damien Tschan
/// @date 24.04.2023
template <typename T>
bool Graph<T>::isWeighted()
{
    bool isWeighted = false;
    for (auto const& vertex : this->adjacencyList)
    {
        for (auto const& edge : vertex.second)
        {
            if(edge->getWeight() != 1)
            {
                isWeighted = true;
            }
        }
    }
    return isWeighted;
    return false;
}

/// @brief Returns whether the graph is planar or not
/// @author TODO
/// @date
template <typename T>
bool Graph<T>::isPlanar()
{
    return false;
}

/// @brief Returns an estimation of the chromatic number of the graph as an integer
/// @author Jonas Flückiger
/// @date 12.05.2023
///
/// This method uses the greedy algorithm, where each vertex is colored one after the other
/// with the first possible color. This method can perform well depending on the order in which
/// the vertices are colored, and depends on the shape of the graph. In this implementation,
/// vertices are colored in order of descending degree.
template <typename T>
int Graph<T>::getChromaticNumber()
{


    // SORTING THE VERTICES
    // Declare vector of pairs
    std::vector<std::pair<T *, std::list<Edge<T> *>> > verticesOrderedByDegree;

    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : this->adjacencyList) {
        verticesOrderedByDegree.push_back(it);
    }

    // Sort using comparator function
    sort(verticesOrderedByDegree.begin(), verticesOrderedByDegree.end(), [this](std::pair<T *, std::list<Edge<T> *>> a, std::pair<T *, std::list<Edge<T> *>> b) {
        int aDegree = this->getVertexIndegree(a.first) + this->getVertexIndegree(a.first);
        int bDegree = this->getVertexIndegree(b.first) + this->getVertexIndegree(b.first);
        return aDegree < bDegree;
    });


    // COLORING THE VERTICES
    // A map of pairs vertex <-> color
    // Colors are simply represented by an integer
    std::unordered_map<T*, int> colorMap;
    // Function to check if a vertex can be assigned a given color
    auto canAssignColor = [&](T* vertex, int color) {
        for (auto& adjacentVertex : this->adjacencyList[vertex]) {
            if (colorMap[adjacentVertex->getTarget()] == color) {
                return false;
            }
        }
        return true;
    };

    int numVertices = this->getNbVertices();
    int chromaticNumber = 0;

    // Try to assign colors from 1 to max. number of colors
    for (auto const& vertexStruct : verticesOrderedByDegree)
    {
        int colorNum = 1;
        while(colorNum <= numVertices){
            if(canAssignColor(vertexStruct.first, colorNum)){
                // Assign a color
                colorMap[vertexStruct.first] = colorNum;
                chromaticNumber = colorNum > chromaticNumber ? colorNum : chromaticNumber;
                break;
            }else{
                // Try with the next color
                colorNum++;
            }
        }
    }

    return chromaticNumber;
}

/// @brief Returns the amount of faces in the graph as an integer
/// @author TODO
/// @date
template <typename T>
int Graph<T>::getNbFaces()
{
    return 0;
}

/// @brief Returns the amount of edges in the graph as an integer
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T>
int Graph<T>::getNbEdges()
{
    int sizeSum = 0;
    for (auto const &vertex : this->adjacencyList)
    {
        sizeSum += vertex.second.size();
    }
    if (!this->isOriented())
    {
        sizeSum /= 2;
    }
    return sizeSum;
}

/// @brief Returns the amount of vertices in the graph as an integer
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T>
int Graph<T>::getNbVertices()
{
    return this->adjacencyList.size();
}

/// @brief Returns the indegree of a vertex
/// @param A vertex
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T>
int Graph<T>::getVertexIndegree(T *vertex)
{
    int indegree = 0;
    if (this->adjacencyList.find(vertex) != this->adjacencyList.end())
    {
        for (auto const &otherVertex : this->adjacencyList)
        {
            for (auto const &edgeFromOtherVertex : this->adjacencyList[otherVertex.first])
            {
                if (edgeFromOtherVertex->getTarget() == vertex)
                {
                    indegree++;
                }
            }
        }
    }
    return indegree;
}

/// @brief Returns the outdegree of a vertex
/// @param A vertex
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T>
int Graph<T>::getVertexOutdegree(T *vertex)
{
    if (this->adjacencyList.find(vertex) != this->adjacencyList.end())
    {
        return this->adjacencyList[vertex].size();
    }
}

#endif // GRAPH_H
