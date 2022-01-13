#include "algorithms.h"
#include <queue>
#include <map>



std::vector<Vertex> algorithms::BFS(Vertex start, Vertex to_find, const Graph& g) {
    std::vector<Vertex> path;
    std::queue<Vertex> BFS;
    std::map<Vertex, bool> visited;
    std::map<Vertex, Vertex> order;
    //initializing the maps to what we need
    order.insert(std::pair<Vertex, Vertex>(start, ""));
    const auto& vertices = g.getVertices();
    for (auto v : vertices) {
        visited.insert(std::pair<Vertex, bool>(v, false));
    }

    BFS.push(start);

    visited[start] = true;
    
    //BFS only empties completely if to_find is not found in the same connected component as start
    while (!BFS.empty()) {
        Vertex v = BFS.front();
        visited[v] = true;
        BFS.pop();

        //ends early if the correct vertex is found
        if (v == to_find) {
            break;
        }

        const auto& adjacent = g.getAdjacent(v);
        //adds in all adjacent vertices that have not been looked at yet
        for (Vertex vertex : adjacent) {
            if (!visited.at(vertex)) {
                BFS.push(vertex);
                order.insert(std::pair<Vertex, Vertex>(vertex, v));
            }
        }
    }

    //backtracks through the vertices to find the path from start to to_find
    Vertex curr = to_find;
    while (curr != "") {
        path.push_back(curr);
        curr = order[curr];
    }

    //path will be in reverse after backtrack, so we need to reverse the path vector to be correct
    std::reverse(path.begin(), path.end());

    return path;

}

std::vector<Vertex> algorithms::Dijkstra(Vertex start, Vertex to_find, const Graph& g) {
    std::map<Vertex, int> distances;
    std::map<Vertex, Vertex> previous;
    std::queue<Vertex> q;
    std::map<Vertex, bool> visited;
    const auto& vertices = g.getVertices();

    //initializes the maps and priority_queues with all the vertices and the default values
    for (const Vertex& v : vertices) {
        distances[v] = INT_MAX;
        previous[v] = "";
        visited[v] = false;
    }

    distances[start] = 0;//queue must start with the first node in place, and the dstiance from the first node to itself is 0
    q.push(start);
    while (!q.empty()) {
        Vertex v = q.front();
        q.pop(); //checks the first vertex in the queue and pops it out
        visited[v] = true;
        if (v == to_find) {
            break;
        }
        const auto& neighbors = g.getAdjacent(v);
        //We want to add in all adjacent vertices that have not been looked at yet.
        for (Vertex neighbor : neighbors) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                //if the cost of getting to the current node plus the cost of the edge between current and neighbor node is smaller than
                //what the cost of getting to the neighbor is currently stored as (default is INT_MAX).  If it is smaller, 
                //the neighbor distance is replaced and the predecessor of the neighbor becomes our current node
                int neighbor_dist = distances[v] + g.getEdgeWeight(v, neighbor);
                if (neighbor_dist < distances[neighbor]) {
                    distances[neighbor] = neighbor_dist;
                    previous[neighbor] = v;
                }
            }
        }
    }

    //backtrack using the "previous" map to find the path from the start to end vertices, 
    //then reverse it to be in the correct direction
    Vertex curr = to_find;
    vector<Vertex> path;

    while (curr != "") {
        path.push_back(curr);
        curr = previous[curr];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::map<Vertex, long double> algorithms::PageRank(const Graph& g) {
    std::map<Vertex, long double> long_run_probs;
    //Each value in the "matrix" will hold the probability of going from the vertex defining that 
    //column to the vertex defining that row
    //E.G: matrix[10][94] is the probability of moving from vertex 10 to vertex 94
    std::map<Vertex, std::map<Vertex, long double>> matrix;
    const auto& vertices = g.getVertices();

    for (const Vertex& v : vertices) {
        //Start all values off in the matrix as 0, any nonzero value will be changed
        for (const Vertex& u : vertices) {
            matrix[v][u] = 0.0;
        }
        //for each vertex, it can move to any adjacent vertex or stay where it is, so the probability for 
        //every possible move from the vertex is 1/(the amount of adjacent vertices + 1)
        const auto& adjacent = g.getAdjacent(v);
        for (const Vertex& a : adjacent) {
            matrix[v][a] = 1.0 / (adjacent.size() + 1);
        }
        matrix[v][v] = 1.0 / (adjacent.size() + 1); // this is the probability of staying in place
        long_run_probs[v] = 1.0 / vertices.size(); //default all values in our probabilities vector to 1/(the amount of vertices)
    }

    //This loop does the same as multiplying (matrix^20) * long_run_probs, with long_run_probs treated as a vector
    for (int i = 0; i < 20; i++) {
        //takes the dot product of each row of the matrix and the long_run_probs "vector"
        for (const Vertex& v : vertices) {
            long double cell_value = 0.0;
            for (const Vertex& u : vertices) {
                cell_value += long_run_probs[v] * matrix[u][v];
            }
            long_run_probs[v] = cell_value;
        }
        //These two loops serve to normalize long_run_probs after multiplication (make all values sum to 1)
        double sum = 0;
        for (const auto& pair : long_run_probs) {
            sum += pair.second;
        }
        for (auto& pair : long_run_probs) {
            pair.second /= sum;
        }
    }
    return long_run_probs;
}