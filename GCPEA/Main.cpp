#include "Tester.h"
#include <iostream>

const string SPECIMEN_TYPES = "1. Legal BCP\n2. Legal BMCP\n3. Penalty BCP\n4. Penalty BMCP\n5. SetColor BCP\n6. SetColor BMCP\n";

int main()
{
	srand(time(NULL));

	char key = '0';
	while (key != 'q')
	{
		cout << SPECIMEN_TYPES;
		cout <<
	}
	
	
	clock_t beginTime = clock();
	int maxPops = 100;
	
	Population p = Population(100, "GEOM20.col", 0.06f, 0.05f, 0.5f, 1, false);
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
	p.getBest();
	//cout << "best: " << p.getBest().toString();

	p.saveToFile();
	
	/*
	Tester t;
	t.setStartingParams(500, 70, "GEOM100.col", 0.06f, 0.05f, 0);
	t.testGenerationCount();
	*/
	return 0;
	
}