#pragma once

#include <containers/Vector.h>
#include <graph/Graph.h>
#include <log/Log.h>

namespace GIS {
namespace Algorithms {
class Kruskal {
public:
    void setGraph(const Graph &graph) {
        LOGI("Kruskal: setGraph");
        auto edgeSet = graph.getEdgeSet();
        m_integrals.clear();
        m_vertexAmount = graph.getVertexAmount();
        m_integrals.resize(graph.getVertexAmount(), -1);

        m_edges.clear();
        m_edges.reserve(edgeSet.size());
        for(auto &edge : edgeSet) {
            m_edges.push_back(Graph::Edge::normalize(edge));
        }
    }
    void prepareMST();
    Graph getMST();
private:
    Graph::Vertex findRoot(const Graph::Vertex &vertex);
    bool findUnion(const Graph::Edge &edge);

    Vector<Graph::Edge> m_edges;
    Vector<Graph::Edge> m_mstEdges;
    Vector<long int> m_integrals;
    long int m_vertexAmount;
};

}
}
