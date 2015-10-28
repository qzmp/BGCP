#include "Graph.h"



Graph::Graph()
{
}

Graph::Graph(string filename)
{
	loadFromFile(filename);
	removeDuplicateEdges();
	this->name = filename;
}


Graph::~Graph()
{
}

int Graph::loadFromFile(string filename)
{
	ifstream fileStream;
	fileStream.open(filename);

	if (fileStream.is_open())
	{
		string next;
		int vertexCount, edgeCount;
		int vertex1, vertex2, weight;

		vector<list<pair<int, int>>> edges;

		while (!fileStream.eof())
		{
			fileStream >> next;

			if (next == "band") {
				fileStream >> vertexCount;
				edges = vector<list<pair<int, int>>>(vertexCount);
				fileStream >> edgeCount;
			}

			if (next == "e") {
				fileStream >> vertex1;
				fileStream >> vertex2;
				fileStream >> weight;			
				edges[vertex1 - 1].push_back(pair<int,int>(vertex2, weight));
			}
		}
		fileStream.close();
		this->neighbours = edges;
		return 0;
	}
	else 
	{
		return -1;
	}
}

void Graph::removeDuplicateEdges()
{
	for (auto& n : neighbours)
	{
		for (auto& p : n)
		{
			list<pair<int, int>> node = neighbours[p.first - 1];
			
			node.erase(remove(node.begin(), node.end(), p), node.end());
		}			
	}
}

string Graph::getName()
{
	return this->name;
}

int Graph::getNodeCount()
{
	return neighbours.size();
}

list<pair<int, int>>& Graph::getNeighbours(int firstNode)
{
	return neighbours[firstNode];
}
