#pragma once
#include <fstream>
#include <graph/Graph.h>

//TODO : Describe the format of serialization

//Serialize to ostream
std::ostream &operator<<(std::ostream &os, const GIS::Graph &graph);

//Deserialize from istream
std::istream &operator >>(std::istream &is, GIS::Graph &graph);
