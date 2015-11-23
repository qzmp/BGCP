#include "Population.h"

Population::Population(int size, string filename, float mutationValue, float tourneyRatio, float crossingChance,
	int errorMultiplier, int colorMultiplier, int specimenType)
{
	this->specimens = vector<shared_ptr<Specimen>>(size);
	this->graph = Graph(filename);
	this->mutationValue = mutationValue;
	this->tourneyRatio = tourneyRatio;
	this->crossingChance = crossingChance;
	this->errorMultiplier = errorMultiplier;
	this->colorMultiplier = colorMultiplier;
	this->specimenType = specimenType;

	for (int i = 0; i < size; i++)
	{
		specimens[i] = shared_ptr<PenaltyStrategySpecimen>(new PenaltyStrategySpecimen(&graph, mutationValue, errorMultiplier, colorMultiplier));		
	}

	this->rateAll();
}

Population::Population(int size, string filename, float mutationValue, float tourneyRatio, float crossingChance, int specimenType)
{
	this->specimens = vector<shared_ptr<Specimen>>(size);
	this->graph = Graph(filename);
	this->mutationValue = mutationValue;
	this->tourneyRatio = tourneyRatio;
	this->crossingChance = crossingChance;
	this->errorMultiplier = errorMultiplier;
	this->colorMultiplier = colorMultiplier;
	this->specimenType = specimenType;

	for (int i = 0; i < size; i++)
	{
		specimens[i] = shared_ptr<LegalSpecimen>(new LegalSpecimen(&graph, mutationValue));
	}

	this->rateAll();
}


Population::Population()
{
}


Population::~Population()
{
}

void Population::reset()
{
	this->specimens = vector<shared_ptr<Specimen>>(specimens.size());
	this->ratings = list<vector<int>>(ratings.size());

	for (int i = 0; i < specimens.size(); i++)
	{
		switch (specimenType)
		{
		case 0:
		{
			specimens[i] = shared_ptr<PenaltyStrategySpecimen>(new PenaltyStrategySpecimen(&graph, mutationValue, errorMultiplier, colorMultiplier));
			break;
		}
		case 1:
		{
			specimens[i] = shared_ptr<LegalSpecimen>(new LegalSpecimen(&graph, mutationValue));
		}
		}
	}

	this->rateAll();
}

int Population::getRating(int specimenNum)
{
	return ratings.back()[specimenNum];;
}

void Population::rateAll()
{
	vector<int> newRatings = vector<int>(specimens.size());
	for (size_t i = 0; i < this->specimens.size(); i++) {
		newRatings[i] = specimens[i]->rate();
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
	return (float)sum / (float)ratings.size();
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

shared_ptr<Specimen> & Population::tourney(vector<int>& tourneyGroup)
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
	return *specimens[rand() % specimens.size()];
}

shared_ptr<Specimen> & Population::select(int tourneySize)
{
	if (tourneySize == 0)
	{
		tourneySize++;
	}
	vector<int> tourneyGroup(tourneySize);
	for (int i = 0; i < tourneySize; i++)
	{
		tourneyGroup[i] = (rand() % specimens.size());
	}
	return tourney(tourneyGroup);
}

void Population::crossing()
{
	vector<shared_ptr<Specimen>> newPop = vector<shared_ptr<Specimen>>(specimens.size());
	shared_ptr<Specimen> parent1, parent2;
	int tourneySize = tourneyRatio * specimens.size();

	vector<shared_ptr<Specimen>> children;

	size_t i = 0;
	while (i < specimens.size())
	{
		parent1 = select(tourneySize);
		parent2 = select(tourneySize);

		children = parent1->cross(parent2, crossingChance);
		for (auto& child : children)
		{
			newPop[i++] = child;
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
	resultFile.imbue(locale("fr"));
	string filename = "results//" + graph.getName() + " " + typeid(*specimens.front()).name() +  " CC#" + to_string(crossingChance) + " TR#" + to_string(tourneyRatio) + " MV#" + to_string(mutationValue) + ".csv";
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
	int test = specimens[bestPos]->rate();
	return *specimens[bestPos];
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

int Population::getErrorMultiplier()
{
	return errorMultiplier;
}

int Population::getColorMultiplier()
{
	return colorMultiplier;
}
