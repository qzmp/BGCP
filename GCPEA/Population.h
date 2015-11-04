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

public:
	Population(int size, string filename, int maxPops, float mutationValue, float tourneyRatio, float crossingChance, double ratingFunc(int colorCount, int errorCount));
	~Population();

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
};

