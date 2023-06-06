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

/// @brief Represents a mathematical graph and allows to handle the creation, modification and analysis of it.
/// @author The Graph++ Development Team
/// @date spring 2023
template <typename T> class Graph
{
public:
    Graph();
    ~Graph();

    // -- attributes --
    /// @brief Represents a graph as an adjacency list
    std::unordered_map<T *, std::list<Edge<T> *>> adjacencyList;

    // -- modifiers --
    void addVertex(T *vertex);
    void addEdge(T *source, T *target, int weight = 1);
    void addDoubleEdge(T *vertex1, T *vertex2, int weight = 1);
    void addPrebuiltEdge(T *source, Edge<T> *);
    void removeVertex(T *vertex);
    std::list<Edge<T>*> popVertex(T *vertex);
    void removeEdge(Edge<T> *edge);
    void popEdge(Edge<T> *edge);

    // -- analysis --
    bool isEmpty();
    bool isEulerian();
    bool isHamiltonian();
    bool isConnected();
    bool isStronglyConnected();

    bool isOriented();
    bool isWeighted();
    int getChromaticNumber();
    int getNbEdges();
    int getNbVertices();
    int getVertexIndegree(T *vertex);
    int getVertexOutdegree(T *vertex);

    // Paths, cycles, trees, subgraphs
    Graph<T> *getMinimumSpanningTree();
    Graph<T> *getMinimumDistanceGraph(T *startingVertex);
    Graph<T> *getHamiltonianPath();

    // Serialization
    std::string exportToDOT();

    // Operators
    template <typename T2>
    friend std::ostream &operator<<(std::ostream &os, const Graph<T2> &p);

    template <typename T2>
    friend std::istream &operator>>(std::istream &is, Graph<T2> &p);
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

/// @brief Returns whether the graph is empty
/// @returns Whether the graph is empty
/// @author Damien Tschan
/// @date 05.06.2023
template <typename T>
bool Graph<T>::isEmpty()
{
    return this->adjacencyList.size() == 0;
}

/// @brief Adds a vertex to the graph
/// @param vertex A vertex
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
/// @param source Source vertex
/// @param target Target vertex
/// @param weight The weight of the edge
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T>
void Graph<T>::addEdge(T *source, T *target, int weight)
{
    if (this->adjacencyList.find(source) != this->adjacencyList.end())
    {
        if (this->adjacencyList.find(target) != this->adjacencyList.end())
        {
            std::list<Edge<T>*> existingEdges = this->adjacencyList[source];
            bool edgeAlreadyExists = false;
            for(Edge<T>* existingEdge : existingEdges)
            {
                if(existingEdge->getTarget() == target)
                {
                    edgeAlreadyExists = true;
                }
            }
            if(!edgeAlreadyExists)
            {
                Edge<T> *newEdge = new Edge(target, weight);
                this->adjacencyList[source].push_back(newEdge);
            }
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
/// @param vertex1 A vertex
/// @param vertex2 Another vertex
/// @param weight The weight of the edge
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

/// @brief Removes a vertex and its linked edges from the graph and deletes them
/// @param vertex A vertex
/// @author Damien Tschan
/// @date 01.06.2023
template <typename T>
void Graph<T>::removeVertex(T *vertex)
{
    // Remove all edges related to the vertex
    std::list<Edge<T>*> poppedEdges = popVertex(vertex);
    for(auto *edge : poppedEdges)
    {
        delete edge;
    }

    // Remove the vertex from the map
    delete vertex;
}

/// @brief Removes a vertex and its linked edges from the graph but doesn't delete anything
/// @param vertex A vertex
/// @author Damien Tschan
/// @date 01.06.2023
/// @return a list of all removed edges (removed from the graph but not deleted)
///
/// As the targeted vertex is a parameter of the function, it doesn't need to be returned (the caller already knows it)
template <typename T>
std::list<Edge<T>*> Graph<T>::popVertex(T *vertex)
{
    std::list<Edge<T>*> poppedEdges;

    // Remove all edges targeting the vertex
    for (auto &vertexPair : this->adjacencyList)
    {
        auto &edgeList = vertexPair.second;
        auto edgeIt = edgeList.begin();
        while (edgeIt != edgeList.end())
        {
            if ((*edgeIt)->getTarget() == vertex)
            {
                poppedEdges.push_back(*edgeIt);
                edgeIt = edgeList.erase(edgeIt);
            }
            else
            {
                ++edgeIt;
            }
        }
    }

    // Remove all edges sourcing from the vertex
    /*
    auto &edgeList = this->adjacencyList[vertex];
    auto edgeIt = edgeList.begin();
    while (edgeIt != edgeList.end())
    {
        poppedEdges.push_back(*edgeIt);
        this->adjacencyList[vertex].erase(edgeIt);
        ++edgeIt;
    }*/

    this->adjacencyList[vertex].clear();

    // Remove the vertex from the map
    adjacencyList.erase(vertex);

    return poppedEdges;
}

/// @brief Removes an edge from the graph and deletes it completely
/// @param edge An edge
/// @author Damien Tschan
/// @date 01.06.2023
template <typename T>
void Graph<T>::removeEdge(Edge<T> *edge)
{
    popEdge(edge);
    delete edge;
    edge = nullptr;
}

/// @brief Removes an edge from the graph but doesn't delete it
/// @param edge An edge
/// @author Damien Tschan
/// @date 01.06.2023
///
/// As the targeted edge is a parameter of the function, it doesn't need to be returned (the caller already knows it)
template <typename T>
void Graph<T>::popEdge(Edge<T> *edge)
{
    for (auto &vertex : this->adjacencyList)
    {
        auto it = vertex.second.begin();
        while (it != vertex.second.end())
        {
            if (*it == edge)
            {
                it = vertex.second.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

/// @brief Returns whether the graph is eulerian
/// @returns Whether the graph is eulerian
/// @author Damien Tschan
/// @date 08.05.2023
template <typename T>
bool Graph<T>::isEulerian()
{
    for (auto &vertex : this->adjacencyList)
    {
        if (this->getVertexIndegree(vertex.first) % 2 != 0 || this->getVertexOutdegree(vertex.first) % 2 != 0)
        {
            return false;
        }
    }
    return true && this->isConnected();
}

/// @brief Returns whether the graph is hamiltonian
/// @returns Whether the graph is hamiltonian
/// @author Damien Tschan
/// @date 05.06.2023
template <typename T>
bool Graph<T>::isHamiltonian()
{
    return !getHamiltonianPath()->isEmpty();
}

/// @brief Returns the hamiltonian path of a graph
/// @returns A subgraph containing the hamiltonian path if it exists, an empty graph otherwise
/// @author Damien Tschan
/// @date 05.06.2023
///
/// Since the algorithm and deduction rules are oriented toward directed graphs, the
/// Hamilton circuits in an undirected graph will be generated twice each, with the nodes
/// named in opposite order. To prevent this redundancy, in step S3 of the search the successors
/// of the origin node may be numbered. Then the undirected arcs to successor nodes
/// which are numbered lower than the successor presently being considered should be
/// deleted. Thus if 0 is the origin and 1, 2, ... , K are its successors, delete arcs (0, 1),
/// (0, 2), - . . , (0, i - 1) when considering successor i.
template <typename T>
Graph<T>* Graph<T>::getHamiltonianPath()
{
    if(this->isConnected())
    {
        std::list<std::pair<T*,Edge<T>*>> finalGraphPath;
        std::list<T*> allVertices;
        std::list<T*> toVisit;
        std::list<T*> partialPath;
        std::unordered_map<int,std::unordered_map<Edge<T>*, int>> edgesStatus;
        //map<step<map<Edge, status>>
        // at each step : the status of the edge : 0 = Undecided, 1 = Required, 2 = Deleted
        // step (= partialPath.length) : 1 = start - when step = nbVertices -> path found, when step = 0 -> no path
        std::unordered_map<int, int> nextAdjacentVertex;
        //map<step, nextVertex>
        //at each step, which would be the next neighbouring vertex to be visited

        auto isPathAdmissible = [=]() mutable -> bool
        {
            bool admissible = true;
            int step = partialPath.size();
            std::cout << "BEGIN : " << step << std::endl;
            for(T* vertex : allVertices)
            {
                // === RULES TREATED IN THE NEXT SECTION ===
                // R. Required edge rules, A. Direction assignment rules, D. Deleted edge rules, F. Failure, or termination rules
                // ---
                // R1. If a vertex has only one directed arc entering (leaving), then that arc is required.
                // F1. Fail if any vertex becomes isolated, that is, has no incident arc.
                // F2. Fail if any vertex has only one incident arc.
                // F3. Fail if any vertex has no directed arc entering (leaving).

                int edgeCount = 0;
                Edge<T> *requiredEdge = NULL;

                // ENTERING
                for(auto edge : edgesStatus[step])
                {
                    if(edge.first->getTarget() == vertex)
                    {
                        if(edge.second == 0)
                        {
                            if(edgeCount == 0)
                            {
                                requiredEdge = edge.first;
                            }
                            edgeCount++;
                        }
                        if(edge.second == 1)
                        {
                            edgeCount = 100;
                            break;
                        }
                    }
                }

                if(edgeCount == 1)
                {
                    edgesStatus[step][requiredEdge] = 1;
                }

                if(edgeCount == 0)
                {
                    admissible = false;
                }

                // LEAVING
                for(Edge<T>* edge : this->adjacencyList[vertex])
                {
                    if(edgesStatus[step].find(edge) != edgesStatus[step].end())
                    {
                        if(edgesStatus[step][edge] == 0)
                        {
                            if(edgeCount == 0)
                            {
                                requiredEdge = edge;
                            }
                            edgeCount++;
                        }
                        if (edgesStatus[step][edge] == 1)
                        {
                            edgeCount = 100;
                            break;
                        }
                    }
                }

                if(edgeCount == 1)
                {
                    edgesStatus[step][requiredEdge] = 1;
                }

                if(edgeCount == 0)
                {
                    admissible = false;
                }

                // R2. If a vertex has only two arcs incident, then both arcs are required.
                // A1. If a vertex has a required directed arc entering (leaving), then all incident undirected
                //     arcs are assigned the direction leaving (entering) that vertex.

                // A2. If a vertex has a required undirected arc incident, and all other incident arcs are
                //     leaving (entering) the vertex, then the required arc is assigned the direction entering
                //     (leaving) the vertex.
                // D1. If a vertex has two required arcs incident, then all undecided arcs incident may
                //     be deleted.
                // D2. If a vertex has a required directed arc entering (leaving), then all undecided
                //     directed arcs entering (leaving) may be deleted.
                // D3. Delete any arc which forms a closed circuit with required arcs, unless it completes
                //     the Hamilton circuit.
                // F4. Fail if any vertex has two required directed arcs entering (leaving).
                // F5. Fail if any vertex has three required arcs incident.
                // F6. Fail if any set of required arcs forms a closed circuit, other than a Hamilton circuit
            }
            std::cout << "END : " << step << ":" << admissible << std::endl;
            return admissible;
        };

        for (auto &vertex : this->adjacencyList)
        {
            allVertices.push_back(vertex.first);
            for (Edge<T>* edge : vertex.second)
            {
                edgesStatus[1][edge] = 0;
            }
        }

        // S1. Select any single node as the initial path.
        partialPath.push_back(*allVertices.begin());
        nextAdjacentVertex[1]=0;

        // Conditions that make the algorithm end successfully
        bool endLoopPathFound = false;

        // Conditions that make the algorithm end unsuccessfully
        bool endLoopNoPath = false;

        while(!(endLoopPathFound || endLoopNoPath))
        {
            // S2. Test the path for admissibility.
            bool pathAdmissible = isPathAdmissible();

            // S3. If the path so far is admissible, list the successors of the last node chosen, and extend the path
            //      to the first of these.
            if(pathAdmissible)
            {
                std::list<T*> neighboursToVisit;
                T* lastVertex = partialPath.back();
                for (auto edgeToNeighbouringVertex : this->adjacencyList[lastVertex])
                {
                    if (std::find(toVisit.begin(), toVisit.end(), edgeToNeighbouringVertex->getTarget()) != toVisit.end())
                    {
                        if(edgesStatus[partialPath.size()][edgeToNeighbouringVertex] == 1)
                        {
                            neighboursToVisit.push_front(edgeToNeighbouringVertex->getTarget());
                        }
                        if(edgesStatus[partialPath.size()][edgeToNeighbouringVertex] != 2)
                        {
                            neighboursToVisit.push_back(edgeToNeighbouringVertex->getTarget());
                        }
                    }

                }
                if(nextAdjacentVertex[partialPath.size()] < (int)neighboursToVisit.size())
                {
                    auto firstNeighbourUnvisited = neighboursToVisit.begin();
                    std::advance(firstNeighbourUnvisited, nextAdjacentVertex[partialPath.size()]++);
                    toVisit.remove(*firstNeighbourUnvisited);
                    partialPath.push_back(*firstNeighbourUnvisited);
                    for(Edge<T>* edge : this->adjacencyList[lastVertex])
                    {
                        if(edge->getTarget() == *firstNeighbourUnvisited)
                        {
                            finalGraphPath.push_back(std::make_pair(lastVertex, edge));
                        }
                    }
                }
                // S5. If all extensions from a given node have been shown inadmissible, repeat step $4.
                else
                {
                    pathAdmissible = false;
                }
            }
            // S4. If the path so far is inadmissible, delete the last node chosen and choose the next listed successor
            //      of the preceding node. Repeat step $2.
            if(!pathAdmissible)
            {
                nextAdjacentVertex[partialPath.size()] = 0;
                edgesStatus[partialPath.size()].clear();
                toVisit.push_back(partialPath.back());
                partialPath.pop_back();
                if(!finalGraphPath.empty())
                {
                    finalGraphPath.pop_back();
                }
                // S6. If all extensions from the initial node have been shown inadmissible, then no circuit exists.
                if(partialPath.size() == 0)
                {
                    endLoopNoPath = true;
                }
            }
            // S7. If a successor of the last node is the origin, a Hamilton circuit is formed; if all Hamilton circuits
            //      are required, then list the circuit found, mark the partial path inadmissible, and repeat step $4.
            if(partialPath.begin() == partialPath.end() && partialPath.size() == this->adjacencyList.size()+1)
            {
                endLoopPathFound = true;
            }
        }

        if(endLoopPathFound)
        {
            Graph<T>* returnGraph = new Graph<T>();
            for(std::pair<T*, std::list<Edge<T>*>> vertexAdjList : this->adjacencyList)
            {
                returnGraph->addVertex(vertexAdjList.first);
            }
            for(std::pair<T*, Edge<T>*> edgePair : finalGraphPath)
            {
                returnGraph->addPrebuiltEdge(edgePair.first, edgePair.second);
            }
            return returnGraph;
        }
    }
    Graph<T>* returnGraph = new Graph<T>();
    return returnGraph;
}

/// @brief Returns whether the graph is connected
/// @returns Whether the graph is connected
/// @author Damien Tschan
/// @date 08.05.2023
template <typename T>
bool Graph<T>::isConnected()
{
    if (this->adjacencyList.size() >= 2)
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

/// @brief Returns whether the graph is strongly connected
/// @returns Whether the graph is strongly connected
/// @author Damien Tschan
/// @date 24.04.2023
template <typename T>
bool Graph<T>::isStronglyConnected()
{
    return this->getNbVertices() * log2(this->getNbVertices()) < this->getNbEdges();
}

/// @brief Returns whether the graph is oriented
/// @returns Whether the graph is oriented
/// @author Damien Tschan
/// @date 24.04.2023
template <typename T>
bool Graph<T>::isOriented()
{
    std::list<std::pair<bool,std::pair<T*,T*>>> edgeList;
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
    return oriented;
}

/// @brief Returns whether the graph is weighted
/// @returns Whether the graph is weighted
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

/// @brief Returns the amount of edges in the graph as an integer
/// @returns The amount of edges in the graph as an integer
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
/// @returns The amount of vertices in the graph as an integer
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T>
int Graph<T>::getNbVertices()
{
    return this->adjacencyList.size();
}

/// @brief Returns the indegree of a vertex
/// @param vertex A vertex
/// @returns The indegree of the vertex
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
/// @param vertex A vertex
/// @returns The outdegree of the vertex
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T>
int Graph<T>::getVertexOutdegree(T *vertex)
{
    if (this->adjacencyList.find(vertex) != this->adjacencyList.end())
    {
        return this->adjacencyList[vertex].size();
    }
    return 0;
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
