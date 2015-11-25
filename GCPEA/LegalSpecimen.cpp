#include "LegalSpecimen.h"

void LegalSpecimen::mutate()
{
	for (size_t i = 0; i < colors.size(); i++) {
		for (size_t j = 0; j < colors[i].size(); j++)
		{
			if (rand() % colors.size() < mutationValue * colors.size())
			{
				fillValidColor(i, j);
			}
		}
	}
}

void LegalSpecimen::fillValidColor(int node, int colorPosition)
{
	pair<int, int> minMaxColors = getMinMaxColor();

	vector<int> availableColors = vector<int>(minMaxColors.second - minMaxColors.first);
	iota(availableColors.begin(), availableColors.end(), minMaxColors.first);
	random_shuffle(availableColors.begin(), availableColors.end());

	bool colored = false;
	//if (rand() % 100 > 10)
	//{
	int i = 0;
	while (!colored && i < availableColors.size())
	{
		colors[node][colorPosition] = availableColors[i];
		if (isValidColored(node, colorPosition))
		{
			colored = true;
		}
		i++;
	}
	//}

	int newMax = minMaxColors.second + 1;
	while (!colored)
	{
		colors[node][colorPosition] = newMax;
		if (isValidColored(node, colorPosition))
		{
			colored = true;
		}
		newMax++;
	}
}

void LegalSpecimen::fixAll()
{
	for (int i = 0; i < colors.size(); i++)
	{
		for (int j = 0; j < colors[i].size(); j++)
		{
			if (!isValidColored(i, j))
			{
				fillValidColor(i, j);
			}
		}
	}
}

LegalSpecimen::LegalSpecimen(Graph * graph, float mutationValue, bool multi) : Specimen(graph, mutationValue, multi)
{
	fixAll();
}

LegalSpecimen::LegalSpecimen(Graph * graph, float mutationValue, vector<vector<int>> colors, bool multi) : Specimen(graph, mutationValue, colors, multi)
{
}

LegalSpecimen::~LegalSpecimen()
{
}

int LegalSpecimen::rate()
{
	return getColorCount();
}

vector<shared_ptr<Specimen>> LegalSpecimen::cross(shared_ptr<Specimen>& other, float chance)
{

	vector<shared_ptr<Specimen>> children(2);

	shared_ptr<LegalSpecimen> child1, child2;

	if ((double)rand() / RAND_MAX < chance)
	{
		auto& firstChildColors = vector<vector<int>>(graph->getNodeCount());
		auto& secondChildColors = vector<vector<int>>(graph->getNodeCount());

		auto& parent2Colors = other->getColors();

		int cutPosition = (rand() % colors.size() / 2) + (colors.size() / 5);
		for (int i = 0; i < cutPosition; i++)
		{
			firstChildColors[i] = this->colors[i];
			secondChildColors[i] = parent2Colors[i];
		}
		for (int i = cutPosition; i < colors.size(); i++)
		{
			firstChildColors[i] = parent2Colors[i];
			secondChildColors[i] = this->colors[i];
		}

		child1 = shared_ptr<LegalSpecimen>(new LegalSpecimen(graph, mutationValue, firstChildColors, multi));
		child2 = shared_ptr<LegalSpecimen>(new LegalSpecimen(graph, mutationValue, secondChildColors, multi));
	}
	else
	{
		child1 = shared_ptr<LegalSpecimen>(new LegalSpecimen(graph, mutationValue, colors, multi));
		child2 = shared_ptr<LegalSpecimen>(new LegalSpecimen(graph, mutationValue, other->getColors(), multi));
	}

	child1->fixAll();
	child2->fixAll();
	child1->mutate();
	child2->mutate();
	children[0] = child1;
	children[1] = child2;
	
	return children;
}
