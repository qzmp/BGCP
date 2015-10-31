#include "Specimen.h"


Specimen::Specimen(Graph * graph, float mutationValue)
{
	this->graph = graph;
	this->mutationValue = mutationValue;
	randomizeGenes();
	fixAll();
}

Specimen::Specimen(Specimen & parent1, Specimen & parent2)
{
	this->graph = parent1.graph;
	this->mutationValue = parent1.mutationValue;
	colors = vector<int>(graph->getNodeCount());
	int cutPosition = (rand() % colors.size() / 2) + (colors.size() / 5);
	for (int i = 0; i < cutPosition; i++) 
	{
		colors[i] = parent1.colors[i];
	}
	for (int i = cutPosition; i < colors.size(); i++)
	{
		colors[i] = parent2.colors[i];
	}
	fixAll();
	mutate2();
}

Specimen::Specimen(Specimen & other)
{
	this->graph = other.graph;
	this->mutationValue = other.mutationValue;
	this->colors = other.colors;
	mutate2();
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

int Specimen::rate()
{
	int errorCount = 0;

	int minElement = *min_element(colors.begin(), colors.end());
	int maxElement = *max_element(colors.begin(), colors.end());

	errorCount = maxElement - minElement;
	
	for (size_t i = 0; i < colors.size(); i++)
	{
		if (!isValidColored(i))
		{
			errorCount++;
		}
	}
	
	return errorCount;
}

pair<Specimen*, Specimen*>& Specimen::cross(Specimen & other)
{
	Specimen* child1 = new Specimen(*this, other);
	Specimen* child2 = new Specimen(other, *this);

	return pair<Specimen*, Specimen*>(child1, child2);
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

void Specimen::mutate()
{
	for (size_t i = 0; i < colors.size(); i++) {
		if (rand() % colors.size() < mutationValue * colors.size())
		{
			colors[i] = rand() % graph->getNodeCount();
		}
	}
}

void Specimen::mutate2()
{
	for (size_t i = 0; i < colors.size(); i++)
	{
		if (rand() % colors.size() < mutationValue * colors.size())
		{
			fillValidColor(i);
		}
	}
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

vector<int> Specimen::fillSurroundings(int mid, int range)
{
	vector<int> result = vector<int>(1 + (2 * range));
	iota(result.begin(), result.end(), mid - range);
	return result;
}

void Specimen::fillValidColor(int node)
{
	auto& minMaxColors = minmax_element(colors.begin(), colors.end());

	vector<int> availableColors = vector<int>(*minMaxColors.second - *minMaxColors.first);
	iota(availableColors.begin(), availableColors.end(), *minMaxColors.first);
	random_shuffle(availableColors.begin(), availableColors.end());

	bool colored = false;
	int i = 0;
	while (!colored && i < availableColors.size())
	{
		colors[node] = availableColors[i];
		if (isValidColored(node))
		{
			colored = true;
		}
		i++;
	}

	int newMax = *minMaxColors.second + 1;
	while (!colored)
	{
		colors[node] = newMax;
		if (isValidColored(node))
		{
			colored = true;
		}
		newMax++;
	}
}

void Specimen::fixAll()
{
	for (int i = 0; i < colors.size(); i++)
	{
		if (!isValidColored(i))
		{
			fillValidColor(i);
		}
	}
}
