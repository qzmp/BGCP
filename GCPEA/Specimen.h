#pragma once

#include "Graph.h"
#include <random>
#include <ctime>
#include <set>
#include <unordered_set>
#include <numeric>
#include <algorithm>
#include <functional>
#include <memory>

using namespace std;

class Specimen
{
protected:
	vector<vector<int>> colors;
	Graph* graph;
	virtual void randomizeGenes();

	bool isValidColored(int node, int colorPosition);

	pair<int, int> getMinMaxColor();

	float mutationValue;
	virtual void mutate() = 0;

	bool multi;

public:
	Specimen(Graph* graph, float mutationValue, bool multi);
	Specimen(Graph* graph, float mutationValue, vector<vector<int>> colors, bool multi);
	Specimen();
	~Specimen();

	virtual int rate() = 0;
	virtual vector<shared_ptr<Specimen>> cross(shared_ptr<Specimen> & other, float chance) = 0;
	
	vector<vector<int>>& getColors();

	int getColorCount();
	int getErrorCount();

	//string toString();
};

