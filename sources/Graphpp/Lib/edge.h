#ifndef EDGE_H
#define EDGE_H

/// @brief Represents a graph edge as a member of an adjacency list and allows to handle the edges of a graph
/// @author The Graph++ Development Team
/// @date spring 2023
///
/// An Edge is represented as a combination of a target vertex and a weight.
/// The source vertex is not included as the edge belongs to the adjacency list corresponding to the source vertex.
template <typename T> class Edge {
private:
    /// @brief The target vertex
    T* target;
    /// @brief The weight of the edge
    int weight;

public:
    Edge(); //Default constructor for arrays
    Edge(T *target, int weight = 1);
    T* getTarget();
    int getWeight();
    void setWeight(int weight);
};

/// @brief A simple edge constructor
/// @param target The target vertex
/// @param weight The weight of the edge
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T> Edge<T>::Edge(T *target, int weight){
    this->target = target;
    this->weight = weight;
}

/// @brief Returns the target vertex of the edge
/// @returns The target vertex of the edge
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T> T* Edge<T>::getTarget(){
    return this->target;
}

/// @brief Returns the weight of the edge
/// @returns The weight of the edge
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T> int Edge<T>::getWeight(){
    return this->weight;
}

/// @brief Sets the weight of the edge
/// @param weight The weight to set
/// @author Damien Tschan
/// @date 17.04.2023
template <typename T> void Edge<T>::setWeight(int weight){
    this->weight = weight;
}

#endif // EDGE_H
