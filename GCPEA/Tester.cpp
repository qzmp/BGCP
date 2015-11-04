#include "Tester.h"



Tester::Tester()
{
	generations = pair<int, int>(10, 2000);
	size = pair<int, int>(10, 200);
	mutationValues = pair<double, double>(0, 0.3);
	crossingChances = pair<double, double>(0, 1);
	tourneyRatios = pair<double, double>(0.01, 0.2);
}

Tester::Tester(pair<int, int> generations, pair<int, int> size, pair<double, double> mutationValues, pair<double, double> crossingChances, pair<double, double> tourneyRatios)
{
	this->generations = generations;
	this->size = size;
	this->mutationValues = mutationValues;
	this->crossingChances = crossingChances;
	this->tourneyRatios = tourneyRatios;
}


Tester::~Tester()
{
}

void Tester::setGenerationBounds(int min, int max, int step)
{
	generations = pair<int, int>(min, max);
	genStep = step;
}

void Tester::setSizeBounds(int min, int max, int step)
{
	size = pair<int, int>(min, max);
	sizeStep = step;
}

void Tester::setMutationBounds(double min, double max, double step)
{
	mutationValues = pair<double, double>(min, max);
	mutStep = step;
}

void Tester::setCrossingBounds(double min, double max, double step)
{
	crossingChances = pair<double, double>(min, max);
	crossStep = step;
}

void Tester::setTourneyBounds(double min, double max, double step)
{
	tourneyRatios = pair<double, double>(min, max);
	tourneyStep = step;
}
