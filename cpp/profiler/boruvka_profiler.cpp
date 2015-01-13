#include <graph/Graph.h>
#include <serializer/GraphPrinter.h>
#include <serializer/GraphSerialization.h>
#include <boruvka/Boruvka.h>
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
    Algorithms::Boruvka boruvka;
    boruvka.setGraph(graph);

    int loop = 100;
    if (graph.getVertexAmount() < 100) loop = 1000;
    if (graph.getVertexAmount() >= 1000) loop = 10;

    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < loop; i++)
        boruvka.prepareMST();
    auto end = std::chrono::system_clock::now();


    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
                              /(float)100;
    std::string unit = "ns";
    auto goodDuration = duration;
    if (duration > 1000000) {
        goodDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                          /(float)100;
        unit = "ms";
    } else if (duration > 1000) {
        goodDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                          /(float)100;
        unit = "mks";
    }
    auto mst = boruvka.getMST();
    printGraph(mst, "MST:");
    LOG("Repeats: " << loop);
    LOG("Duration of whole loop: "
         << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "ns");
    LOG("Duration in ns: " << duration << "ns");
    LOG("Duration: " << goodDuration << " " << unit);
    return 0;
}



