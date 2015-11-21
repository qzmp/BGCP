#include "Tester.h"



double Tester::countMean(vector<int> values)
{
	int sum = 0;
	for (int v : values)
	{
		sum += v;
	}
	return (double)sum / (double)values.size();
}

double Tester::countDeviation(vector<int> values, double mean)
{
	double sum = 0;
	for (int v : values)
	{
		sum += (v - mean) * (v - mean);
	}
	return sqrt(sum / (double)values.size());
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

void Tester::testRatingFunction(int size, string filename, int maxGens, float mutationValue, float tourneyRatio, float crossingChance)
{
	int colorCountMultiplierMin = 1;
	int colorCountMultiplierMax = 1;
	int colorCountMultiplierStep = 1;

	int errorCountMultiplierMin = 20;
	int errorCountMultiplierMax = 20;
	int errorCountMultiplierStep = 1;

	Population* testedPop = new Population();
	for (int i = colorCountMultiplierMin; i <= colorCountMultiplierMax; i += colorCountMultiplierStep)
	{
		for (int j = errorCountMultiplierMin; j <= errorCountMultiplierMax; j += errorCountMultiplierStep)
		{
			testedPop = new Population(size, filename, mutationValue, tourneyRatio, crossingChance, i, j, 0);
			test(*testedPop, maxGens, 10);
		}
		delete testedPop;
	}
}

void Tester::test(Population & pop, int genSize, int count)
{
	vector<int> bestColorCounts = vector<int>(count);
	vector<int> bestErrorCounts = vector<int>(count);

	Specimen* bestSpec;;

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < genSize; j++)
		{
			pop.generateNewPopulation();
		}

		bestSpec = &pop.getBest();
		bestColorCounts[i] = bestSpec->getColorCount();
		bestErrorCounts[i] = bestSpec->getErrorCount();
		pop.reset();
	}

	double avgColorCount = countMean(bestColorCounts);
	double colorDeviation = countDeviation(bestColorCounts, avgColorCount);
	double avgErrorCount = countMean(bestErrorCounts);
	double errorDeviation = countDeviation(bestErrorCounts, avgErrorCount);

	save(pop, genSize, avgColorCount, colorDeviation, avgErrorCount, errorDeviation);
}

void Tester::save(Population & pop, int genSize, double avgColorCount, double colorDeviation, double avgErrorCount, double errorDeviation)
{
	ofstream resultFile;
	string filename = "results//" + pop.getGraph().getName() + ".csv";
	resultFile.imbue(locale("fr"));
	resultFile.open(filename, ios::ate | ios::app);
	string line = to_string(pop.getSize()) + ";" + to_string(genSize) + ";" + to_string(pop.getCrossingChance()) + ";" + to_string(pop.getMutationValue()) + ";" + to_string(pop.getTourneyRatio()) + ";";
	resultFile << line;
	resultFile << pop.getColorMultiplier() << ";";
	resultFile << pop.getErrorMultiplier() << ";";
	resultFile << avgColorCount << ";";
	resultFile << colorDeviation << ";";
	resultFile << avgErrorCount << ";";
	resultFile << errorDeviation << "\n";
	resultFile.close();
}
