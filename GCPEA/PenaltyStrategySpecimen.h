#pragma once

#include "Specimen.h"

using namespace std;

class PenaltyStrategySpecimen : public Specimen
{
private:
	int errorMultiplier;
	int colorMultiplier;

	void mutate();
	
public:
	PenaltyStrategySpecimen();
	PenaltyStrategySpecimen(Graph* graph, float mutationValue, int errorMultiplier, int colorMultiplier);
	PenaltyStrategySpecimen(Graph* graph, float mutationValue, int errorMultiplier, int colorMultiplier, vector<int> & colors);
	~PenaltyStrategySpecimen();

	int rate();
	vector<shared_ptr<Specimen>> cross(shared_ptr<Specimen> & other, float chance);
};

