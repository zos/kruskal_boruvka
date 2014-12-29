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
    struct Component {
        Graph::Vertex root;
        Vector<Graph::Edge> edges;
    };
    struct ComponentInfo {
        Graph::Vertex root;
        std::size_t id;
    };
    Graph::Vertex findRoot(const Graph::Vertex &vertex);
    bool findUnion(Graph::Vertex beginRoot, Graph::Vertex endRoot, const Graph::Edge &edge);
    long int m_componentsAmount;
    Vector<ComponentInfo> m_componentInfos;
    Vector<Component> m_components;
    Vector<Graph::Edge> m_mstEdges;
};

} /* namespace Algorithms */
} /* namespace GIS */

