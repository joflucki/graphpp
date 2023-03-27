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
#endif // EDGE_H
