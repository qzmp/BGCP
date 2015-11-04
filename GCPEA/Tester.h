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

public:
	Tester();
	Tester(pair<int, int> generations, pair<int, int> size, pair<double, double> mutationValues, pair<double, double> crossingChances, pair<double, double> tourneyRatios);
	~Tester();
};

