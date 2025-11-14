# Graph++ – Graphs in a Nutshell :spider_web:

Graph++ is a C++ library that provides a full‑featured toolbox for graph analysis and exploration. It ships with three main components: the core library, a graphical user‑interface (GUI) application, and a unit‑test suite. It is designed to help researchers, students and graph enthusiasts work efficiently with graphs (degree calculation, chromatic numbers, Hamiltonian/Eulerian paths, etc.).

> This project was initially developed on Gitlab. Pipelines remain in the Gitlab format.

## Project Structure

The repository is organized into three top‑level modules:
|Module|Purpose|
|------|-------|
|Library| C++ library (graph.h, implementations, data structures, algorithms). Provides a clean API for creating, modifying and analysing graphs.|
|Application|Desktop GUI application (Windows 64‑bit) that builds on the library. Offers visual editing, layout customisation, interactive property display and algorithm execution using Qt.|
|Tests|Unit‑test suite exercising the library’s functionality.|

## Usage (C++ Library)

Below is a minimal example showing how to create a circular graph, query basic properties and run a few algorithms. The main concept of Graph++ is that you are free to define the data type of the graph nodes. Graph++ uses templates to provide the user with the possibility of building graphs of integers, floats, or more complex data structures. In the examples below, a graph of integers is used.

```cpp
#include <graph.h>

    ///.......
    // Create some vertices
    int vertices[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Create a graph for those vertices
    Graph<int>* graph = new Graph<int>();

    // Add the vertices to the graph
    for(int i : vertices){
        graph->addVertex(&i);
    }

    // Add some edges to the graph (Circular graph)
    for(int i : vertices){
        int nextIndex = i + 1;
        if(nextIndex >= nbVertices){
            nextIndex = 0;
        }
        graph->addDoubleEdge(&vertices[i], &vertices[nextIndex]);
    }

    // Basic properties
    std::cout << graph->getNbVertices() << std::endl;
    std::cout << graph->getNbEdges() << std::endl;
    std::cout << graph->isOriented() << std::endl;
    std::cout << graph->isWeighted() << std::endl;

    // Algorithms
    Graph<int>* hamiltionianPath = graph->getHamiltonianPath();
    Graph<int>* shortestPathGraph = graph->getMinimumDistanceGraph(&vertices[3]);
    Graph<int>* minimumSpanningTree = graph->getMinimumSpanningTree();

```

# License

The software was developed by [Damien Tschan](https://github.com/damientschan), [Jonas Flückiger](https://github.com/joflucki), and [Simon Plumey](https://github.com/Krucksy), all rights reserved.
