//
// Created by rosendahl on 04/12/2021.
//

#include <iostream>
#include "Vertex.h"

Vertex::Vertex(int identifier) {
    this->id = identifier;
    this->connected_edges = std::set<Edge*>();
    this->neighbour_vertices = std::set<Vertex*>();

    this->distance = 99999999;
    this->predecessor = nullptr;
    this->visited = false;
}

void Vertex::print() const {
    std::cout << "< Vertex ID: " << this->id << " >" << std::endl;
    std::cout << "\tmy distance is " << this->distance << std::endl;
    if(this->predecessor != nullptr)
        std::cout << "\tmy predecessor has ID " << this->predecessor->get_id() << std::endl;

    /*for(auto &edge : this->connected_edges) {
        std::cout << "\tconnected to edge " << edge->get_start() << ":" << edge->get_end() << std::endl;
    }
    for(auto &vertex : this->neighbour_vertices) {
        std::cout << "\tconnected to neighbour " << vertex->get_id() << std::endl;
    }*/
}

void Vertex::add_edge(Edge* e) {
    this->connected_edges.emplace(e);
}

void Vertex::add_neighbour(Vertex *v) {
    this->neighbour_vertices.emplace(v);
}


int Vertex::get_id() const {
    return id;
}

int Vertex::get_distance() const {
    return this->distance;
}

Vertex *Vertex::get_predecessor() const {
    return this->predecessor;
}

bool Vertex::get_visited() const {
    return this->visited;
}

std::set<Vertex *> Vertex::get_neighbours() const {
    return this->neighbour_vertices;
}

std::set<Edge*> Vertex::get_edges() const {
    return this->connected_edges;
}

void Vertex::set_distance(int d) {
    this->distance = d;
}

void Vertex::set_predecessor(Vertex* v) {
    this->predecessor = v;
}

void Vertex::set_visited(bool b) {
    this->visited = b;
}
