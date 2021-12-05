cmake_minimum_required(VERSION 3.16)
project(Dijkstra)

set(CMAKE_CXX_STANDARD 20)

add_executable(Dijkstra main.cpp Vertex.cpp Vertex.h Edge.cpp Edge.h Graph.cpp Graph.h)
