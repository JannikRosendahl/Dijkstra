//
// Created by rosendahl on 04/12/2021.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <utility>
#include "Graph.h"


Graph::Graph(std::vector<Vertex> vertices, std::vector<Edge> edges, int start, int end) {
    this->vertices = std::move(vertices);
    this->edges = std::move(edges);

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
    }

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

/**
 * helper function to remove unwanted chars from string
 * @param in string to remove from
 * @param to_remove chars to remove
 * @return 'in' without 'to_remove'
 */
std::string clean_string(std::string& in, const std::string& to_remove) {
    for(char c : to_remove)
        in.erase(std::remove(in.begin(), in.end(), c), in.end());
    return in;
}

/**
 * helper function to extract vector of ints from a string
 * @param in input string
 * @return vector of ints in 'in'
 */
std::vector<int> extract_ints(const std::string& in) {
    std::vector<int> v = std::vector<int>();

    std::stringstream ss;
    ss << in;

    std::string segment;

    while(std::getline(ss, segment, ',')) {
        v.emplace_back(std::stoi(segment));
    }
    return v;
}

/**
 * constructs graph from file
 * input file has to contain 3 sets of ints. a set is delimited by '}',
 * integers are seperated by ','
 * 1st set contains vertex ids
 * 2nd set contains start vertex id and end vertex id
 * 3rd set contains edges in groups of 3 ints: start vertex id, end vertex id, weight
 * @param input_file_name
 */
Graph::Graph(const std::string& input_file_name) {
    std::ifstream input_file(input_file_name);

    //check if we could open the file
    if (!input_file.is_open()) {
        std::cout << "failed to open file " << std::filesystem::current_path() << "/" << input_file_name << std::endl;
        return;
    }

    //read entire file into input_stream
    std::stringstream input_stream = std::stringstream();
    std::string line;
    while (getline(input_file, line)) {
        input_stream << line;
    }
    input_file.close();

    //read 3 sets delimited by '}', vertices, start+end, edges
    std::string vertices_str;
    std::string start_end_str;
    std::string edges_str;
    getline(input_stream, vertices_str, '}');
    getline(input_stream, start_end_str, '}');
    getline(input_stream, edges_str, '}');

    //clean up input to extract ints later
    vertices_str = clean_string(vertices_str, "\n\r{} ");
    start_end_str = clean_string(start_end_str, "\n\r{} ");
    edges_str = clean_string(edges_str, "\n\r{} ()");

    //get vector of ints from input
    std::vector<int> vertex_ids = extract_ints(vertices_str);
    std::vector<int> start_end_ids = extract_ints(start_end_str);
    std::vector<int> edge_ids = extract_ints(edges_str);

    //start building vertex vector
    this->vertices = std::vector<Vertex>();
    for(int i : vertex_ids) {
        Vertex v = Vertex(i);
        this->vertices.emplace_back(v);
    }

    //set start/end
    int start_id = start_end_ids[0];
    int end_id = start_end_ids[1];
    for(auto& vertex : this->vertices) {
        if(vertex.get_id() == start_id)
            this->start = &vertex;
        if(vertex.get_id() == end_id) {
            this->end = &vertex;
        }
    }

    //build edges
    for(int i=0; i<edge_ids.size(); i+=3) {
        Edge e = Edge(edge_ids[i], edge_ids[i+1], edge_ids[i+2]);
        this->edges.emplace_back(e);
    }

    this->generate_associations();
}

