#include <iostream>
#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"


#undef GRAPH_FROM_MANUAL_INPUT
#define GRAPH_FROM_FILE


int main() {

#ifdef GRAPH_FROM_MANUAL_INPUT
    /*
        {1, 2, 3, 4, 5, 6, 7}
        { (1, 2, 7), (1, 3, 9), (1, 6, 14), (2, 3, 10), (2, 4, 15), (3, 4, 11), (3, 6, 2), (4, 5, 6), (5, 6, 9)}
    */
    std::vector<Vertex> vertices = std::vector<Vertex>();
    vertices.emplace_back(Vertex(1));
    vertices.emplace_back(Vertex(2));
    vertices.emplace_back(Vertex(3));
    vertices.emplace_back(Vertex(4));
    vertices.emplace_back(Vertex(5));
    vertices.emplace_back(Vertex(6));

    std::vector<Edge> edges = std::vector<Edge>();
    edges.emplace_back(Edge(1, 2, 7));
    edges.emplace_back(Edge(1, 3, 9));
    edges.emplace_back(Edge(1, 6, 14));
    edges.emplace_back(Edge(2, 3, 10));
    edges.emplace_back(Edge(2, 4, 15));
    edges.emplace_back(Edge(3, 4, 11));
    edges.emplace_back(Edge(3, 6, 2));
    edges.emplace_back(Edge(4, 5, 6));
    edges.emplace_back(Edge(5, 6, 9));

    Graph graph = Graph(vertices, edges, 1, 5);
    graph.dijkstra();
#endif

#ifdef GRAPH_FROM_FILE
    Graph graph = Graph("../input.txt");
    graph.print();
    graph.dijkstra();
#endif

    return 0;
}
