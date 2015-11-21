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
	vector<int> colors;
	Graph* graph;
	float mutationValue;

	void randomizeGenes();
	virtual void mutate() = 0;
	
	bool isValidColored(int node);
	int rateNode(int node);

public:
	Specimen(Graph* graph, float mutationValue);
	Specimen(Graph* graph, float mutationValue, vector<int> & colors);
	Specimen();
	~Specimen();

	virtual int rate() = 0;
	virtual vector<shared_ptr<Specimen>> cross(shared_ptr<Specimen> & other, float chance) = 0;
	
	string toString();
	vector<int>& getColors();

	int getColorCount();
	int getErrorCount();
};

