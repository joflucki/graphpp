/*! \mainpage Graph++ Documentation

\section intro_sec Introduction
Graph++ is a C++ project that provides a comprehensive toolkit for graph analysis and exploration.
The project consists of three main components: a library, a graphical user interface (GUI) application, and a unit test project.
Its primary aim is to facilitate graph-related tasks
such as calculating vertex degrees, chromatic numbers, Hamiltonian and Eulerian paths, and other properties.
Graph++ offers a valuable platform for researchers, students, and graph enthusiasts to analyze and explore graphs effectively.
Its library, GUI application, and unit test project work together to provide an instrument for graph analysis,
making it a useful resource for various graph-related tasks.

\subsection intro_lib Graph++ Library
The Graph++ library serves as the foundation of the project,
offering efficient implementations of various graph data structures and algorithms.
It provides developers with a straightforward API to create and modify graphs.
Additionally, the library includes algorithms for graph analysis,
enabling users to gain insights into the structure of their graphs.

\subsection intro_app Graph++ GUI App
The GUI application complements the library by providing a user-friendly interface for interacting with graphs.
It allows users to create, edit, and visualize graphs, applying algorithms and obtaining visual feedback on graph properties.
The application includes features such as graph editing tools, customizable layouts, and interactive displays of graph properties.

\section usage_sec Usage
\code
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
\endcode
*/