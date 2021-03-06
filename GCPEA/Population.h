#pragma once

#include "Graph.h"
#include "PenaltyStrategySpecimen.h"
#include "LegalSpecimen.h"
#include "SetColorSpecimen.h"
#include <memory>

enum SpecimenType {
	Penalty,
	Legal,
	SetColor
};

class Population
{
private:
	vector<shared_ptr<Specimen>> specimens;
	Graph graph;
	int colorNumber;
	list<vector<int>> ratings;
	float mutationValue;
	float tourneyRatio;
	float crossingChance;

	SpecimenType specimenType;

	shared_ptr<Specimen> & tourney(vector<int>& tourneyGroup);

	Specimen & randomSpec();

	shared_ptr<Specimen>& select(int tourneySize);

	void crossing();

	int errorMultiplier;
	int colorMultiplier;

	int colorCount;

	bool multi;
public:
	Population(int size, string filename, float mutationValue, float tourneyRatio, float crossingChance,
		int errorMultiplier, int colorMultiplier, bool multi);
	Population(int size, string filename, float mutationValue, float tourneyRatio, float crossingChance, bool multi);
	Population(int size, string filename, float mutationValue, float tourneyRatio, float crossingChance, int colorCount, bool multi);
	~Population();

	void reset();

	int getRating(int specimenNum);
	void rateAll();

	int bestGrade(vector<int> &ratings);
	float averageGrade(vector<int> &ratings);
	int worstGrade(vector<int> &ratings);

	bool perfected();

	void generateNewPopulation();

	void saveToFile();

	Specimen& getBest();

	void writeSpec(int num);

	Graph& getGraph();
	int getSize();
	float getMutationValue();
	float getCrossingChance();
	float getTourneyRatio();
	int getErrorMultiplier();
	int getColorMultiplier();
};

