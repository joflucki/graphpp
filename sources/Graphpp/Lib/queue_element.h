#ifndef QUEUE_ELEMENT_H
#define QUEUE_ELEMENT_H
#include "edge.h"

template <typename T>
struct queue_element{
    queue_element(int priority, T*source, Edge<T>* edge){
        this->priority = priority;
        this->source = source;
        this->edge = edge;
    }
    ~queue_element<T>(){}

    int priority;
    T* source;
    Edge<T>* edge;
};

#endif // QUEUE_ELEMENT_H
