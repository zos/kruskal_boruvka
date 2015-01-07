#include <graph/Graph.h>
#include <serializer/GraphPrinter.h>
#include <serializer/GraphSerialization.h>
#include <kruskal/Kruskal.h>
#include <log/Log.h>

#include <chrono>
#include <fstream>

using namespace GIS;
int main(int argc, char **argv) {
    std::string filename;
    if (argc == 2) {
        filename = argv[1];
    } else {
        filename = "graph10v_40e.txt";
    }

    std::ifstream fin(filename);
    if(!fin) {
        LOGE("Couldn't set file >" << filename << "<");
        return -1;
    }

    Graph graph;
    fin >> graph;
    if(!fin) {
        LOGE("Couldn't set graph from file >" << filename << "<");
        return -1;
    }

    printGraph(graph, "Graph:");
    Algorithms::Kruskal kruskal;
    kruskal.setGraph(graph);
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < 100; i++)
        kruskal.prepareMST();
    auto end = std::chrono::system_clock::now();


    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                          /(float)100;
    std::string unit = "mks";
    auto goodDuration = duration;
    if (duration > 1000) {
        goodDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                          /(float)100;
        unit = "ms";
    } else if (duration < 10) {
        goodDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
                          /(float)100;
        unit = "ns";
    }
    LOG("Duration: " << goodDuration << " " << unit);

    auto mst = kruskal.getMST();
    printGraph(mst, "MST:");
    return 0;
}



