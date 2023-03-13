#ifndef EDGE_H
#define EDGE_H
#include "vertex.h"

class Edge
{
public:
    Edge(Vertex* source, Vertex* target);

    //getters
    Vertex getSource();
    Vertex getTarget();
    int getWeight();

    //setters
    void setWeight(int weight);

private:
    Vertex* source;
    Vertex* target;
    int weight;
};

#endif // EDGE_H
