#include "../catch/catch.hpp"
#include "../graph.h"
#include "../random.h"
#include "../read.h"
#include "../readFromFile.hpp"
#include "../algorithms.h"

TEST_CASE("parseData", "[parse]")
{
	Graph g = readdata::readData("tests/parsingSimple.txt");
    //Checks to see if the proper number of vertices and edges were created
	REQUIRE(g.getVertices().size() == 10);
    REQUIRE(g.getEdges().size() == 10);

    //Checks random vertices to make sure they were created
    REQUIRE(g.vertexExists("123456789"));
    REQUIRE(g.vertexExists("987654321"));
    REQUIRE(g.vertexExists("149162536"));
    REQUIRE(g.vertexExists("11235813"));
    REQUIRE(g.vertexExists("101010101"));
    REQUIRE(g.vertexExists("35783231"));

    //Checks to make sure a couple random vertices have the correct number of connections
    std::vector<Vertex> adj = g.getAdjacent("123456789");
    REQUIRE(adj.size() == 1);
    REQUIRE(adj[0] == "987654321");

    adj = g.getAdjacent("149162536");
    REQUIRE(adj.size() == 3);

    adj = g.getAdjacent("135790246");
    REQUIRE(adj.size() == 2);
}


TEST_CASE("BFS with immediate link", "[algorithm][BFS]")
{
    Graph g = readdata::readData("tests/parsingSimple.txt");

    const auto& trav = algorithms::BFS("123456789", "987654321", g);

    std::vector<Vertex> expected;
    expected.push_back("123456789");
    expected.push_back("987654321");

    REQUIRE(trav.size() == expected.size());

    for (size_t i = 0; i < trav.size(); i++) {
        REQUIRE(trav.at(i) == expected.at(i));
    }

}


TEST_CASE("BFS with one internal node", "[algorithm][BFS]")
{
    Graph g = readdata::readData("tests/parsingSimple.txt");

    const auto& trav = algorithms::BFS("135790246", "11235813", g);

    std::vector<Vertex> expected;
    expected.push_back("135790246");
    expected.push_back("149162536");
    expected.push_back("11235813");

    REQUIRE(trav.size() == expected.size());

    for (size_t i = 0; i < trav.size(); i++) {
        REQUIRE(trav.at(i) == expected.at(i));
    }
}

TEST_CASE("BFS with multiple internal nodes", "[algorithm][BFS]")
{
    Graph g = readdata::readData("tests/parsingSimple.txt");

    const auto& trav = algorithms::BFS("149162536", "987654321", g);

    std::vector<Vertex> expected;
    expected.push_back("149162536");
    expected.push_back("101010101");
    expected.push_back("123456789");
    expected.push_back("987654321");

    REQUIRE(trav.size() == expected.size());

    for (size_t i = 0; i < trav.size(); i++) {
        REQUIRE(trav.at(i) == expected.at(i));
    }
}

TEST_CASE("Dijkstra with immediate link", "[algorithm][Dijkstra]")
{
    Graph g = readdata::readData("tests/parsingSimple.txt");

    const auto& trav = algorithms::Dijkstra("123456789", "987654321", g);

    std::vector<Vertex> expected;
    expected.push_back("123456789");
    expected.push_back("987654321");

    REQUIRE(trav.size() == expected.size());

    for (size_t i = 0; i < trav.size(); i++) {
        REQUIRE(trav.at(i) == expected.at(i));
    }

}


TEST_CASE("Dijkstra with one internal node", "[algorithm][Dijkstra]")
{
    Graph g = readdata::readData("tests/parsingSimple.txt");

    const auto& trav = algorithms::Dijkstra("135790246", "11235813", g);

    std::vector<Vertex> expected;
    expected.push_back("135790246");
    expected.push_back("149162536");
    expected.push_back("11235813");

    REQUIRE(trav.size() == expected.size());

    for (size_t i = 0; i < trav.size(); i++) {
        REQUIRE(trav.at(i) == expected.at(i));
    }
}

TEST_CASE("Dijkstra with multiple internal nodes", "[algorithm][Dijkstra]")
{
    Graph g = readdata::readData("tests/parsingSimple.txt");

    const auto& trav = algorithms::Dijkstra("149162536", "987654321", g);

    std::vector<Vertex> expected;
    expected.push_back("149162536");
    expected.push_back("101010101");
    expected.push_back("123456789");
    expected.push_back("987654321");

    REQUIRE(trav.size() == expected.size());

    for (size_t i = 0; i < trav.size(); i++) {
        REQUIRE(trav.at(i) == expected.at(i));
    }
}

TEST_CASE("Dijkstra simple test", "[algorithm][Dijkstra]")
{
    Graph g = readdata::readData("tests/dijkstraSimple.txt");

    const auto& trav = algorithms::Dijkstra("1", "12", g);

    std::vector<Vertex> expected;
    expected.push_back("1");
    expected.push_back("21");
    expected.push_back("12");

    REQUIRE(trav.size() == expected.size());

    for (size_t i = 0; i < trav.size(); i++) {
        REQUIRE(trav.at(i) == expected.at(i));
    }
}

TEST_CASE("Dijkstra complex test", "[algorithm][Dijkstra]")
{
    Graph g = readdata::readData("tests/dijkstraComplex.txt");

    const auto& trav = algorithms::Dijkstra("1", "4", g);

    std::vector<Vertex> expected;
    expected.push_back("1");
    expected.push_back("2");
    expected.push_back("3");
    expected.push_back("4");

    REQUIRE(trav.size() == expected.size());

    for (size_t i = 0; i < trav.size(); i++) {
        REQUIRE(trav.at(i) == expected.at(i));
    }
}

TEST_CASE("PageRank simple Test", "[algorithm][PageRank]")
{
    Graph g = readdata::readData("tests/parsingSimple.txt");
    auto pageRankMap = algorithms::PageRank(g);
    vector<long double> ordered_vec;
    for (const auto pair : pageRankMap) {
        ordered_vec.push_back(pair.second);
    }
    std::sort(ordered_vec.begin(), ordered_vec.end());

    REQUIRE(ordered_vec[0] == pageRankMap["12468996"]);
    REQUIRE(ordered_vec[1] == pageRankMap["101519816"]);
    REQUIRE(ordered_vec[4] == pageRankMap["101010101"]);
    REQUIRE(ordered_vec[5] == pageRankMap["123456789"]);
    REQUIRE(ordered_vec[8] == pageRankMap["11235813"]);
    REQUIRE(ordered_vec[9] == pageRankMap["987654321"]);

    REQUIRE(ordered_vec[2] == ordered_vec[3]);
    REQUIRE(ordered_vec[7] == ordered_vec[6]);
    
}

TEST_CASE("PageRank complex Test", "[algorithm][PageRank]")
{
    Graph g = readdata::readData("tests/dijkstraSimple.txt");
    auto pageRankMap = algorithms::PageRank(g);
    vector<long double> ordered_vec;
    for (const auto pair : pageRankMap) {
        ordered_vec.push_back(pair.second);
    }
    std::sort(ordered_vec.begin(), ordered_vec.end());

    REQUIRE(ordered_vec[15] == pageRankMap["4"]);
    REQUIRE(ordered_vec[20] == pageRankMap["12"]);
    REQUIRE(ordered_vec[21] == pageRankMap["6"]);
    REQUIRE(ordered_vec[22] == pageRankMap["21"]);

    REQUIRE(ordered_vec[0] == ordered_vec[14]);
    REQUIRE(ordered_vec[16] == ordered_vec[17]);
    REQUIRE(ordered_vec[18] == ordered_vec[19]);

}
