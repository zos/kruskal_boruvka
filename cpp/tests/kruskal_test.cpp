#include <kruskal/Kruskal.h>
#include <serializer/GraphPrinter.h>
#include <serializer/GraphSerialization.h>
#include <fstream>
#include <log/Log.h>

using namespace GIS;

const std::string file = "graph10v_20e.txt";

// Should be parametrized:
// -f file path
// -o output path
// -r resolution

int main() {
    Graph graph;
    std::ifstream fin(file);
    fin >> graph;
    printGraph(graph);

    auto mst = Algorithms::Kruskal::getMST(graph);

    printGraph(mst);

    if (mst.getEdgeAmount() + 1 != (long int)mst.getVertexAmount()) {
        LOG("Wrong amount of edges!");
        return -1;
    }
    return 0;
}




