#pragma once

#include <vector>
#include <list>
#include <set>

namespace GIS {

class Graph {
public:
    typedef int Value;
    typedef std::size_t Vertex;

    class Edge {
    public:
        Edge() : m_begin(0), m_end(0), m_value(0) {}
        Edge(Vertex b, Vertex e, Value v) : m_begin(b), m_end(e), m_value(v) {};
        // Do not compare values of edges, as we don't want multiple edges between the same
        // pair of vertexes
        bool operator<(const GIS::Graph::Edge &other) const {
            return begin() < other.begin()
                    || (begin() == other.begin() && end() < other.end());
        }

        Vertex begin() const {
            return m_begin;
        }
        Vertex end() const {
            return m_end;
        }
        Vertex value() const {
            return m_value;
        }
    private:
        Vertex m_begin;
        Vertex m_end;
        Value m_value;
    };

    typedef std::vector<std::list<Edge>> NbhList;
    typedef std::vector<std::vector<Value> > NbhMap;

    Graph() : m_edgeAmount(0) {}
    Graph(std::size_t vertexAmount, const std::set<Edge> &edgeSet);
    std::size_t getVertexAmount() const;
    long int getEdgeAmount() const;
    NbhList getNeighbourhoodList() const;
    NbhMap getNeighbourhoodMap() const;
    virtual ~Graph();
private:
    NbhList m_list;
    long int m_edgeAmount;
};

} /* namespace GIS */
