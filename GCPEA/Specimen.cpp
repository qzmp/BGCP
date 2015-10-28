#include "Specimen.h"


Specimen::Specimen(Graph * graph, float mutationValue)
{
	this->graph = graph;
	this->mutationValue = mutationValue;
	randomizeGenes();
}

Specimen::Specimen(Specimen & parent1, Specimen & parent2)
{
	this->graph = parent1.graph;
	this->mutationValue = parent1.mutationValue;
	colors = vector<int>(graph->getNodeCount());
	for (int i = 0; i < colors.size() / 2; i++) 
	{
		colors[i] = parent1.colors[i];
	}
	for (int i = colors.size() / 2; i < colors.size(); i++)
	{
		colors[i] = parent2.colors[i];
	}
	mutate();
}

Specimen::Specimen(Specimen & other)
{
	this->graph = other.graph;
	this->mutationValue = other.mutationValue;
	this->colors = other.colors;
	mutate();
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
			if (abs(colors[p.first - 1] - processedColor) > p.second)//naprawic
			{
				errorCount++;
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

void Specimen::mutate()
{
	for (size_t i = 0; i < colors.size(); i++) {
		if (rand() % colors.size() < mutationValue * colors.size())
		{
			colors[i] = rand() % graph->getNodeCount();
		}
	}
}

bool Specimen::validColor(int color)
{
	for (auto& n : graph->getNeighbours(color))
	{
		if (abs(n.first - color) < n.second)
		{
			return false;
		}
	}
	return true;
}

int Specimen::fix(int color)
{
	unordered_set<int> unavailableColors;
	for (auto& n : graph->getNeighbours(color))
	{
		if (abs(n.first - color) < n.second)
		{
			unavailableColors.insert(n.first);
		}
	}
	/*
	if (find(unavailableColors.begin(), unavailableColors.end(), color) == unavailableColors.end())
	{
		return color;
	}
	*/
	vector<int> availableColors(colors.size() - unavailableColors.size());
	
	int fillingColor = 0;
	int i = 0;
	while (fillingColor = colors.size())
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
			colors[i] = fix(colors[i]);
		}
	}
}
