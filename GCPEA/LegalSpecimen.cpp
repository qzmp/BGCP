#include "LegalSpecimen.h"

void LegalSpecimen::mutate()
{
	for (size_t i = 0; i < colors.size(); i++) {
		if (rand() % colors.size() < mutationValue * colors.size())
		{
			fillValidColor(i);
		}
	}
}

vector<int> LegalSpecimen::fillSurroundings(int mid, int range)
{
	vector<int> result = vector<int>(1 + (2 * range));
	iota(result.begin(), result.end(), mid - range);
	return result;
}

void LegalSpecimen::fillValidColor(int node)
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

void LegalSpecimen::fixAll()
{
	for (int i = 0; i < colors.size(); i++)
	{
		if (!isValidColored(i))
		{
			fillValidColor(i);
		}
	}
}

LegalSpecimen::LegalSpecimen()
{
}

LegalSpecimen::LegalSpecimen(Graph * graph, float mutationValue) : Specimen(graph, mutationValue)
{
	fixAll();
}

LegalSpecimen::LegalSpecimen(Graph * graph, float mutationValue, vector<int> & colors) : Specimen(graph, mutationValue, colors)
{
}

LegalSpecimen::~LegalSpecimen()
{
}

int LegalSpecimen::rate()
{
	if(getErrorCount() > 0)
		int test = getErrorCount();
	return getColorCount();
}

vector<shared_ptr<Specimen>> LegalSpecimen::cross(shared_ptr<Specimen>& other, float chance)
{

	vector<shared_ptr<Specimen>> children(2);

	shared_ptr<LegalSpecimen> child1, child2;

	if ((double)rand() / RAND_MAX < chance)
	{
		auto& firstChildColors = vector<int>(graph->getNodeCount());
		auto& secondChildColors = vector<int>(graph->getNodeCount());

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

		child1 = shared_ptr<LegalSpecimen>(new LegalSpecimen(graph, mutationValue, firstChildColors));
		child2 = shared_ptr<LegalSpecimen>(new LegalSpecimen(graph, mutationValue, secondChildColors));
	}
	else
	{
		child1 = shared_ptr<LegalSpecimen>(new LegalSpecimen(graph, mutationValue, colors));
		child2 = shared_ptr<LegalSpecimen>(new LegalSpecimen(graph, mutationValue, other->getColors()));
	}

	child1->fixAll();
	child2->fixAll();
	child1->mutate();
	child2->mutate();
	children[0] = child1;
	children[1] = child2;
	
	return children;
}
