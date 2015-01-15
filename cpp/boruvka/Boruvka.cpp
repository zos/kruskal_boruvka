#include "Boruvka.h"
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <sort/QuickSort.h>
#include <log/Log.h>
#include <assert.h>

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
    auto root = findRoot(m_componentInfos[vertex].root);
    m_componentInfos[vertex].root = root;
    return root;
}

void Boruvka::findUnion(Graph::Vertex beginRoot, Graph::Vertex endRoot, const Graph::Edge &edge) {
    LOGI("Boruvka: union on " << beginRoot << " and " << endRoot);
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
    LOGI("Boruvka: setGraph");

    m_vertexAmount = graph.getVertexAmount();
    m_graphEdges = graph.getNeighbourhoodList();
}
void Boruvka::prepareMST() {
    LOGI("Boruvka: prepareMST");
    //Init data
    m_mstEdges.clear();
    m_mstEdges.reserve(m_vertexAmount - 1);

    m_components.clear();
    m_componentInfos.clear();
    m_componentInfos.reserve(m_vertexAmount);
    for(unsigned i = 0; i < m_vertexAmount; ++i) {
        m_componentInfos.push_back(ComponentInfo{Graph::Vertex(i),
                                                 Vector<Graph::Edge>()});
        m_components.push_back(Graph::Vertex(i));
    }

    //Copy edges, as we will be deleting those, which would create cycles
    for (auto &edgeList : m_graphEdges) {
        for (auto &edge : edgeList) {
            m_componentInfos[edge.begin()].edges.push_back(edge);
        }
    }

    //Sort edges ordering by value
    for (auto &component : m_componentInfos) {
        GIS::QuickSort::sort(component.edges.begin(), component.edges.end(),
                [](const Graph::Edge& left, const Graph::Edge &right) {
                    return left.value() < right.value();
        });
    }

    //Algorithm itself
    while (m_components.size() > 1) {
        LOGD("Boruvka: Got " << m_components.size() << " components");
        Graph::Vertex componentRoot;
        Graph::Vertex endRoot;
        Graph::Edge minEdge(0, 0, std::numeric_limits<Graph::Value>::max());

        for (auto &component : m_components) {
            //this is NOT optimal
            //delete cycle edges, so they won't be checked more than once
            auto &edges = m_componentInfos[component].edges;

            //take the first one
            for (int i = 0; i < 1; i++) {
                LOGD("Boruvka: Checking edge (" << edges[i].begin() << ", " << edges[i].end() << ", "
                        << edges[i].value() << ") for component: " << component);

                Graph::Vertex root = findRoot(edges[i].end());
                if (edges[i].value() < minEdge.value() && component != root) {
                    LOGD("Boruvka: saving minEdge (" << edges[i].begin() << ", " << edges[i].end() << ", " << edges[i].value() << ")");
                    componentRoot = findRoot(component);
                    endRoot = root;
                    minEdge = edges[i];
                    break;
                }
            }
        }

        if (minEdge.value() == std::numeric_limits<Graph::Value>::max()) {
            LOGE("Minimum edge not set! Graph is not connected");
            throw std::runtime_error("Graph not connected!");
        }


        findUnion(componentRoot, endRoot, minEdge);

        auto splitIt = std::remove_if(m_componentInfos[componentRoot].edges.begin(),
	                                  m_componentInfos[componentRoot].edges.end(),
                                      [&componentRoot, this](const Graph::Edge &edge) {
                                         if (componentRoot == this->findRoot(edge.end())) {
                                             LOGD("Deleting (" << edge.begin() << ", " << edge.end() << ")");
                                             return true;
                                         }
		                                 return false;
                                     });
		m_componentInfos[componentRoot].edges.erase(splitIt, m_componentInfos[componentRoot].edges.end());
        LOGI("Boruvka: Adding (" << minEdge.begin() << ", " << minEdge.end() << "," << minEdge.value() << ")");
        LOGD("Boruvka: Joining " << componentRoot << " and " << endRoot);
        m_mstEdges.push_back(minEdge);
    }
    LOGI("Boruvka: MST found");

}
Graph Boruvka::getMST() {
    LOGI("Boruvka: getMST");
    Graph::EdgeSet mstSet;
    for (unsigned i = 0; i < m_mstEdges.size(); ++i)
        mstSet.insert(m_mstEdges[i]);
    return Graph(m_mstEdges.size() + 1, std::move(mstSet));
}

} /* namespace Algorithms */
} /* namespace GIS */
