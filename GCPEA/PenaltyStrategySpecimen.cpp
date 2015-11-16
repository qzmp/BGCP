#include "PenaltyStrategySpecimen.h"



PenaltyStrategySpecimen::PenaltyStrategySpecimen()
{
}

PenaltyStrategySpecimen::PenaltyStrategySpecimen(Graph * graph, float mutationValue, int errorMultiplier, int colorMultiplier) 
	: graph(graph), mutationValue(mutationValue), errorMultiplier(errorMultiplier), colorMultiplier(colorMultiplier)
{
}


PenaltyStrategySpecimen::~PenaltyStrategySpecimen()
{
}
