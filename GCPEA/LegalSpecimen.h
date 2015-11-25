#pragma once

#include "Specimen.h"

class LegalSpecimen : public Specimen
{
private:

	void mutate();

	void fillValidColor(int node, int colorPosition);
	void fixAll();

public:
	LegalSpecimen(Graph* graph, float mutationValue, bool multi);
	LegalSpecimen(Graph* graph, float mutationValue, vector<vector<int>> colors, bool multi);
	~LegalSpecimen();

	int rate();
	vector<shared_ptr<Specimen>> cross(shared_ptr<Specimen> & other, float chance);
};

