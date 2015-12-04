//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiment
//
//	@Project:	Cellular Automaton Map Gen
//
//	@Last Updated:	2015-12-05 08:22:49
//	@Created:		2015-12-05 08:22:32
//
//===============================================//


#include <iostream>

#include "CA.h"

int main()
{
	// Generate new map
	CA* reg = new CA(40,40);
	GRID map = reg->getMap();


	// Print out the map
	char out = ' ';
	for (int x = 0; x < (int)map.size(); x++)
	{
		for (int y = 0; y < (int)map[x].size(); y++)
		{
			// map is full of bools, diff between them
			out = map[x][y] ? 'X' : ' ';
			std::cout << out;
		}

		std::cout << std::endl;
	}

	return 0;
}
