#pragma once

#include "Specimen.h"

class PenaltyStrategySpecimen : public Specimen
{
private:
	int errorMultiplier;
	int colorMultiplier;

	void mutate();
	
public:
	PenaltyStrategySpecimen(Graph* graph, float mutationValue, int errorMultiplier, int colorMultiplier, bool multi);
	PenaltyStrategySpecimen(Graph* graph, float mutationValue, int errorMultiplier, int colorMultiplier, vector<vector<int>> colors, bool multi);
	~PenaltyStrategySpecimen();

	int rate();
	vector<shared_ptr<Specimen>> cross(shared_ptr<Specimen> & other, float chance);
};

