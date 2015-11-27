#pragma once

#include "Specimen.h"

class SetColorSpecimen : Specimen
{
private:

	int colorCount;

	void mutate();

public:
	SetColorSpecimen(Graph* graph, float mutationValue, bool multi, int colorCount);
	SetColorSpecimen(Graph* graph, float mutationValue, vector<vector<int>> colors, bool multi, int colorCount);
	~SetColorSpecimen();

	int rate();
	vector<shared_ptr<Specimen>> cross(shared_ptr<Specimen> & other, float chance);
};

