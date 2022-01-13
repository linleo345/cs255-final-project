#include <iostream>
#include <vector>
#include "graph.h"
#include "readFromFile.hpp"
#include <map>

namespace readdata {
    /**
     * This function takes a filepath and calls file_to_vector on it, turning each line into a pair of vertices (strings)
     * Those vertices are then inserted into a directed graph with the first vertex connected to the second vertex.
     */
    Graph readData(std::string filepath);
}
