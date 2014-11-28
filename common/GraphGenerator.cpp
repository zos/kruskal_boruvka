#include "GraphGenerator.h"
#include "Log.h"
#include <random>

namespace GIS {

static void DFS(std::vector<bool> &discovered, const Graph::NbhList &list, Graph::Vertex v) {
    discovered[v] = true;
    LOG("DFS: In vertex" << v);
    for (auto &edge : list[v]) {
        if (!discovered[edge.end()]) {
            DFS(discovered, list, edge.end());
        }
    }
}


static Graph::Edge generateRandomEdge(std::size_t maxVertex) {
    //TODO : settable from outside
    Graph::Value maxValue = maxVertex * (maxVertex - 1);
    static std::default_random_engine re;
    static std::uniform_int_distribution<int> dVertex(0, maxVertex - 1);
    static std::uniform_int_distribution<int> dValue(1, maxValue);

    Graph::Vertex from = 0, to = 0;
    while(from == to) {
        from = dVertex(re);
        to = dVertex(re);
    }
    Graph::Value value = dValue(re);
    LOG("Generated edge(" << from << ", " << to << ", " << value << ")");
    return Graph::Edge(from, to ,value);
}

static std::set<Graph::Edge> generateEdgeSet(long int edgeAmount, std::size_t maxVertex) {
    std::set<Graph::Edge> edgeSet;
    do {
        Graph::Edge edge = generateRandomEdge(maxVertex);
        Graph::Edge edgeReverse(edge.end(), edge.begin(), edge.value());
        edgeSet.insert(edge);
        edgeSet.insert(edgeReverse);
    } while (edgeSet.size() < 2 * edgeAmount);
    return edgeSet;
}

void GraphGenerator::setVertexAmount(std::size_t vertexAmount){
    m_vertexAmount = vertexAmount;
}
void GraphGenerator::setEdgeAmount(std::size_t edgeAmount){

    m_edgeAmount = edgeAmount;
}

Graph GraphGenerator::generate() {
    if (m_vertexAmount <= 0)
        throw InvalidParameterException("Amount of vertex should be > 0");
    if (m_edgeAmount <= 0)
        throw InvalidParameterException("Amount of edges should be > 0");

    if (m_edgeAmount > (m_vertexAmount * (m_vertexAmount - 1) / 2))
        throw InvalidParameterException("Too many edges set");

    if (m_edgeAmount < m_vertexAmount - 1)
        throw InvalidParameterException("Not enough edges set");

    std::set<Graph::Edge> edgeSet;
    auto tries = m_tries;

    do {
        LOG("Try " << m_tries - tries + 1 << "/" << m_tries)
        edgeSet = generateEdgeSet(m_edgeAmount, m_vertexAmount);
        LOG("Got " << edgeSet.size() << " double edges");
        tries--;
    } while (!isConnected(Graph(m_vertexAmount, edgeSet)) && tries);

    if (tries == 0) {
        throw GraphNotConnectedException();
    }
    return Graph(m_vertexAmount, edgeSet);
}

bool GraphGenerator::isConnected(const Graph& graph) {
    //Hello DFS!
    LOG("isConnected");
    auto list = graph.getNeighbourhoodList();
    LOG("Got graph with " << graph.getVertexAmount() << " vertexes and "
            << graph.getEdgeAmount() << " edges");
    std::vector<bool> discovered(list.size(), false);
    DFS(discovered, list, Graph::Vertex(0));
    int discoveredAmount = 0;
    for(int i = 0; i < discovered.size(); i++) {
        if (discovered[i])
            discoveredAmount++;
    }
    if (discoveredAmount == list.size()){
        LOG("Graph is connected");
        return true;
    }
    LOG("Graph not connected");
    return false;
}

} /* namespace GIS */
