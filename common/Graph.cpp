#include "Graph.h"
#include "Log.h"

namespace GIS {

Graph::Graph(std::size_t vertexAmount, const std::set<Edge> &edgeSet) {
    m_edgeAmount = 0;
    m_list.resize(vertexAmount);
    for (const Graph::Edge &edge : edgeSet) {
        m_list[edge.begin()].push_back(edge);
    }
    m_edgeAmount = edgeSet.size() / 2;
}

std::size_t Graph::getVertexAmount() const {
    return m_list.size();
}

long int Graph::getEdgeAmount() const {
    return m_edgeAmount;
}

Graph::NbhList Graph::getNeighbourhoodList() const {
    return m_list;

}
Graph::NbhMap Graph::getNeighbourhoodMap() const {
    NbhMap map;
    // Reserve every axis with amount of Vertexes in Graph
    map.reserve(m_list.size());
    for (auto & vertexRow : map) {
        vertexRow.reserve(m_list.size());
    }

    for (unsigned int i = 0; i < m_list.size(); i++) {
        for (const auto &edge : m_list[i]) {
            // Reminder, that edge.begin() == i
            map[i][edge.end()] = edge.value();
        }
    }
    return map;
}
Graph::~Graph() {

}

} /* namespace GIS */
