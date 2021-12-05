//
// Created by rosendahl on 04/12/2021.
//

#ifndef DIJKSTRA_VERTEX_H
#define DIJKSTRA_VERTEX_H

#include "Edge.h"

class Vertex {
private:
    int id;
    std::set<Edge*> connected_edges;
    std::set<Vertex*> neighbour_vertices;

    int distance;
    Vertex* predecessor;
    bool visited;
public:
    [[nodiscard]] int get_id() const;
    int get_distance() const;
    Vertex* get_predecessor() const;
    bool get_visited() const;
    std::set<Vertex*> get_neighbours() const;
    std::set<Edge*> get_edges() const;

    void set_distance(int d);
    void set_predecessor(Vertex* v);
    void set_visited(bool b);

    explicit Vertex(int identifier);
    void print() const;
    void add_edge(Edge* e);
    void add_neighbour(Vertex* v);
};


#endif //DIJKSTRA_VERTEX_H
