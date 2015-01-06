#include "Kruskal.h"
#include <sort/QuickSort.h>
#include <log/Log.h>
#include <containers/Vector.h>

#include <algorithm>

namespace GIS {
namespace Algorithms {

Graph::Vertex Kruskal::findRoot(const Graph::Vertex &vertex) {
    if (m_integrals[vertex] == -1)
        return vertex;
    auto rootVertex = findRoot(m_integrals[vertex]);
    m_integrals[vertex] = rootVertex;
    return rootVertex;
}

bool Kruskal::findUnion(const Graph::Edge &edge) {
    auto root1 = findRoot(edge.begin());
    auto root2 = findRoot(edge.end());

    if (root1 != root2) {
        LOG("Kruskal: Joining " << root1 << " and " << root2);
        m_integrals[root1] = root2;
        return true;
    }
    return false;
}

void Kruskal::prepareMST() {
    LOGI("Kruskal: prepareMST");
    m_mstEdges.clear();
    m_mstEdges.reserve(m_vertexAmount - 1);

    GIS::QuickSort::sort(m_edges.begin(), m_edges.end(),
            [] (const Graph::Edge &left, const Graph::Edge &right) {
                return left.value() < right.value();});

    for(auto &edge : m_edges) {
        LOG("Kruskal: Checking edge (" << edge.begin() << "," << edge.end() << "," << edge.value() << ")")
        if (findUnion(edge)) {
            LOG("Kruskal: Adding (" << edge.begin() << ", " << edge.end() << ", " << edge.value() << ")");
            m_mstEdges.push_back(edge);
            if (m_mstEdges.size() == static_cast<long unsigned>(m_vertexAmount - 1)) {
                LOGI("Kruskal: MST found, no further search needed");
                break;
            }
        }

    }
}

Graph Kruskal::getMST() {
    LOGI("Kruskal: getMST");
    Graph::EdgeSet mstSet;
    for (unsigned i = 0; i < m_mstEdges.size(); ++i)
        mstSet.insert(m_mstEdges[i]);
    return Graph(m_vertexAmount, std::move(mstSet));
}

} // namespace Algorithms
} // namespace GIS




