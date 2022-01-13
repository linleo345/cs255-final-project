#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iterator>
#include "graph.h"


std::string file_to_string(const std::string & filename) {
	std::ifstream text(filename);
	
	std::stringstream strStream;
	if (text.is_open()) {
		strStream << text.rdbuf();
	}

	return strStream.str();
}

std::vector<std::pair<Vertex, Vertex>> file_to_vector(const std::string & filename) {
	std::ifstream text(filename);
	std::vector<std::pair<Vertex, Vertex>> out;
	long count = 0;
	Vertex a, b;
	if (text.is_open()) {
		while (text >> a >> b) {
			if (count == 10000) {
				break;
			}
			out.push_back(std::pair<Vertex, Vertex>(a, b));
			count++;
		}
	}

	return out;
} 