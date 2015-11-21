#include "Specimen.h"

Specimen::Specimen(Graph * graph, float mutationValue)
{
	this->graph = graph;
	this->mutationValue = mutationValue;
	randomizeGenes();
}

Specimen::Specimen(Graph * graph, float mutationValue, vector<int> & colors)
{
	this->graph = graph;
	this->mutationValue = mutationValue;
	this->colors = colors;
}

Specimen::Specimen()
{
}

void Specimen::randomizeGenes()
{
	colors = vector<int>(graph->getNodeCount());
	for (int j = 0; j < graph->getNodeCount(); j++)
	{
		colors[j] = (rand() % graph->getNodeCount());
	}
}

Specimen::~Specimen()
{
}

string Specimen::toString()
{
	string result;
	for (int i = 0; i < colors.size(); i++)
	{
		result += to_string(i) + ":" + to_string(colors[i]) + " ";
	}
	return result;
}

vector<int>& Specimen::getColors()
{
	return colors;
}

bool Specimen::isValidColored(int node)
{
	for (auto& n : graph->getNeighbours(node))
	{
		if (abs(colors[n.first] - colors[node]) < n.second)
		{
			return false;
		}
	}
	return true;
}

int Specimen::rateNode(int node)
{
	int rating = 0;
	for (auto& n : graph->getNeighbours(node))
	{
		if (abs(colors[n.first] - colors[node]) < n.second)
		{
			rating++;
		}
	}
	return rating;
}

int Specimen::getColorCount()
{
	int minElement = *min_element(colors.begin(), colors.end());
	int maxElement = *max_element(colors.begin(), colors.end());

	return maxElement - minElement;
}

int Specimen::getErrorCount()
{
	int errorCount = 0;
	for (size_t i = 0; i < colors.size(); i++)
	{
		if (!isValidColored(i))
		{
			errorCount++;
		}
	}

	return errorCount;
}
