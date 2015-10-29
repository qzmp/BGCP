#pragma once

#include "Graph.h"
#include <random>
#include <ctime>
#include <set>
#include <unordered_set>
#include <numeric>
#include <algorithm>

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
	bool isValidColored(int node);

	void fillValidColor(int color);
	void fixAll();


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

