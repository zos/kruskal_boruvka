#pragma once

#include <Graph.h>
#include <exception>
#include <string>

namespace GIS {

class GraphGenerator {
public:
    class InvalidParameterException : public std::exception {
    public:
        InvalidParameterException(const std::string &why) : m_why(why) {}
        virtual ~InvalidParameterException() throw() {}

        /** Returns a C-style character string describing the general cause
         *  of the current error.  */
        virtual const char* what() const throw() {
            std::string s("InvalidParameterException: ");
            s += m_why.c_str();
            return s.c_str();
        }
    private:
        std::string m_why;
    };

    class GraphNotConnectedException : public std::exception {
    public:
        GraphNotConnectedException() {}
        ~GraphNotConnectedException() throw() {}

        const char* what() const throw() {
            return "GraphNotConnectedException";
        }
    };

    GraphGenerator() : m_vertexAmount(0), m_edgeAmount(0), m_tries(0) {}

    void setFile(const std::string &file) { m_file = file; }
    void setVertexAmount(std::size_t vertexAmount);
    void setEdgeAmount(std::size_t edgeAmount);
    void setTries(int tries) { m_tries = tries; }

    Graph generate();

private:
    bool isConnected(const Graph &graph);
    void saveToFile(const Graph &graph);

    std::string m_file;
    std::size_t m_vertexAmount;
    std::size_t m_edgeAmount;
    int m_tries;
};

} /* namespace GIS */

