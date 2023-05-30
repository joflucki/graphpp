#include "qmemento.h"

QMemento::QMemento(std::unordered_map<QVertex *, std::list<Edge<QVertex> *>> adjencyList)
{
    this->adjacencyList = adjencyList;
}
std::unordered_map<QVertex *, std::list<Edge<QVertex> *>> QMemento::getAdjencyList()
{
    return this->adjacencyList;
}
