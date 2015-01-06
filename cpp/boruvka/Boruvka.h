#pragma once

#include <graph/Graph.h>
#include <containers/Vector.h>

#include <list>

namespace GIS {
namespace Algorithms {

class Boruvka {
public:
    void setGraph(const Graph &graph);
    void prepareMST();
    Graph getMST();
private:
    struct ComponentInfo {
        Graph::Vertex root;
        Vector<Graph::Edge> edges;
    };

    Graph::Vertex findRoot(const Graph::Vertex &vertex);
    void findUnion(Graph::Vertex beginRoot, Graph::Vertex endRoot, const Graph::Edge &edge);
    Vector<ComponentInfo> m_componentInfos;
    List<Graph::Vertex> m_components;
    Vector<Graph::Edge> m_mstEdges;
};

} /* namespace Algorithms */
} /* namespace GIS */

