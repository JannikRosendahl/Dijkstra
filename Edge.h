//
// Created by rosendahl on 04/12/2021.
//

#ifndef DIJKSTRA_EDGE_H
#define DIJKSTRA_EDGE_H


#include <set>

class Vertex;

class Edge {
private:
    int start;
    int end;
    int weight;

    std::set<Vertex*> connected_vertices;
public:
    [[nodiscard]] int get_start() const;
    [[nodiscard]] int get_end() const;

    Edge(int start, int end, int weight);
    void add_vertex(Vertex* v);

    [[nodiscard]] int get_weight() const;
};


#endif //DIJKSTRA_EDGE_H
