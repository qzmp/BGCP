#pragma once

#include "Graph.h"
#include <random>
#include <ctime>
#include <set>
#include <unordered_set>
#include <numeric>
#include <algorithm>
#include <functional>

using namespace std;

class Specimen
{
private:
	vector<int> colors;
	Graph* graph;
	float mutationValue;

	void randomizeGenes();
	void mutate();
	
	bool isValidColored(int node);
	int rateNode(int node);
	
	int errorMultiplier;
	int colorMultiplier;

public:
	Specimen(Graph* graph, int errorMultiplier, int colorMultiplier, float mutationValue);
	Specimen(Specimen & other);
	Specimen();
	~Specimen();

	virtual int rate() = 0;
	
	virtual Specimen & cross1(Specimen & other);
	virtual pair<Specimen*, Specimen*> & cross2(Specimen & other);

	virtual string toString();

	virtual int getColorCount();
	virtual int getErrorCount();
};

