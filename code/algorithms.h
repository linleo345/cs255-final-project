#include <iostream>
#include <vector>
#include "graph.h"
#include "readFromFile.hpp"
#include <map>

namespace algorithms {
    
    /**
    * BFS does a breadth-first search, starting from the start vertex, and looking for the to_find vertex, on graph g.  The goal
    * of the algorithm is to find the shortest path from one vertex to the other.  The algorithm concludes when to_find is found, 
    * or after exploring the entire connected component that "start" resides in.
    * 
    * @return the path of Vertices from start to to_find
    */
    std::vector<Vertex> BFS(Vertex start, Vertex to_find, const Graph& g);

    /**
    * Dijkstra performs Dijkstra's Algorithm in order to find the single source shortest path from the start vertex to to_find, 
    * on graph g.  This is similar to BFS, however it includes the effect of edge weights, and chooses the path with the smallest
    * edge weight sum, often described as the cost of the path.  The algorithm concludes when to_find is found, or after exploring
    * the entire connected component that "start" resides in.
    * 
    * @return the path of Vertices from start to to_find
    */
    std::vector<Vertex> Dijkstra(Vertex start, Vertex to_find, const Graph& g);

    /**
    * PageRank performs the PageRank algorithm that Google uses to compute which pages you are most likely to visit from a certain page.
    * This uses the assumption that you move directly from one vertex to an adjacent vertex or stay in place on every "move", and uses
    * that to find the most probable vertices to be visiting at any given time.  
    * 
    * @return a map with every Vertex and the probability of being at that vertex in the long run
    */
    std::map<Vertex, long double> PageRank(const Graph &g);
}