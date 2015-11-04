#include "Population.h"

Population::Population(int size, string filename, int maxPops, float mutationValue, float tourneyRatio, float crossingChance, double ratingFunc(int colorCount, int errorCount))
{
	srand(time(NULL));
	this->specimens = vector<Specimen>(size);
	this->graph = Graph(filename);
	this->mutationValue = mutationValue;
	this->tourneyRatio = tourneyRatio;
	this->crossingChance = crossingChance;

	for (int i = 0; i < size; i++)
	{
		specimens[i] = Specimen(&graph, mutationValue, ratingFunc);
	}

	this->rateAll();
}

Population::~Population()
{
}

int Population::getRating(int specimenNum)
{
	return ratings.back()[specimenNum];;
}

void Population::rateAll()
{
	vector<int> newRatings = vector<int>(specimens.size());
	for (size_t i = 0; i < this->specimens.size(); i++) {
		newRatings[i] = specimens[i].rateFenotype();
	}
	ratings.push_back(newRatings);
}

int Population::bestGrade(vector<int>& ratings)
{
	int best = ratings[0];
	for (size_t i = 0; i < ratings.size(); i++)
	{
		if (ratings[i] < best)
			best = ratings[i];
	}
	return best;
}

int Population::worstGrade(vector<int>& ratings)
{
	int worst = ratings[0];
	for (size_t i = 0; i < ratings.size(); i++)
	{
		if (ratings[i] > worst)
			worst = ratings[i];
	}
	return worst;
}

float Population::averageGrade(vector<int>& ratings)
{
	int sum = 0;
	for (size_t i = 0; i < ratings.size(); i++)
	{
		sum += ratings[i];
	}
	return sum / ratings.size();
}

bool Population::perfected()
{
	if (!ratings.empty())
	{
		return bestGrade(ratings.back()) == 0;
	}
	else
	{
		return false;
	}
}

Specimen & Population::tourney(vector<int>& tourneyGroup)
{
	int best = tourneyGroup[0];
	for (size_t i = 1; i < tourneyGroup.size(); i++)
	{
		if (this->getRating(tourneyGroup[i]) < this->getRating(best))
		{
			best = tourneyGroup[i];
		}
	}
	return specimens[best];
}

Specimen & Population::randomSpec()
{
	return specimens[rand() % specimens.size()];
}

Specimen & Population::select(int tourneySize)
{
	vector<int> tourneyGroup(tourneySize);
	for (int i = 0; i < tourneySize; i++)
	{
		tourneyGroup[i] = (rand() % specimens.size());
	}
	return tourney(tourneyGroup);
}

void Population::crossing()
{
	vector<Specimen> newPop = vector<Specimen>(specimens.size());
	Specimen *parent1, *parent2;
	pair<Specimen*, Specimen*> children;
	int tourneySize = tourneyRatio * specimens.size();

	size_t i = 0;
	while (i < specimens.size())
	{
		parent1 = &select(tourneySize);
		parent2 = &select(tourneySize);

		if (rand() % specimens.size() < crossingChance * specimens.size())
		{
			children = parent1->cross(*parent2);
			newPop[i++] = *children.first;
			newPop[i++] = *children.second;
			delete children.first;
			delete children.second;
		}
		else
		{
			newPop[i++] = Specimen(*parent1);
			newPop[i++] = Specimen(*parent2);
		}
	}
	specimens = newPop;
}

void Population::generateNewPopulation()
{
	crossing();
	rateAll();
}

void Population::saveToFile()
{
	ofstream resultFile;
	string filename = "results//" + graph.getName() + " CC#" + to_string(crossingChance) + " TR#" + to_string(tourneyRatio) + " MV#" + to_string(mutationValue) + ".csv";
	resultFile.open(filename);
	for (list<vector<int>>::iterator it = ratings.begin(); it != ratings.end(); it++)
	{
		vector<int> processedRatings = *it;
		resultFile << worstGrade(processedRatings) << ";";
		resultFile << averageGrade(processedRatings) << ";";
		resultFile << bestGrade(processedRatings) << "\n";

	}
	resultFile.close();
}

Specimen & Population::getBest()
{
	auto& recentRatings = ratings.back();
	int minRating = recentRatings[0];
	int bestPos = 0;
	for (int i = 1; i < recentRatings.size(); i++)
	{
		if (recentRatings[i] < minRating)
		{
			minRating = recentRatings[i];
			bestPos = i;
		}
	}
	int test = specimens[bestPos].rateFenotype();
	return specimens[bestPos];
}

Graph & Population::getGraph()
{
	return graph;
}

int Population::getSize()
{
	return specimens.size();
}

float Population::getMutationValue()
{
	return mutationValue;
}

float Population::getCrossingChance()
{
	return crossingChance;
}

float Population::getTourneyRatio()
{
	return tourneyRatio;
}
