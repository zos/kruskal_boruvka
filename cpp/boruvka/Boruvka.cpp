#include "Boruvka.h"
#include <limits>

namespace GIS {
namespace Algorithms {

typedef GIS::Vector<GIS::Graph::Edge> EdgeVector;

static EdgeVector merge(const EdgeVector &left, const EdgeVector &right) {
    EdgeVector merged;
    merged.reserve(left.size() + right.size());
    auto leftIt = left.begin();
    auto rightIt = right.begin();
    while ( leftIt != left.end() && rightIt != right.end()) {
        if (leftIt->value() < rightIt->value()) {
            merged.push_back(*leftIt);
            ++leftIt;
        } else {
            merged.push_back(*rightIt);
            ++rightIt;
        }
    }
    for(; leftIt != left.end(); ++leftIt) {
        merged.push_back(*leftIt);
    }
    for(; rightIt != right.end(); ++rightIt) {
        merged.push_back(*rightIt);
    }

    return merged;
}

Graph::Vertex Boruvka::findRoot(const Graph::Vertex &vertex) {
    if (m_componentInfos[vertex].root == vertex)
        return vertex;
    auto rootVertex = findRoot(m_componentInfos[vertex].root);
    m_componentInfos[vertex].root = rootVertex;
    return rootVertex;
}

bool Boruvka::findUnion(Graph::Vertex beginRoot, Graph::Vertex endRoot, const Graph::Edge &edge) {
    auto beginId = m_componentInfos[beginRoot].id;
    auto endId = m_componentInfos[endRoot].id;

    if (beginId == endId)
        return true;

    m_componentInfos[endRoot].root = beginRoot;
    m_componentInfos[edge.begin()].root = beginRoot;
    m_componentInfos[edge.end()].root = beginRoot;

    m_componentInfos[endRoot].id = beginId;

    m_components[beginId].edges = merge(m_components[beginId].edges, m_components[endId].edges);
    std::swap(m_components[endId], m_components.back());
    m_components.erase(std::prev(m_components.end()));
    return false;
}

void Boruvka::setGraph(const Graph &graph) {
    m_components.clear();
    m_components.reserve(graph.getVertexAmount());
    m_componentInfos.clear();
    m_componentInfos.reserve(graph.getVertexAmount());
    m_mstEdges.clear();
    m_mstEdges.reserve(graph.getVertexAmount() - 1);

    for (auto &edgeList : graph.getNeighbourhoodList()) {
        for (auto &edge : edgeList) {
            m_components[edge.begin()].edges.push_back(edge);
        }
    }
}
void Boruvka::prepareMST() {
    for (unsigned i = 0; i < m_components.capacity(); i++)
        m_componentInfos.push_back(ComponentInfo(Graph::Vertex(i), i));
    m_componentsAmount = m_components.size();

    for (auto &component : m_components) {
        GIS::QuickSort::sort(component.edges.begin(), component.edges.end(),
                [](const Graph::Edge& left, const Graph::Edge &right) {
                    return left.value() < right.value();
        });
    }

    while (m_components.size() > 1) {
        Graph::Vertex componentRoot;
        Graph::Vertex endRoot;
        Graph::Edge minEdge(0, 0, std::numeric_limits<Graph::Value>::max());
        for (auto &component : m_components) {
            for (auto &edge : component.edges) {
                Graph::Vertex root = findRoot(edge.end());
                if (component.root != root && edge.value() < minEdge.value()) {
                    componentRoot = component.root;
                    endRoot = root;
                    minEdge = edge;
                }
            }
        }
        findUnion(componentRoot, endRoot, minEdge);
        m_mstEdges.push_back(minEdge);
    }

}
Graph Boruvka::getMST() {
    Graph::EdgeSet mstSet;
    for (unsigned i = 0; i < m_mstEdges.size(); ++i)
        mstSet.insert(m_mstEdges[i]);
    return Graph(m_mstEdges.size() + 1, std::move(mstSet));
}

} /* namespace Algorithms */
} /* namespace GIS */
