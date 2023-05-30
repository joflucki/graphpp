#ifndef QMEMENTO_H
#define QMEMENTO_H
#include <unordered_map>
#include <list>
#include "qvertex.h"
#include <edge.h>

class QMemento
{
public:
    QMemento(std::unordered_map<QVertex *, std::list<Edge<QVertex> *>> adjencyList);
    std::unordered_map<QVertex *, std::list<Edge<QVertex> *>> getAdjencyList();

private:
    std::unordered_map<QVertex *, std::list<Edge<QVertex> *>> adjacencyList;

};

#endif // QMEMENTO_H
