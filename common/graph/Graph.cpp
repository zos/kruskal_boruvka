#include "Graph.h"
#include <log/Log.h>

namespace GIS {

Graph::Graph(std::size_t vertexAmount, std::set<Edge> &&edgeSet) {

    m_edgeAmount = edgeSet.size();
    m_vertexAmount = vertexAmount;
    m_edgeSet = std::move(edgeSet);
}

std::size_t Graph::getVertexAmount() const {
    return m_vertexAmount;
}

long int Graph::getEdgeAmount() const {
    return m_edgeAmount;
}

Graph::EdgeSet Graph::getEdgeSet() const {
    return m_edgeSet;
}

Graph::NbhList Graph::getNeighbourhoodList() const {
    NbhList list;
    list.resize(m_vertexAmount);
    for (const Graph::Edge &edge : m_edgeSet) {
        list[edge.begin()].push_back(edge);
        list[edge.end()].push_back(Edge(edge.end(), edge.begin(), edge.value()));
    }
    return list;

}
Graph::NbhMap Graph::getNeighbourhoodMap() const {
    NbhMap map;
    // Reserve every axis with amount of Vertexes in Graph
    map.resize(m_vertexAmount);
    for (auto & vertexRow : map) {
        vertexRow.resize(m_vertexAmount);
    }

    for (auto &edge : m_edgeSet) {
        map[edge.begin()][edge.begin()] = edge.value();
        map[edge.end()][edge.begin()] = edge.value();
    }
    return map;
}
Graph::~Graph() {

}

} /* namespace GIS */
