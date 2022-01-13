#include <iostream>
#include <fstream>
#include "read.h"
#include "algorithms.h"

int main(int argv, char** argc) {

    std::cout << "make main works!" << std::endl;

    /**
     * Data can be read into graphs using the readData function from the readdata namespace
     * Files should be formatted as 2 entries per line, separated by a space. The left entry is the vertex an edge will come from, and the right is what it will point to
     * Like this:
     * 1 2
     * 3 4
     * 5 6
     * 7 8
     * This will create a graph with 8 vertices such that 1->2, 3->4, 5->6, 7->8.
     * The resulting graph can be used to pass into the methods in the algorithm namespace
     * 
     * The readdata::readData function takes the filepath as a parameter, and returns an instance of the Graph class.
     */
    Graph g = readdata::readData("../data/twitter_combined.txt");

    std::vector<std::vector<Vertex>> bfs;
    std::vector<std::vector<Vertex>> dij;

    /**
     * The algorithms::BFS function takes 3 parameters:
     * @param std::string: this is the starting vertex, or the beginning of the traversal
     * @param std::string: this is the second parameter, which is the point you will try to find via BFS traversal
     * @param Graph: This is the graph to be traversed using a BFS.
     * @return std::vector<Vertex>: The traversal, in order, as a sequence of vertices
     * 
     * This function can be called as follows:
     */
    bfs.push_back(algorithms::BFS("35148062", "31331740", g));
    bfs.push_back(algorithms::BFS("204317520", "56860418", g));
    bfs.push_back(algorithms::BFS("288485704", "22462180", g));
    bfs.push_back(algorithms::BFS("149538028", "134940306", g));
    bfs.push_back(algorithms::BFS("279787626", "22462180", g));

    /**
     * The algorithms::Dijkstra function takes 3 parameters:
     * @param std::string: this is the starting vertex, or the beginning of the traversal
     * @param std::string: this is the second parameter, which is the point you will try to find via BFS traversal
     * @param Graph: This is the graph to be traversed using Dijkstra's algorithm.
     * @return std::vector<Vertex>: The traversal, in order, as a sequence of vertices
     * 
     * This function can be called as follows:
     */
    dij.push_back(algorithms::Dijkstra("35148062", "31331740", g));
    dij.push_back(algorithms::Dijkstra("204317520", "56860418", g));
    dij.push_back(algorithms::Dijkstra("288485704", "22462180", g));
    dij.push_back(algorithms::Dijkstra("149538028", "134940306", g));
    dij.push_back(algorithms::Dijkstra("279787626", "22462180", g));

    std::cout << std::endl;


    std::cout << "BFS traversals" << std::endl << std::endl;
    for(size_t i = 0; i < bfs.size(); i++) {
        for(auto v : bfs[i]) {
            std::cout << v << " -> ";
        }
        std::cout << " end ";
        std::cout << " with path length " << bfs[i].size();
        std::cout << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Dijkstra traversals" << std::endl << std::endl;
    for(size_t i = 0; i < dij.size(); i++) {
        for(auto v : dij[i]) {
            std::cout << v << " -> ";
        }
        std::cout << " end "; 
        std::cout << " with path length " << dij[i].size();
        std::cout << std::endl;
    }

    /**
     * The PageRank algorithm takes the graph, g, and returns an std::map<Vertex, long double>
     * This uses the PageRank algorithm created by Google to rank accounts based on clicks/views/popularity
     * The resulting map can be interpreted as a map of vertices to their respective probabilities of long term viewership based on the PageRank algorithm.
     * It should be noted that due to the size of the twitter data, PageRank is not able to run. Based on standard computer hardware, the max it can take in is a file about 10000 lines long (10000 edges)
     * As a result, any input file should be shortened to 10000 lines.
     */
    auto pageRank = algorithms::PageRank(g);
    std::ofstream file;
    file.open("pageRank.txt");
    for (auto pair : pageRank) {
        file << pair.first << " with probability: " << pair.second << "\n";
    }

    std::cout << std::endl << "pageRank complete: see pageRank.txt";

    return 0;
}