//
// Created by rosendahl on 04/12/2021.
//

#include <vector>
#include <iostream>
#include "Edge.h"

Edge::Edge(int start, int end, int weight) {
    this->start = start;
    this->end = end;
    this->weight = weight;

    this->connected_vertices = std::set<Vertex*>();
}

void Edge::add_vertex(Vertex* v) {
    this->connected_vertices.emplace(v);
    if(connected_vertices.size() > 2) {
        std::cout << "trying to connect more than 2 vertices to edge" << std::endl;
        exit(1);
    }
}

int Edge::get_start() const {
    return start;
}

int Edge::get_end() const {
    return end;
}

int Edge::get_weight() const {
    return this->weight;
}
