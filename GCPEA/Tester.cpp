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

void Tester::testValid(int which, float min, float max, float step)
{
	Population* testedPop;
	for (float i = min; i <= max; i += step)
	{
		switch (which)
		{
		case 1:
			testedPop = new Population(size, filename, mutationValue, tourneyRatio, crossingChance, multi);
			test(*testedPop, i, testCount);
			break;
		case 2:
			testedPop = new Population(i, filename, mutationValue, tourneyRatio, crossingChance, multi);
			test(*testedPop, generations, testCount);
			break;
		case 3:
			testedPop = new Population(size, filename, i, tourneyRatio, crossingChance, multi);
			test(*testedPop, generations, testCount);
			break;
		case 4:
			testedPop = new Population(size, filename, mutationValue, i, crossingChance, multi);
			test(*testedPop, generations, testCount);
			break;
		case 5:
			testedPop = new Population(size, filename, mutationValue, tourneyRatio, i, multi);
			test(*testedPop, generations, testCount);
			break;
		}
	}
}

void Tester::testPenalty(int which, float min, float max, float step)
{
	Population* testedPop;
	for (float i = min; i <= max; i += step)
	{
		switch (which)
		{
		case 1:
			testedPop = new Population(size, filename, mutationValue, tourneyRatio, crossingChance, colorMultiplier, errorMultiplier, multi);
			test(*testedPop, i, testCount);
			break;
		case 2:
			testedPop = new Population(i, filename, mutationValue, tourneyRatio, crossingChance, colorMultiplier, errorMultiplier, multi);
			test(*testedPop, generations, testCount);
			break;
		case 3:
			testedPop = new Population(size, filename, i, tourneyRatio, crossingChance, colorMultiplier, errorMultiplier, multi);
			test(*testedPop, generations, testCount);
			break;
		case 4:
			testedPop = new Population(size, filename, mutationValue, i, crossingChance, colorMultiplier, errorMultiplier, multi);
			test(*testedPop, generations, testCount);
			break;
		case 5:
			testedPop = new Population(size, filename, mutationValue, tourneyRatio, i, colorMultiplier, errorMultiplier, multi);
			test(*testedPop, generations, testCount);
			break;
		case 6:
			for (int j = min; j <= max; j++)
			{
				testedPop = new Population(size, filename, mutationValue, tourneyRatio, crossingChance, i, j, multi);
				test(*testedPop, generations, testCount);
			}
			break;
		}
	}
}

void Tester::testSetColor(int which, float min, float max, float step)
{
	Population* testedPop;
	for (float i = min; i <= max; i += step)
	{
		switch (which)
		{
		case 1:
			testedPop = new Population(size, filename, mutationValue, tourneyRatio, crossingChance, colorCount, multi);
			test(*testedPop, i, testCount);
			break;
		case 2:
			testedPop = new Population(i, filename, mutationValue, tourneyRatio, crossingChance, colorCount, multi);
			test(*testedPop, generations, testCount);
			break;
		case 3:
			testedPop = new Population(size, filename, i, tourneyRatio, crossingChance, colorCount, multi);
			test(*testedPop, generations, testCount);
			break;
		case 4:
			testedPop = new Population(size, filename, mutationValue, i, crossingChance, colorCount, multi);
			test(*testedPop, generations, testCount);
			break;
		case 5:
			testedPop = new Population(size, filename, mutationValue, tourneyRatio, i, colorCount, multi);
			test(*testedPop, generations, testCount);
			break;
		case 6:
			testedPop = new Population(size, filename, mutationValue, tourneyRatio, crossingChance, i, multi);
			test(*testedPop, generations, testCount);
			break;
		}
	}
}

Tester::Tester()
{
}

Tester::~Tester()
{
}

void Tester::setStartingParams(int generations, int size, string filename, float mutationValue, float tourneyRatio, float crossingChance, bool multi)
{
	this->generations = generations;
	this->size = size;
	this->filename = filename;
	this->mutationValue = mutationValue;
	this->tourneyRatio = tourneyRatio;
	this->crossingChance = crossingChance;
	this->multi = multi;
	this->specimenType = Legal;
}

void Tester::setStartingParams(int generations, int size, string filename, float mutationValue, float tourneyRatio, float crossingChance, 
	int colorMultiplier, int errorMultiplier, bool multi)
{
	this->generations = generations;
	this->size = size;
	this->filename = filename;
	this->mutationValue = mutationValue;
	this->tourneyRatio = tourneyRatio;
	this->crossingChance = crossingChance;
	this->colorMultiplier = colorMultiplier;
	this->errorMultiplier = errorMultiplier;
	this->multi = multi;
	this->specimenType = Penalty;
}

void Tester::setStartingParams(int generations, int size, string filename, float mutationValue, float tourneyRatio, float crossingChance, int colorCount, bool multi)
{
	this->generations = generations;
	this->size = size;
	this->filename = filename;
	this->mutationValue = mutationValue;
	this->tourneyRatio = tourneyRatio;
	this->crossingChance = crossingChance;
	this->colorCount = colorCount;
	this->multi = multi;
	this->specimenType = SetColor;
}

void Tester::testParameter(int which, float min, float max, float step)
{
	
	
}

void Tester::testCrossingChance()
{
	float crossingChanceMin = 0;
	float crossingChanceMax = 1;
	float crossingChanceStep = 0.05;

	Population* testedPop = new Population();
	for (float i = crossingChanceMin; i <= crossingChanceMax; i += crossingChanceStep)
	{
		testedPop = new Population(size, filename, mutationValue, tourneyRatio, i, 1, multi);
		test(*testedPop, generations, testCount);
		delete testedPop;
	}
}

void Tester::testMutationValue()
{
	float mutationChanceMin = 0;
	float mutationChanceMax = 0.5;
	float mutationChanceStep = 0.01;

	Population* testedPop = new Population();
	for (float i = mutationChanceMin; i <= mutationChanceMax; i += mutationChanceStep)
	{
		testedPop = new Population(size, filename, i, tourneyRatio, crossingChance, 1, multi);
		test(*testedPop, generations, testCount);
		delete testedPop;
	}
}

void Tester::testTourneyRatio()
{
	float tourneyRatioMin = 0;
	float tourneyRatioMax = 0.5;
	float tourneyRatioStep = 0.05;

	Population* testedPop = new Population();
	for (float i = tourneyRatioMin; i <= tourneyRatioMax; i += tourneyRatioStep)
	{
		testedPop = new Population(size, filename, mutationValue, i, crossingChance, 1, multi);
		test(*testedPop, generations, testCount);
		delete testedPop;
	}
}

void Tester::testPopSize()
{
	int popSizeMin = 2;
	int popSizeMax = 100;
	int popSizeStep = 10;

	Population* testedPop = new Population();
	for (int i = popSizeMin; i <= popSizeMax; i += popSizeStep)
	{
		testedPop = new Population(i, filename, mutationValue, tourneyRatio, crossingChance, 1, multi);
		test(*testedPop, generations, testCount);
		delete testedPop;
	}
}

void Tester::testGenerationCount()
{
	int genCountMin = 5;
	int genCountMax = 1000;
	int genCountStep = 100;

	Population* testedPop = new Population();
	for (int i = genCountMin; i <= genCountMax; i += genCountStep)
	{
		testedPop = new Population(size, filename, mutationValue, tourneyRatio, crossingChance, 1, multi);
		test(*testedPop, i, testCount);
		delete testedPop;
	}
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
			testedPop = new Population(size, filename, mutationValue, tourneyRatio, crossingChance, i, j, 1, multi);
			test(*testedPop, maxGens, testCount);
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
	resultFile << avgColorCount << ";";
	resultFile << colorDeviation << ";";
	resultFile << avgErrorCount << ";";
	resultFile << errorDeviation << "\n";
	resultFile.close();
}
