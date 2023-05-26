#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <stack>
#include <algorithm>
#include <sstream>
#include "edge.h"
#include "queue_element.h"

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
    void addPrebuiltEdge(T *source, Edge<T> *);
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

    // Paths, cycles, trees, subgraphs
    Graph<T> *getMinimumSpanningTree();
    Graph<T> *getMinimumDistanceGraph(T *startingVertex);

    // Serialization
    std::string exportToDOT();

    // Operators
    friend std::ostream &operator<<(std::ostream &os, const Graph<T> &p);

    friend std::istream &operator>>(std::istream &is, Graph<T> &p);
};

/// @brief Initializes a new graph
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T>
Graph<T>::Graph()
{
    this->adjacencyList = std::unordered_map<T *, std::list<Edge<T> *>>();
}

/// @brief Deletes the current graph
/// @author Jonas Flückiger
/// @date 16.05.2023
template <typename T>
Graph<T>::~Graph()
{
    // delete this->adjacencyList;
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

/// @brief Adds a prebuilt edge to the graph
/// @param The source vertex
/// @param The prebuilt edge
/// @author Jonas Flückiger
/// @date 15.05.2023
template <typename T>
void Graph<T>::addPrebuiltEdge(T *source, Edge<T> *edge)
{
    this->adjacencyList[source].push_back(edge);
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
        if (this->getVertexIndegree(vertex.first) % 2 != 0 || this->getVertexOutdegree(vertex.first) % 2 != 0)
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
    if (this->adjacencyList.size() >= 1)
    {
        T *vertex = this->adjacencyList.begin()->first;

        std::list<T *> visited;
        std::list<T *> toVisit;

        toVisit.push_back(vertex);

        while (!toVisit.empty())
        {
            T *currentVertex = *toVisit.begin();
            visited.push_back(currentVertex);

            for (auto &adjacentVertex : this->adjacencyList[currentVertex])
            {
                bool notVisited = std::find(visited.begin(), visited.end(), adjacentVertex->getTarget()) == visited.end();
                bool notEncountered = std::find(toVisit.begin(), toVisit.end(), adjacentVertex->getTarget()) == toVisit.end();
                if (notVisited && notEncountered)
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
    for (auto const &vertex : this->adjacencyList)
    {
        for (auto const &edge : vertex.second)
        {
            if (edge->getWeight() != 1)
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
    std::vector<std::pair<T *, std::list<Edge<T> *>>> verticesOrderedByDegree;

    // Copy key-value pair from Map
    // to vector of pairs
    for (auto &it : this->adjacencyList)
    {
        verticesOrderedByDegree.push_back(it);
    }

    // Sort using comparator function
    sort(verticesOrderedByDegree.begin(), verticesOrderedByDegree.end(), [this](std::pair<T *, std::list<Edge<T> *>> a, std::pair<T *, std::list<Edge<T> *>> b)
         {
        int aDegree = this->getVertexIndegree(a.first) + this->getVertexIndegree(a.first);
        int bDegree = this->getVertexIndegree(b.first) + this->getVertexIndegree(b.first);
        return aDegree < bDegree; });

    // COLORING THE VERTICES
    // A map of pairs vertex <-> color
    // Colors are simply represented by an integer
    std::unordered_map<T *, int> colorMap;
    // Function to check if a vertex can be assigned a given color
    auto canAssignColor = [&](T *vertex, int color)
    {
        for (auto &adjacentVertex : this->adjacencyList[vertex])
        {
            if (colorMap[adjacentVertex->getTarget()] == color)
            {
                return false;
            }
        }
        return true;
    };

    int numVertices = this->getNbVertices();
    int chromaticNumber = 0;

    // Try to assign colors from 1 to max. number of colors
    for (auto const &vertexStruct : verticesOrderedByDegree)
    {
        int colorNum = 1;
        while (colorNum <= numVertices)
        {
            if (canAssignColor(vertexStruct.first, colorNum))
            {
                // Assign a color
                colorMap[vertexStruct.first] = colorNum;
                chromaticNumber = colorNum > chromaticNumber ? colorNum : chromaticNumber;
                break;
            }
            else
            {
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

/// @brief Returns a new graph which is a minimum spanning tree of the initial graph.
///
/// This method uses Prim's algorithm.
/// @author Jonas Flückiger
/// @date 15.05.2023
template <typename T>
Graph<T> *Graph<T>::getMinimumSpanningTree()
{
    Graph<T> *msTree = new Graph<T>();

    // This method uses a standard library priority queue. Because this implementation does not allow
    // priority updates, we must check if each element we pop is the most up-to-date one
    // see https://stackoverflow.com/questions/649640/how-to-do-an-efficient-priority-update-in-stl-priority-queue
    auto cmp = [](queue_element<T> left, queue_element<T> right)
    { return left.priority > right.priority; };
    std::unordered_map<T *, int> upToDatePrios = std::unordered_map<T *, int>();
    std::priority_queue<queue_element<T>, std::vector<queue_element<T>>, decltype(cmp)> toVisit(cmp);

    // Add first vertex and its edges
    msTree->addVertex(this->adjacencyList.begin()->first);
    for (Edge<T> *&edge : this->adjacencyList.begin()->second)
    {
        toVisit.push(queue_element<T>(edge->getWeight(), this->adjacencyList.begin()->first, edge));
        upToDatePrios.insert(std::make_pair(edge->getTarget(), edge->getWeight()));
    }
    while (!toVisit.empty())
    {
        // Get the top element
        queue_element<T> top = toVisit.top();
        toVisit.pop();

        // Ignore out-of-date elements
        bool visited = msTree->adjacencyList.find(top.edge->getTarget()) != msTree->adjacencyList.end();
        if (visited || top.priority > upToDatePrios[top.edge->getTarget()])
        {
            continue;
        }

        // Visit the vertex and add it to the tree
        msTree->addVertex(top.edge->getTarget());
        msTree->addPrebuiltEdge(top.source, top.edge);
        if (!this->isOriented())
        {
            auto hasSourceAsTarget = [&top](Edge<T> *edge)
            {
                return edge->getTarget() == top.source;
            };

            // Find corresponding edge
            Edge<T> *reverseEdge = nullptr;
            for (auto const &edge : this->adjacencyList[top.edge->getTarget()])
            {
                if (hasSourceAsTarget(edge))
                {
                    reverseEdge = edge;
                    continue;
                }
            }

            // Add the reverse path
            if (reverseEdge != nullptr)
            {
                msTree->addPrebuiltEdge(top.edge->getTarget(), reverseEdge);
            }
        }

        // Add all its neighbour and update edges weight
        for (Edge<T> *&edge : this->adjacencyList[top.edge->getTarget()])
        {
            // Check if next vertex was already visited
            bool notVisited = msTree->adjacencyList.find(edge->getTarget()) == msTree->adjacencyList.end();
            if (notVisited)
            {
                // Check if the next vertex wasnt already encountered and if it was, that the new prio is smaller
                if (upToDatePrios.find(edge->getTarget()) == upToDatePrios.end())
                {
                    upToDatePrios.insert(std::make_pair(edge->getTarget(), edge->getWeight()));
                }
                else if (edge->getWeight() < upToDatePrios[edge->getTarget()])
                {
                    upToDatePrios.erase(edge->getTarget());
                    upToDatePrios.insert(std::make_pair(edge->getTarget(), edge->getWeight()));
                }
                toVisit.push(queue_element<T>(edge->getWeight(), top.edge->getTarget(), edge));
            }
        }
    }
    return msTree;
}

/// @brief Returns a new graph which is the shortest paths graph of the initial graph.
///
/// This method uses Dijkstra's algorithm.
/// @author Jonas Flückiger
/// @date 26.05.2023
template <typename T>
Graph<T> *Graph<T>::getMinimumDistanceGraph(T *startingVertex)
{
    Graph<T> *mdGraph = new Graph<T>();

    // This method uses a standard library priority queue. Because this implementation does not allow
    // priority updates, we must check if each element we pop is the most up-to-date one
    // see https://stackoverflow.com/questions/649640/how-to-do-an-efficient-priority-update-in-stl-priority-queue
    auto cmp = [](queue_element<T> left, queue_element<T> right)
    { return left.priority > right.priority; };
    std::unordered_map<T *, int> upToDatePrios = std::unordered_map<T *, int>();
    std::priority_queue<queue_element<T>, std::vector<queue_element<T>>, decltype(cmp)> toVisit(cmp);

    // Add first vertex and its edges
    mdGraph->addVertex(startingVertex);
    for (Edge<T> *&edge : this->adjacencyList[startingVertex])
    {
        toVisit.push(queue_element<T>(edge->getWeight(), startingVertex, edge));
        upToDatePrios.insert(std::make_pair(edge->getTarget(), edge->getWeight()));
    }
    while (!toVisit.empty())
    {
        // Get the top element
        queue_element<T> top = toVisit.top();
        toVisit.pop();

        // Ignore out-of-date elements
        bool visited = mdGraph->adjacencyList.find(top.edge->getTarget()) != mdGraph->adjacencyList.end();
        if (visited || top.priority > upToDatePrios[top.edge->getTarget()])
        {
            continue;
        }

        // Visit the vertex and add it to the tree
        mdGraph->addVertex(top.edge->getTarget());
        mdGraph->addPrebuiltEdge(top.source, top.edge);
        if (!this->isOriented())
        {
            auto hasSourceAsTarget = [&top](Edge<T> *edge)
            {
                return edge->getTarget() == top.source;
            };

            // Find corresponding edge
            Edge<T> *reverseEdge = nullptr;
            for (auto const &edge : this->adjacencyList[top.edge->getTarget()])
            {
                if (hasSourceAsTarget(edge))
                {
                    reverseEdge = edge;
                    continue;
                }
            }

            // Add the reverse path
            if (reverseEdge != nullptr)
            {
                mdGraph->addPrebuiltEdge(top.edge->getTarget(), reverseEdge);
            }
        }

        // Add all its neighbour and update edges weight
        for (Edge<T> *&edge : this->adjacencyList[top.edge->getTarget()])
        {
            // Check if next vertex was already visited
            bool notVisited = mdGraph->adjacencyList.find(edge->getTarget()) == mdGraph->adjacencyList.end();
            if (notVisited)
            {
                // Check if the next vertex wasnt already encountered and if it was, that the new prio is smaller
                if (upToDatePrios.find(edge->getTarget()) == upToDatePrios.end())
                {
                    upToDatePrios.insert(std::make_pair(edge->getTarget(), top.priority + edge->getWeight()));
                }
                else if (top.priority + edge->getWeight() < upToDatePrios[edge->getTarget()])
                {
                    upToDatePrios.erase(edge->getTarget());
                    upToDatePrios.insert(std::make_pair(edge->getTarget(), top.priority + edge->getWeight()));
                }
                upToDatePrios.insert(std::make_pair(edge->getTarget(), top.priority + edge->getWeight()));
                toVisit.push(queue_element<T>(top.priority + edge->getWeight(), top.edge->getTarget(), edge));
            }
        }
    }
    return mdGraph;
}

/// @brief Serializes a graph into the DOT format.
///
/// The templated class will also be serialized using the out stream operator.
/// @author Jonas Flückiger
/// @date 26.05.2023
template <typename T>
std::string Graph<T>::exportToDOT()
{
    std::ostringstream os;
    os << "digraph {" << std::endl;
    for (auto &vertexPair : this->adjacencyList)
    {
        for (auto &edge : vertexPair.second)
        {
            os << '"' << vertexPair.first << '"';
            os << " -> ";
            os << '"' << edge->getTarget() << '"';
            os << " [weight=";
            os << edge->getWeight();
            os << "]";
            os << std::endl;
        }
    }
    os << "}";
    return os.str();
}
#endif // GRAPH_H
