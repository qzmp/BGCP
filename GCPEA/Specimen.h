#pragma once

#include "Graph.h"
#include <random>
#include <ctime>
#include <set>
#include <unordered_set>
#include <numeric>

using namespace std;

class Specimen
{
private:
	vector<int> colors;
	Graph* graph;
	float mutationValue;

	void randomizeGenes();
	void mutate();
	void mutate2();
	bool validColor(int color);

	vector<int> getFilledSet(int middle, int range);
	int fix(int color);
	void fix();


public:
	Specimen(Graph* graph, float mutationValue);
	Specimen(Specimen & parent1, Specimen & parent2);
	Specimen(Specimen & other);
	Specimen();
	~Specimen();

	int rate();
	pair<Specimen*, Specimen*>& cross(Specimen & other);

	string toString();
	
};

