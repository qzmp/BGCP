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
}


Tester::~Tester()
{
}
