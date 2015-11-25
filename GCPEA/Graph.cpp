#include "Graph.h"



Graph::Graph()
{
}

Graph::Graph(string filename)
{
	loadFromFile(filename);
	duplicateNeighbours();
	//removeLoops();
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
				nodeWeights = vector<int>(vertexCount);
				fileStream >> edgeCount;
			}
			if (next == "e") {
				fileStream >> vertex1;
				fileStream >> vertex2;
				fileStream >> weight;			
				edges[--vertex1].push_back(pair<int,int>(--vertex2, weight));
			}
			if (next == "n") {
				fileStream >> vertex1;
				fileStream >> weight;
				nodeWeights[--vertex1] = weight;
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

void Graph::removeLoops()
{
	for (int i = 0; i < neighbours.size(); i++)
	{
		if (neighbours[i].front().first == i)
		{
			neighbours[i].erase(remove(neighbours[i].begin(), neighbours[i].end(), neighbours[i].front()), neighbours[i].end());
		}
	}
}

void Graph::removeDuplicateEdges()
{
	for (auto& n : neighbours)
	{
		for (auto& p : n)
		{
			list<pair<int, int>> node = neighbours[p.first];
			
			node.erase(remove(node.begin(), node.end(), p), node.end());
		}			
	}
}

void Graph::duplicateNeighbours()
{
	for (int i = 0; i < neighbours.size(); i++)
	{
		for (auto& p : neighbours[i])
		{
			auto& node = neighbours[p.first];
			if (find(node.begin(), node.end(), pair<int, int>(i, p.second)) == node.end())
			{
				node.push_back(pair<int, int>(i, p.second));
			}			
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

int Graph::getNodeWeight(int node)
{
	return nodeWeights[node];
}
