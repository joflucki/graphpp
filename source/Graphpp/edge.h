#ifndef EDGE_H
#define EDGE_H

template <typename T> class Edge {
private:
    T* target;
    int weight;

public:
    Edge(T target, int weight = 1);
    T* getTarget();
    int getWeight();
    void setWeight(int weight);
};

template <typename T>
Edge<T>::Edge(T target, int weight){
    this->target = target;
    this->weight = weight;
}

template <typename T>
T* Edge<T>::getTarget(){
    return this->target;
}
template <typename T> int Edge<T>::getWeight(){
    return this->weight;
}
template <typename T> void Edge<T>::setWeight(int weight){
    this->weight = weight;
}

#endif // EDGE_H
