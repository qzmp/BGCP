#pragma once

#include "Specimen.h"

using namespace std;

class PenaltyStrategySpecimen : Specimen
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
	PenaltyStrategySpecimen();
	PenaltyStrategySpecimen(Graph* graph, float mutationValue, int errorMultiplier, int colorMultiplier);
	~PenaltyStrategySpecimen();
};

