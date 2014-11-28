
#include "Graph.h"
#include "GraphGenerator.h"
#include <iostream>
#include <fstream>

using namespace GIS;

void printGraph(const Graph &graph) {
    auto list = graph.getNeighbourhoodList();
    auto vertexes = graph.getVertexAmount();

    for (int i = 0; i < vertexes; i++) {
        std::cout << i << " : ";
        for (auto &edge : list[i]) {
            std::cout << edge.end() << ", ";
        }
        std::cout << std::endl;
    }
}

void printGraphToFile(const Graph &graph, const std::string &filename) {
    std::ifstream file;
}

int main() {
    GraphGenerator g;

    g.setVertexAmount(100);
    g.setEdgeAmount(300);
    g.setTries(10);

    try {
        Graph graph = g.generate();
        printGraph(graph);
    } catch (GraphGenerator::InvalidParameterException &e) {
        std::cout << "Caught " << e.what() << std::endl;
    } catch (GraphGenerator::GraphNotConnectedException &e) {
        std::cout << "Caught " << e.what() << std::endl;
    }

    return 0;
}




