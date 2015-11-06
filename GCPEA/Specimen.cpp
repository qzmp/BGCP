#include "Specimen.h"


Specimen::Specimen(Graph * graph, float mutationValue, int errorMultiplier, int colorMultiplier)
{
	this->graph = graph;
	this->mutationValue = mutationValue;
	this->errorMultiplier = errorMultiplier;
	this->colorMultiplier = colorMultiplier;
	randomizeGenes();
}

Specimen::Specimen(Specimen & parent1, Specimen & parent2)
{
	this->graph = parent1.graph;
	this->mutationValue = parent1.mutationValue;
	this->errorMultiplier = parent1.errorMultiplier;
	this->colorMultiplier = parent1.colorMultiplier;
	colors = vector<int>(graph->getNodeCount());

	for (int i = 0; i < colors.size(); i++)
	{
		if (parent1.rateNode(i) < parent2.rateNode(i))
		{
			colors[i] = parent1.colors[i];
		}
		else
		{
			colors[i] = parent2.colors[i];
		}
	}
}

Specimen::Specimen(Specimen & other)
{
	this->graph = other.graph;
	this->mutationValue = other.mutationValue;
	this->colors = other.colors;
	this->errorMultiplier = other.errorMultiplier;
	this->colorMultiplier = other.colorMultiplier;
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
	int colorCount = getColorCount();
	
	int errorCount = getErrorCount();
	
	return colorMultiplier * colorCount + errorMultiplier * errorCount;
}

int Specimen::rateFenotype()
{
	vector<int> genotypeColors = colors;
	
	fixAll();

	int rating = rate();

	colors = genotypeColors;

	return rating;
}

Specimen & Specimen::cross(Specimen & other)
{
	return Specimen(*this, other);
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
			colors[i] = rand() % (graph->getNodeCount());
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
	//if (rand() % 100 > 10)
	//{
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
	//}

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
