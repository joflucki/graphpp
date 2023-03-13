#ifndef EDGE_H
#define EDGE_H
#include "vertex.h"

class Edge
{
public:
    Edge(Vertex* source, Vertex* target);

private:
    Vertex* source;
    Vertex* target;
};

#endif // EDGE_H
