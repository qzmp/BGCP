#include "Specimen.h"


Specimen::Specimen(Graph * graph, float mutationValue)
{
	this->graph = graph;
	this->mutationValue = mutationValue;
	randomizeGenes();
	fix();
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

	set<int> individualColors(colors.begin(), colors.end());

	errorCount = individualColors.size();

	for (size_t i = 0; i < colors.size(); i++)
	{
		int processedColor = colors[i];
		list<pair<int, int>> processedNeighbours = graph->getNeighbours(i);

		for (auto& p : processedNeighbours) {
			int colorDiff = abs(colors[p.first - 1] - processedColor);
			if (colorDiff < p.second)
			{
				errorCount += 2;
			}
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
			colors[i] = fix(colors[i]);
		}
	}
}

bool Specimen::validColor(int color)
{
	for (auto& n : graph->getNeighbours(color))
	{
		if (abs(colors[n.first - 1] - color) < n.second)
		{
			return false;
		}
	}
	return true;
}

vector<int> Specimen::getFilledSet(int middle, int range)
{
	vector<int> result = vector<int>(1 + (2 * range));
	iota(result.begin(), result.end(), middle - range);
	return result;
}

int Specimen::fix(int node)
{
	set<int> unavailableColors;
	vector<int> temporaryColors;
	for (auto& n : graph->getNeighbours(node))
	{
		temporaryColors = getFilledSet(colors[n.first - 1], n.second - 1);
		unavailableColors.insert(temporaryColors.begin(), temporaryColors.end());
	}

	if (unavailableColors.size() >= colors.size())
	{
		return (*unavailableColors.rbegin()) + 1;
	}

	vector<int> availableColors(colors.size() - unavailableColors.size());
	
	int fillingColor = 0;
	int i = 0;
	while (i < availableColors.size())
	{
		if (find(unavailableColors.begin(), unavailableColors.end(), fillingColor) == unavailableColors.end())
		{
			availableColors[i++] = fillingColor;
		}
		fillingColor++;
	}
	return availableColors[rand() % availableColors.size()];
}

void Specimen::fix()
{
	for (int i = 0; i < colors.size(); i++)
	{
		if (!validColor(colors[i]))
		{
			colors[i] = fix(i);
		}
	}
}
