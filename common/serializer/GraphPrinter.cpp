#include "GraphPrinter.h"
#include <iostream>
#include <sstream>
#include <log/Log.h>

void printGraph(const GIS::Graph &graph, const std::string &msg) {
    auto list = graph.getNeighbourhoodList();
    auto vertexes = graph.getVertexAmount();
    LOGP(msg);
    std::stringstream line;

    for (std::size_t i = 0; i < vertexes; i++) {
        line << i << " : ";
        for (auto &edge : list[i]) {
            line << edge.end() << " <" << edge.value() << ">, ";
        }
        LOGP(line.str());
        line.str("");
    }
}


