#include "Specimen.h"

vector<vector<int>>& Specimen::getColors()
{
	return colors;
}

Specimen::Specimen(Graph * graph, float mutationValue, bool multi)
{
	this->graph = graph;
	this->mutationValue = mutationValue;
	this->multi = multi;

	colors = vector<vector<int>>(graph->getNodeCount());

	if (multi)
	{
		for (int i = 0; i < colors.size(); i++)
		{
			colors[i] = vector<int>(graph->getNodeWeight(i));
		}
	}
	else
	{
		for (int i = 0; i < colors.size(); i++)
		{
			colors[i] = vector<int>(1);
		}
	}

	randomizeGenes();
}

Specimen::Specimen(Graph * graph, float mutationValue, vector<vector<int>> colors, bool multi)
{
	this->graph = graph;
	this->mutationValue = mutationValue;
	this->multi = multi;
	this->colors = colors;
}

Specimen::Specimen()
{
}

Specimen::~Specimen()
{
}

void Specimen::randomizeGenes()
{
	for (int i = 0; i < graph->getNodeCount(); i++)
	{
		for (int j = 0; j < colors[i].size(); j++)
		{
			colors[i][j] = (rand() % 20);
		}
	}
}

bool Specimen::isValidColored(int node, int colorPosition)
{
	/*
	for (size_t i = 0; i < colors[node].size(); i++)
	{
		if (i != colorPosition && colors[node][colorPosition] == colors[node][i])
		{
			return false;
		}
	}
	*/
	for (auto& n : graph->getNeighbours(node))
	{
		for (int i = 0; i < colors[n.first].size(); i++)
		{
			if (!(n.first == node && i == colorPosition))
			{
				if (abs(colors[node][colorPosition] - colors[n.first][i]) < n.second)
				{
					return false;
				}
			}	
		}
	}
	return true;
}

pair<int, int> Specimen::getMinMaxColor()
{
	int minColor = colors[0][0];
	int maxColor = colors[0][0];

	for (vector<int> node : colors)
	{
		for (int color : node) {
			if (color < minColor)
			{
				minColor = color;
			}
			if (color > maxColor)
			{
				maxColor = color;
			}
		}
	}
	return pair<int, int>(minColor, maxColor);
}

int Specimen::getColorCount()
{
	pair<int, int> minMax = getMinMaxColor();
	return minMax.second - minMax.first;
}

int Specimen::getErrorCount()
{
	int errorCount = 0;
	for (size_t i = 0; i < colors.size(); i++)
	{
		for (size_t j = 0; j < colors[i].size(); j++)
		{
			if (!isValidColored(i, j))
			{
				errorCount++;
			}
		}
	}

	return errorCount;
}

