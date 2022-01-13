#include "read.h"
#include "graph.h"
#include <queue>
#include <map>
#include "readFromFile.hpp"

Graph readdata::readData(std::string filepath) {
    std::vector<std::pair<Vertex, Vertex>> data = file_to_vector(filepath);

    Graph g(true, true);

    unsigned long long i = 0;
    for (const auto& d : data) {
        //the graph will overwrite an vertex with the same string if you try to add it in, so to avoid losing other edges
        //we have to check to make sure the vertex does not exist first.
        if (!g.vertexExists(d.first)) {
            g.insertVertex(d.first);
        }

        if (!g.vertexExists(d.second)) {
            g.insertVertex(d.second);
        }
        
        g.insertEdge(d.first, d.second);

        g.setEdgeLabel(d.first, d.second, std::to_string(i++));
    }

    for(auto& edge: g.getEdges()) {
        const auto& srcVertices = g.getAdjacent(edge.source);
        const auto& destVertices = g.getAdjacent(edge.dest);
        //Each edge is weighted with the difference between the number of followed accounts of each account.
        g.setEdgeWeight(edge.source, edge.dest, std::abs(static_cast<int>(srcVertices.size()) - static_cast<int>(destVertices.size())));
    }
    
    return g;
}
