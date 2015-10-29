#include "Population.h"
#include <iostream>

int main()
{


	clock_t beginTime = clock();
	int maxPops = 2000;
	
	Population p = Population(100, "GEOM100.col", maxPops, 0.01f, 0.1f, 0.7f);
	int i = 0;

	while (!p.perfected() && i < maxPops)
	{
		//begin_time = clock();
		p.generateNewPopulation();
		//cout << "czas krzyzowania" << float(clock() - begin_time) / CLOCKS_PER_SEC <<"\n";

		i++;
		if (i % 10 == 0)
			cout << i << "\n";
	}

	cout << "czas kolorowania algorytmem genetycznym:" << float(clock() - beginTime) / CLOCKS_PER_SEC << "\n";
	cout << "best: " << p.getBest().toString();

	p.saveToFile();

	return 0;
}