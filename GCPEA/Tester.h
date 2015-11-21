#pragma once

#include "Population.h"

class Tester
{
private:
	pair<int, int> generations;
	int genStep;
	pair<int, int> size;
	int sizeStep;
	pair<double, double> mutationValues;
	double mutStep;
	pair<double, double> crossingChances;
	double crossStep;
	pair<double, double> tourneyRatios;
	double tourneyStep;
	function<double(int, int)> ratingFunc;

	double countMean(vector<int> values);
	double countDeviation(vector<int> values, double mean);

public:
	Tester();
	Tester(pair<int, int> generations, pair<int, int> size, pair<double, double> mutationValues, pair<double, double> crossingChances, pair<double, double> tourneyRatios);
	~Tester();

	void setGenerationBounds(int min, int max, int step);
	void setSizeBounds(int min, int max, int step);
	void setMutationBounds(double min, double max, double step);
	void setCrossingBounds(double min, double max, double step);
	void setTourneyBounds(double min, double max, double step);

	void testRatingFunction(int size, string filename, int maxPops, float mutationValue, float tourneyRatio, float crossingChance);
	void test(Population& pop, int genSize, int count);

	void save(Population& pop, int genSize, double avgColorCount, double colorDeviation, double avgErrorCount, double errorDeviation);

};

