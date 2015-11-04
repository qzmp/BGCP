#include "Tester.h"



double Tester::countMean(vector<int> values)
{
	int sum = 0;
	for (int v : values)
	{
		sum += v;
	}
	return sum / values.size();
}

double Tester::countDeviation(vector<int> values, double mean)
{
	int sum = 0;
	for (int v : values)
	{
		sum += v - mean;
	}

	return sqrt(sum / values.size());
}

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

void Tester::testRatingFunction(int size, string filename, int maxPops, float mutationValue, float tourneyRatio, float crossingChance)
{
	double colorCountMultiplierMin = 0.1;
	double colorCountMultiplierMax = 10;
	double colorCountMultiplierStep = 0.1;

	double errorCountMultiplierMin = 0.1;
	double errorCountMultiplierMax = 10;
	double errorCountMultiplierStep = 0.1;

	for (int i = colorCountMultiplierMin; i < colorCountMultiplierMax; i += colorCountMultiplierStep)
	{

	}
}

void Tester::test(Population & pop, int genSize, int count)
{
	vector<int> bestColorCounts = vector<int>(count);
	vector<int> bestErrorCounts = vector<int>(count);

	Specimen bestSpec;;

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < genSize; j++)
		{
			pop.generateNewPopulation();
		}

		bestSpec = pop.getBest();
		bestColorCounts[i] = bestSpec.getColorCount();
		bestErrorCounts[i] = bestSpec.getErrorCount();
	}

	double avgColorCount = countMean(bestColorCounts);
	double colorDeviation = countDeviation(bestColorCounts, avgColorCount);
	double avgErrorCount = countMean(bestErrorCounts);
	double errorDeviation = countDeviation(bestErrorCounts, avgErrorCount);

	save(pop, count, avgColorCount, colorDeviation, avgErrorCount, errorDeviation);
}

void Tester::save(Population & pop, int genSize, double avgColorCount, double colorDeviation, double avgErrorCount, double errorDeviation)
{
	ofstream resultFile;
	string filename = "results//" + pop.getGraph().getName() + ".csv";
	resultFile.open(filename, ios::ate);
	string line = pop.getSize() + " | " + genSize + " | " + pop.getCrossingChance() + " | " + 
	resultFile << pop
	for (list<vector<int>>::iterator it = ratings.begin(); it != ratings.end(); it++)
	{
		vector<int> processedRatings = *it;
		resultFile << worstGrade(processedRatings) << ";";
		resultFile << averageGrade(processedRatings) << ";";
		resultFile << bestGrade(processedRatings) << "\n";

	}
	resultFile.close();
}
