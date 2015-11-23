#pragma once

#include "Population.h"

class Tester
{
private:
	int generations;
	int size;
	string filename;
	float mutationValue;
	float tourneyRatio;
	float crossingChance;

	int testCount = 10;

	double countMean(vector<int> values);
	double countDeviation(vector<int> values, double mean);

public:
	Tester();
	~Tester();

	void setStartingParams(int generations, int size, string filename, float mutationValue, float tourneyRatio, float crossingChance);

	void testCrossingChance();
	void testTourneyRatio();
	void testMutationValue();
	void testPopSize();
	void testGenerationCount();

	void testRatingFunction(int size, string filename, int maxPops, float mutationValue, float tourneyRatio, float crossingChance);
	void test(Population& pop, int genSize, int count);

	void save(Population& pop, int genSize, double avgColorCount, double colorDeviation, double avgErrorCount, double errorDeviation);

};

