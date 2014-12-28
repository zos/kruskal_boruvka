#include "Kruskal.h"
#include <log/Log.h>
#include <containers/Vector.h>

#include <algorithm>

namespace GIS {

namespace Algorithms {

namespace Kruskal {

Graph::Vertex findRoot(Vector<long int> &integrals, const Graph::Vertex &vertex) {
    if (integrals[vertex] == -1)
        return vertex;
    auto rootVertex = findRoot(integrals, integrals[vertex]);
    integrals[vertex] = rootVertex;
    return rootVertex;
}

bool findUnion(Vector<long int> &integrals, const Graph::Edge &edge) {
    auto root1 = findRoot(integrals, edge.begin());
    auto root2 = findRoot(integrals, edge.end());

    if (root1 != root2) {
        integrals[root1] = root2;
        return true;
    }
    return false;
}

Graph getMST(const Graph &graph) {
    Vector<long int> integrals;
    Graph::EdgeSet mst;
    auto edgeSet = graph.getEdgeSet();
    integrals.resize(graph.getVertexAmount(), -1);
    std::cout << "Kruskal" << std::endl;

    Vector<Graph::Edge> edgesSorted;
    edgesSorted.reserve(edgeSet.size());
    for(auto &edge : edgeSet) {
        edgesSorted.push_back(Graph::Edge::normalize(edge));
    }

    std::sort(edgesSorted.begin(), edgesSorted.end(),
            [] (const Graph::Edge &left, const Graph::Edge &right) {
                return left.value() < right.value();});
    // Till here, there should be an outside function prepare(),
    // so whole preparation isn't profiled

    for(auto &edge : edgesSorted) {
        std::cout << "Integrals: ";
        for(unsigned int i = 0; i < integrals.size(); i++)
            std::cout << integrals[i] << ",";
        std::cout << std::endl;
        LOG("Kruskal: Checking edge (" << edge.begin() << "," << edge.end() << "," << edge.value() << ")")
        if (findUnion(integrals, edge)) {
            LOG("Kruskal: Added");
            mst.insert(edge);
        }
    }

    // This probably also should be done outside
    return Graph(graph.getVertexAmount(), std::move(mst));
}

} // namespace Kruskal
} // namespace Algorithms
} // namespace GIS




