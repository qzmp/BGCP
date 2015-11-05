#pragma once

#include "Graph.h"
#include "Specimen.h"

class Population
{
private:
	vector<Specimen> specimens;
	Graph graph;
	int colorNumber;
	list<vector<int>> ratings;
	float mutationValue;
	float tourneyRatio;
	float crossingChance;

	Specimen & tourney(vector<int>& tourneyGroup);

	Specimen & randomSpec();

	Specimen & select(int tourneySize);

	void crossing();

	int errorMultiplier;
	int colorMultiplier;

public:
	Population(int size, string filename, float mutationValue, float tourneyRatio, float crossingChance, int errorMultiplier, int colorMultiplier);
	Population();
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

