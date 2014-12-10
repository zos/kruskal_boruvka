#include <log/Log.h>
#include <graph/Graph.h>
#include "GraphGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace GIS;

void printGraph(const Graph &graph) {
    auto list = graph.getNeighbourhoodList();
    auto vertexes = graph.getVertexAmount();

    for (std::size_t i = 0; i < vertexes; i++) {
        std::cout << i << " : ";
        for (auto &edge : list[i]) {
            std::cout << edge.end() << ", ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char** argv) {
    std::size_t defaultVertexes = 100;
    std::size_t defaultEdges = defaultVertexes * (defaultVertexes - 1) / 4;

    if (argc == 3) {
        //TODO : check for error
        std::istringstream sstr(argv[1]);
        sstr >> defaultVertexes;
        sstr.clear();
        sstr.str(argv[2]);
        sstr >> defaultEdges;
    }
    // TODO : add help description

    LOG("Generating with vertexes: " << defaultVertexes << " and edges : " << defaultEdges);
    GraphGenerator g;

    std::string file_name = "graph" + std::to_string(defaultVertexes) + "v_" +
                            std::to_string(defaultEdges) + "e.txt";
    g.setFile(file_name);
    g.setVertexAmount(defaultVertexes);
    g.setEdgeAmount(defaultEdges);
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




