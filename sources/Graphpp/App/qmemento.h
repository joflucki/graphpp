#ifndef QMEMENTO_H
#define QMEMENTO_H
#include <unordered_map>
#include <list>
#include "qvertex.h"
#include <edge.h>

/// @brief Memento of qboard state. It's part of the memento design pattern
/// @author Plumey Simon
/// @date spring 2023
class QMemento
{
public:
    QMemento(); // Default constructor for use in data structs
    QMemento(std::unordered_map<QVertex *, std::list<Edge<QVertex> *>> adjencyList);
    std::unordered_map<QVertex *, std::list<Edge<QVertex> *>> getAdjencyList();

private:
    std::unordered_map<QVertex *, std::list<Edge<QVertex> *>> adjacencyList;

};

#endif // QMEMENTO_H
