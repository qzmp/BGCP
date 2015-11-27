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

	int colorMultiplier;
	int errorMultiplier;
	int colorCount;

	SpecimenType specimenType;

	bool multi;

	int testCount = 10;

	double countMean(vector<int> values);
	double countDeviation(vector<int> values, double mean);

	void testValid(int which, float min, float max, float step);
	void testPenalty(int which, float min, float max, float step);
	void testSetColor(int which, float min, float max, float step);

public:
	Tester();
	~Tester();

	void setStartingParams(int generations, int size, string filename, float mutationValue, float tourneyRatio, float crossingChance, bool multi);
	void setStartingParams(int generations, int size, string filename, float mutationValue, float tourneyRatio, float crossingChance,
		int colorMultiplier, int errorMultiplier, bool multi);
	void setStartingParams(int generations, int size, string filename, float mutationValue, float tourneyRatio, float crossingChance, 
		int colorCount, bool multi);

	void testParameter(int which, float min, float max, float step);

	void testRatingFunction(int size, string filename, int maxPops, float mutationValue, float tourneyRatio, float crossingChance);
	void test(Population& pop, int genSize, int count);

	void save(Population& pop, int genSize, double avgColorCount, double colorDeviation, double avgErrorCount, double errorDeviation);

};

