#include "Boruvka.h"
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <sort/QuickSort.h>
#include <log/Log.h>

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
    LOG("Merged: " << left.size() << " + " << right.size() << " = " << merged.size());
    return merged;
}

Graph::Vertex Boruvka::findRoot(const Graph::Vertex &vertex) {
    if (m_componentInfos[vertex].root == vertex)
        return vertex;
    auto root = findRoot(m_componentInfos[vertex].root);
    m_componentInfos[vertex].root = root;
    return root;
}

void Boruvka::findUnion(Graph::Vertex beginRoot, Graph::Vertex endRoot, const Graph::Edge &edge) {
    LOG("Boruvka: union on " << beginRoot << " and " << endRoot);
    m_componentInfos[endRoot].root = beginRoot;
    m_componentInfos[edge.begin()].root = beginRoot;
    m_componentInfos[edge.end()].root = beginRoot;

    m_componentInfos[beginRoot].edges = merge(m_componentInfos[beginRoot].edges,
                                              m_componentInfos[endRoot].edges);
    m_componentInfos[endRoot].edges.clear();

    auto splitIt = std::remove_if(m_components.begin(), m_components.end(),
            [&endRoot](const Graph::Vertex &vertex) {
                return vertex == endRoot;
    });
    m_components.erase(splitIt, m_components.end());
}

void Boruvka::setGraph(const Graph &graph) {
    LOG("Boruvka: setGraph");
    m_components.clear();
    m_componentInfos.clear();
    m_componentInfos.reserve(graph.getVertexAmount());
    m_mstEdges.clear();
    m_mstEdges.reserve(graph.getVertexAmount() - 1);

    for(unsigned i = 0; i < graph.getVertexAmount(); ++i) {
        m_componentInfos.push_back(ComponentInfo{Graph::Vertex(i),
                                                 Vector<Graph::Edge>()});
        m_components.push_back(Graph::Vertex(i));
    }
    for (auto &edgeList : graph.getNeighbourhoodList()) {
        for (auto &edge : edgeList) {
            m_componentInfos[edge.begin()].edges.push_back(edge);
        }
    }
}
void Boruvka::prepareMST() {
    LOG("Boruvka: prepareMST");
    //Init data
    for (auto &component : m_componentInfos) {
        GIS::QuickSort::sort(component.edges.begin(), component.edges.end(),
                [](const Graph::Edge& left, const Graph::Edge &right) {
                    return left.value() < right.value();
        });
    }

    //Algorithm itself
    while (m_components.size() > 1) {
        LOG("Boruvka: Got " << m_components.size() << " components");
        Graph::Vertex componentRoot;
        Graph::Vertex endRoot;
        Graph::Edge minEdge(0, 0, std::numeric_limits<Graph::Value>::max());
        for (auto &component : m_components) {
            for (auto &edge : m_componentInfos[component].edges) {
                LOG("Boruvka: Checking edge (" << edge.begin() << ", " << edge.end() << ", "
                        << edge.value() << ") for component: " << component);
                Graph::Vertex root = findRoot(edge.end());
                if (component != root && edge.value() < minEdge.value()) {
                    componentRoot = component;
                    endRoot = root;
                    minEdge = edge;
                    break;
                }
            }
        }
        std::cout << "Boruvka: ComponentInfos (";
        for (unsigned i = 0; i < m_componentInfos.size(); ++i) {
            std::cout << "[i: " << i << ", root: " << m_componentInfos[i].root << " , edges: " <<
                      m_componentInfos[i].edges.size() << " ], ";
        }
        std::cout << ")" << std::endl;
        if (minEdge.value() == std::numeric_limits<Graph::Value>::max()) {
            LOG("Minimum edge not set! Graph is not connected");
            throw std::runtime_error("Graph not connected!");
        }

        findUnion(componentRoot, endRoot, minEdge);
        LOG("Boruvka: Adding (" << minEdge.begin() << ", " << minEdge.end() << "," << minEdge.value() << ")");
        LOG("Boruvka: Joining " << componentRoot << " and " << endRoot);
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
