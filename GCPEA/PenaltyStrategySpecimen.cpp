#include "PenaltyStrategySpecimen.h"


void PenaltyStrategySpecimen::mutate()
{
	for (size_t i = 0; i < colors.size(); i++) {
		for (size_t j = 0; j < colors[i].size(); j++)
		{
			if (rand() % colors.size() < mutationValue * colors.size())
			{
				colors[i][j] = rand() % (60);
			}
		}
	}
}

PenaltyStrategySpecimen::PenaltyStrategySpecimen(Graph * graph, float mutationValue, int errorMultiplier, int colorMultiplier, bool multi) 
	: Specimen(graph, mutationValue, multi)
{
	this->errorMultiplier = errorMultiplier;
	this->colorMultiplier = colorMultiplier;
	randomizeGenes(100);
	//TODO : pick better number
}

PenaltyStrategySpecimen::PenaltyStrategySpecimen(Graph * graph, float mutationValue, int errorMultiplier, int colorMultiplier, 
	vector<vector<int>> colors, bool multi) : Specimen(graph, mutationValue, colors, multi)
{
	this->errorMultiplier = errorMultiplier;
	this->colorMultiplier = colorMultiplier;
}

PenaltyStrategySpecimen::~PenaltyStrategySpecimen()
{
}

vector<shared_ptr<Specimen>> PenaltyStrategySpecimen::cross(shared_ptr<Specimen> & other, float chance)
{
	vector<shared_ptr<Specimen>> children(2);

	shared_ptr<PenaltyStrategySpecimen> child1, child2;

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

		child1 = shared_ptr<PenaltyStrategySpecimen>(new PenaltyStrategySpecimen(graph, mutationValue, errorMultiplier, colorMultiplier, firstChildColors, multi));
		child2 = shared_ptr<PenaltyStrategySpecimen>(new PenaltyStrategySpecimen(graph, mutationValue, errorMultiplier, colorMultiplier, secondChildColors, multi));
	}
	else
	{
		child1 = shared_ptr<PenaltyStrategySpecimen>(new PenaltyStrategySpecimen(graph, mutationValue, errorMultiplier, colorMultiplier, colors, multi));
		child2 = shared_ptr<PenaltyStrategySpecimen>(new PenaltyStrategySpecimen(graph, mutationValue, errorMultiplier, colorMultiplier, other->getColors(), multi));
	}
	child1->mutate();
	child2->mutate();
	children[0] = child1;
	children[1] = child2;

	return children;
}

int PenaltyStrategySpecimen::rate()
{
	int colorCount = getColorCount();

	int errorCount = getErrorCount();

	return colorMultiplier * colorCount + errorMultiplier * errorCount;
}