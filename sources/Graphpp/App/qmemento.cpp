#include "qmemento.h"

/**
 * @brief Default constructor for data structs
 * @author Flückiger Jonas
 */
QMemento::QMemento(){}

/// @brief Constructor of QMemento
/// @author Plumey Simon
QMemento::QMemento(std::unordered_map<QVertex *, std::list<Edge<QVertex> *>> adjencyList)
{
    this->adjacencyList = adjencyList;
}

/// @brief Getter of attribut adjencyList
/// @return std::unordered_map<QVertex *, std::list<Edge<QVertex> *>>
/// @author Plumey Simon
std::unordered_map<QVertex *, std::list<Edge<QVertex> *>> QMemento::getAdjencyList()
{
    return this->adjacencyList;
}
