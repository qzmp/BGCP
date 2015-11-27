#include "SetColorSpecimen.h"


void SetColorSpecimen::mutate()
{
	for (size_t i = 0; i < colors.size(); i++) {
		for (size_t j = 0; j < colors[i].size(); j++)
		{
			if (rand() % colors.size() < mutationValue * colors.size())
			{
				colors[i][j] = rand() % colorCount;
			}
		}
	}
}

SetColorSpecimen::SetColorSpecimen(Graph * graph, float mutationValue, bool multi, int colorCount) : Specimen(graph, mutationValue, multi)
{
	this->colorCount = colorCount;
	randomizeGenes(colorCount);
}

SetColorSpecimen::SetColorSpecimen(Graph * graph, float mutationValue, vector<vector<int>> colors, bool multi, int colorCount) : Specimen(graph, mutationValue, colors, multi)
{
	this->colorCount = colorCount;
}

SetColorSpecimen::~SetColorSpecimen()
{
}

int SetColorSpecimen::rate()
{
	return getErrorCount();
}

vector<shared_ptr<Specimen>> SetColorSpecimen::cross(shared_ptr<Specimen>& other, float chance)
{
	vector<shared_ptr<Specimen>> children(2);

	shared_ptr<SetColorSpecimen> child1, child2;

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

		child1 = shared_ptr<SetColorSpecimen>(new SetColorSpecimen(graph, mutationValue, firstChildColors, multi, colorCount));
		child2 = shared_ptr<SetColorSpecimen>(new SetColorSpecimen(graph, mutationValue, secondChildColors, multi, colorCount));
	}
	else
	{
		child1 = shared_ptr<SetColorSpecimen>(new SetColorSpecimen(graph, mutationValue, colors, multi, colorCount));
		child2 = shared_ptr<SetColorSpecimen>(new SetColorSpecimen(graph, mutationValue, other->getColors(), multi, colorCount));
	}
	child1->mutate();
	child2->mutate();
	children[0] = child1;
	children[1] = child2;

	return children;
}
