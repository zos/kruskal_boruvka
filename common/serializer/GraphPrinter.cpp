#include "GraphPrinter.h"
#include <iostream>

void printGraph(const GIS::Graph &graph) {
    auto list = graph.getNeighbourhoodList();
    auto vertexes = graph.getVertexAmount();

    for (std::size_t i = 0; i < vertexes; i++) {
        std::cout << i << " : ";
        for (auto &edge : list[i]) {
            std::cout << edge.end() << " <" << edge.value() << ">, ";
        }
        std::cout << std::endl;
    }
}


