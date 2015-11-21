#pragma once

#include "Specimen.h"

class LegalSpecimen : public Specimen
{
private:

	void mutate();

	vector<int> fillSurroundings(int mid, int range);
	void fillValidColor(int node);
	void fixAll();

public:
	LegalSpecimen();
	LegalSpecimen(Graph* graph, float mutationValue);
	LegalSpecimen(Graph* graph, float mutationValue, vector<int> & colors);
	~LegalSpecimen();

	int rate();
	vector<shared_ptr<Specimen>> cross(shared_ptr<Specimen> & other, float chance);
};

