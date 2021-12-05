//
// Created by rosendahl on 04/12/2021.
//

#ifndef DIJKSTRA_GRAPH_H
#define DIJKSTRA_GRAPH_H


#include <vector>
#include "Vertex.h"

class Graph {
private:
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;

    Vertex* start;
    Vertex* end;
    void generate_associations();
public:
    Graph(std::vector<Vertex> vertices, std::vector<Edge> edges, int start, int end);
    void dijkstra();
    void print();
};


#endif //DIJKSTRA_GRAPH_H
