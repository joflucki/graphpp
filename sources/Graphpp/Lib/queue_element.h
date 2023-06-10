#ifndef QUEUE_ELEMENT_H
#define QUEUE_ELEMENT_H
#include "edge.h"

/**
 * @brief A structure to hold vertices in a priority queue.
 *
 * This structure is used for different graph search algorithms where vertices
 * and the way (source and egde) through which they were discovered must be saved in a priority queue.
 */
template <typename T>
struct queue_element{
    /**
     * @brief Builds a new queue element.
     * @param The priority of this element in the queue.
     * @param The vertex from which the element was discovered.
     * @param The edge connecting the source and the element.
     */
    queue_element(int priority, T*source, Edge<T>* edge){
        this->priority = priority;
        this->source = source;
        this->edge = edge;
    }
    ~queue_element<T>(){}

    /**
     * @brief The priority of this element in the queue.
     */
    int priority;
    /**
     * @brief The vertex from which the element was discovered
     */
    T* source;

    /**
     * @brief The edge connecting the source and the element.
     */
    Edge<T>* edge;
};

#endif // QUEUE_ELEMENT_H
