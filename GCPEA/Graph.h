#pragma once

#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Graph
{
private:
	vector<list<pair<int, int>>> neighbours;
	string name;

	void removeDuplicateEdges();

public:
	Graph();
	Graph(string filename);
	~Graph();

	int loadFromFile(string filename);

	string getName();

	int getNodeCount();
	list<pair<int, int>>& getNeighbours(int firstNode);
};

