#pragma once

#include <containers/Vector.h>
#include <containers/List.h>

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
        Edge(const Edge &other): m_begin(other.m_begin), m_end(other.m_end), m_value(other.m_value){}
        Edge(Edge &&other) : m_begin(other.m_begin), m_end(other.m_end), m_value(other.m_value) {
            other.m_begin = 0;
            other.m_end = 0;
            other.m_value = 0;
        }
        Edge& operator=(const Edge &other) {
            if (this == &other)
                return *this;
            m_begin = other.m_begin;
            m_end = other.m_end;
            m_value = other.m_value;

            return *this;
        }
        Edge& operator=(Edge &&other) {
            if (this == &other)
                return *this;
            m_begin = other.m_begin;
            m_end = other.m_end;
            m_value = other.m_value;

            other.m_begin = 0;
            other.m_end = 0;
            other.m_value = 0;

            return *this;
        }

        // Do not compare values of edges, as we don't want multiple edges between the same
        // pair of vertexes
        bool operator<(const Edge &other) const {
            auto normalizedThis = normalize(*this);
            auto normalizedOther = normalize(other);

            return normalizedThis.begin() < normalizedOther.begin()
                    || (normalizedThis.begin() == normalizedOther.begin()
                            && normalizedThis.end() < normalizedOther.end());
        }

        bool operator==(const Edge &edge) {
            if (begin() != edge.begin())
                return false;
            if (end() != edge.end())
                return false;
            if (value() != edge.value())
                return false;
            return true;
        }

        bool operator!=(const Edge &edge) {
            return !(*this == edge);
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

        static Edge normalize(const Edge &edge) {
            if (edge.begin() < edge.end())
                return edge;
            else
                return Edge(edge.end(), edge.begin(), edge.value());
        }

    private:
        Vertex m_begin;
        Vertex m_end;
        Value m_value;


    };
    typedef std::set<Edge> EdgeSet;
    typedef Vector<List<Edge>> NbhList;
    typedef Vector<Vector<Value> > NbhMap;

    Graph() : m_edgeAmount(0), m_vertexAmount(0) {}
    Graph(std::size_t vertexAmount, std::set<Edge> &&edgeSet);

    Graph(Graph &&other) {
        m_edgeSet = std::move(other.m_edgeSet);
        m_edgeAmount = other.m_edgeAmount;
        m_vertexAmount = other.m_vertexAmount;

        other.m_edgeAmount = 0;
        other.m_vertexAmount = 0;
    }

    Graph& operator=(Graph &&other) {
        if (this == &other)
            return *this;

        m_edgeSet = std::move(other.m_edgeSet);
        m_edgeAmount = other.m_edgeAmount;
        m_vertexAmount = other.m_vertexAmount;

        other.m_edgeAmount = 0;
        other.m_vertexAmount = 0;

        return *this;
    }

    bool operator==(const Graph &other) {
        if (getVertexAmount() != other.getVertexAmount())
            return false;
        if (getEdgeAmount() != other.getEdgeAmount())
            return false;

        auto myNbhList = getNeighbourhoodList();
        auto otherNbhList = other.getNeighbourhoodList();
        for (unsigned i = 0; i < getVertexAmount(); i++) {
            auto myEdgeList = myNbhList[i];
            auto otherEdgeList = otherNbhList[i];
            if (myEdgeList.size() != otherEdgeList.size()) {
                return false;
            }
            auto it1 = myEdgeList.begin();
            auto it2 = otherEdgeList.begin();

            while (it1 != myEdgeList.end()) {
                if (*it1 != *it2)
                    return false;
                ++it1;
                ++it2;
            }
        }
        return true;
    }

    bool operator!=(const Graph &other) {
        return !(*this == other);
    }

    std::size_t getVertexAmount() const;
    long int getEdgeAmount() const;
    EdgeSet getEdgeSet() const;
    NbhList getNeighbourhoodList() const;
    NbhMap getNeighbourhoodMap() const;
    virtual ~Graph();
private:
    EdgeSet m_edgeSet;
    long int m_edgeAmount;
    long int m_vertexAmount;
};

} /* namespace GIS */
