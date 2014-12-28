#include "GraphSerialization.h"
#include <log/Log.h>

#include <stdexcept>

typedef std::runtime_error DeserializationException;

std::ostream &operator<<(std::ostream &os, const GIS::Graph &graph) {
    const auto &nbhlist = graph.getNeighbourhoodList();
    auto vertexAmount = graph.getVertexAmount();

    os << vertexAmount << std::endl;

    for (std::size_t i = 0; i < vertexAmount; i++) {
        os << nbhlist[i].size();
        for (auto &edge : nbhlist[i]) {
            os << " " << edge.end();
            os << " " << edge.value();
        }
        os << std::endl;
    }

    return os;
}

std::istream &operator >>(std::istream &is, GIS::Graph &graph) {
    std::size_t vertexAmount;
    std::set<GIS::Graph::Edge> edges;
    is.exceptions(std::istream::failbit | std::istream::badbit | std::istream::eofbit);
    try {
        is >> vertexAmount;
        LOG("Getting graph of " << vertexAmount << " vertexes.");

        GIS::Graph::Vertex begin;
        GIS::Graph::Vertex end;
        GIS::Graph::Value value;
        for (std::size_t i = 0; i < vertexAmount; i++) {
            begin = i;
            std::size_t vertexDegree;
            is >> vertexDegree;
            for (std::size_t j = 0; j < vertexDegree; j++) {
                is >> end;
                is >> value;
                edges.insert(GIS::Graph::Edge(begin, end, value));
                LOG("Got edge : (" << i << ", " << end << ", " << value << ")");
            }
        }
        LOG("Got " << edges.size() << " edges");
        graph = GIS::Graph(vertexAmount, std::move(edges));
    } catch (std::ios_base::failure &e) {
        LOG("Deserialization failed with: " << e.what());
    } catch (std::exception &e) {
        LOG("Deserialization failed with: " << e.what());
    } catch (...) {
        LOG("This should not have happened...");
    }

    is.exceptions(std::istream::goodbit);
    return is;
}

