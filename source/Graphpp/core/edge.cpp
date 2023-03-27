#include "edge.h"

template <typename T> Edge<T>::Edge(T target, int weight){
    this->target = target;
    this->weight = weight;
}

template <typename T> T* Edge<T>::getTarget(){
    return this->target;
}
template <typename T> int Edge<T>::getWeight(){
    return this->weight;
}
template <typename T> void Edge<T>::setWeight(int weight){
    this->weight = weight;
}
