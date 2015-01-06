#include <kruskal/Kruskal.h>
#include <serializer/GraphPrinter.h>
#include <serializer/GraphSerialization.h>
#include <log/Log.h>

#include <assert.h>
#include <fstream>
using namespace GIS;

const std::string file = "graph10v_20e.txt";

// Should be parameterized:
// -f file path
// -o output path
// -r resolution

int main(int argc, char **argv) {
    Graph graph;
    std::string filename;
    if (argc == 2) {
        filename = argv[1];
    } else {
        filename = file;
    }
    std::ifstream fin(filename);
    assert(fin && "Test needs a file!");
    fin >> graph;
    printGraph(graph);

    Algorithms::Kruskal kruskal;
    kruskal.setGraph(graph);
    kruskal.prepareMST();
    auto mst = kruskal.getMST();

    printGraph(mst);

    if (mst.getEdgeAmount() + 1 != (long int)mst.getVertexAmount()) {
        LOG("Wrong amount of edges!");
        return -1;
    }

    LOG("SUCCESS!");
    return 0;
}




