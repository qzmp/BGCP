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
	void mutate2();
	bool isValidColored(int node);

	vector<int> fillSurroundings(int mid, int range);
	void fillValidColor(int color);
	void fixAll();

	function <double(int, int)> getRating;

public:
	Specimen(Graph* graph, float mutationValue, double ratingFunc(int colorCount, int errorCount));
	Specimen(Specimen & parent1, Specimen & parent2);
	Specimen(Specimen & other);
	Specimen();
	~Specimen();

	int rate();
	int rateFenotype();
	pair<Specimen*, Specimen*>& cross(Specimen & other);

	string toString();
	
};

