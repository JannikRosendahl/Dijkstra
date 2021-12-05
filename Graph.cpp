//
// Created by rosendahl on 04/12/2021.
//

#include <iostream>
#include "Graph.h"


Graph::Graph(std::vector<Vertex> vertices, std::vector<Edge> edges, int start, int end) {
    this->vertices = vertices;
    this->edges = edges;

    //set start and end vertex
    for(auto& vertex : this->vertices) {
        if(vertex.get_id() == start)
            this->start = &vertex;
        if(vertex.get_id() == end) {
            this->end = &vertex;
        }
    }

    this->generate_associations();
}

/**
 * every vertex holds a record of edges (Edge*) and neighbours (Vertex*)
 * it is connected to. this function sets these records
 */
void Graph::generate_associations() {
    //loop over all edges
    for(auto& edge : this->edges) {
        int id_1 = edge.get_start();
        int id_2 = edge.get_end();

        Vertex* v_1;
        Vertex* v_2;

        for(auto& vertex : this->vertices) {
            if(vertex.get_id() == id_1) {
                v_1 = &vertex;
            }
            if(vertex.get_id() == id_2) {
                v_2 = &vertex;
            }
        }
        v_1->add_neighbour(v_2);
        v_2->add_neighbour(v_1);

        v_1->add_edge(&edge);
        v_2->add_edge(&edge);

        //std::cout << v_1 << " " << v_2 << std::endl;
    }

    //this->print();
}

void Graph::print() {
    std::cout << "start: " << this->start->get_id() << " " << this->start << std::endl;
    std::cout << "end: " << this->end->get_id() << " " << this->end << std::endl;
    for(auto& v : this->vertices) {
        v.print();
        std::cout << "----------------------------------" << std::endl;
    }
}

void Graph::dijkstra() {
    // set distance of start vertex to 0, all other distances are already initialized to int max
    this->start->set_distance(0);

    //while there are vertices marked as unvisited
    int num_unvisited_vertices;
    do {
        //get vertex with minimal distance that has not been visited
        Vertex* v = nullptr;
        for(auto& vertex : this->vertices) {
            if(v == nullptr) {
                if(!vertex.get_visited())
                    v = &vertex;
                continue;
            }
            if(vertex.get_visited())
                continue;
            if(v->get_distance() < v->get_distance())
                v = &vertex;
        }
        std::cout << "vertex with min distance is" << std::endl;
        v->print();
        v->set_visited(true);

        //calculate distance to all neighbour vertices
        for(auto& neighbour : v->get_neighbours()) {
            //find edge that connects v to neighbour
            Edge* connection;
            for(auto& v_edge : v->get_edges()) {
                for(auto& n_edge : neighbour->get_edges()) {
                    if(v_edge == n_edge) {
                        //std::cout << "found connecting edge " << v_edge->get_start() << ":" << v_edge->get_end() <<  std::endl;
                        connection = v_edge;
                    }
                }
            }
            std::cout << "neighbour dist: " << neighbour->get_distance() << "con weight: " << connection->get_weight() << std::endl;
            //the connection from v to neighbour has been found, check if this is a shorter way to neighbour
            if(v->get_distance() + connection->get_weight() < neighbour->get_distance()) {
                std::cout << "found faster connection from " << v->get_id() << " to " << neighbour->get_id() << std::endl;
                //this is indeed a faster connection, set distance, predecessor of neighbour
                neighbour->set_distance(v->get_distance() + connection->get_weight());
                neighbour->set_predecessor(v);
            }

        }

        //repeat while there are unvisited edges
        num_unvisited_vertices = 0;
        for(auto& vertex : this->vertices) {
            if(!vertex.get_visited())
                num_unvisited_vertices++;
        }
        std::cout << "num_unvisited_vertices: " << num_unvisited_vertices << std::endl;
    } while(num_unvisited_vertices > 0);

    this->print();

    //print path in reverse order
    Vertex* current_vertex = this->end;
    do {
        current_vertex->print();
        current_vertex = current_vertex->get_predecessor();
    } while(current_vertex != this->start->get_predecessor());
}

