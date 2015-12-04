//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiment
//
//	@Project:	Cellular Automaton Map Gen
//
//	@Last Updated:	2015-12-05 08:22:39
//	@Created:		2015-12-05 08:22:32
//
//===============================================//

#include <string>

#include "lbRNG.h"

#include "CA.h"

CA::CA(int width, int height)
{

	_width = width;
	_height = height;
	_map.resize(_width, std::vector<bool>(_width, false));

	// Options, should probably make these more dynamic...
	_pStartAlive = 0.45;
	_numIts = 2;
	_birthLim = 4;
	_deathLim = 4;

	// Randomly populate map
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			if (lbRNG::decision(_pStartAlive))
			{
				_map[x][y] = true;
			}
		}
	}	

	// Apply "formula"
	for (int i = 0; i < _numIts; i++)
	{
		_map = step(_map);
	}

}

CA::CA() : CA(40,40) {}

// Counts to see if surrounding tiles are 'alive' (true)
int CA::countAliveNeighbours(int x, int y, GRID currentMap)
{
	int numAlive = 0;

	for (int i = x-1; i < x+2; i++)
	{
		for (int j = y-1; j < y+2; j++)
		{
			if (i == x && j == y)
			{
				// Do nothing. No point in checking yourself
			} else if (i < 0 || i >= _width || j < 0 || j > _height) {
				// Walls count as "alive"
				numAlive++;
			} else if (currentMap[i][j]) {
				numAlive++;
			}
		}
	}

	return numAlive;
}

// Apply the 'rules'
GRID CA::step(GRID currentMap)
{
	// Mutable map, so we can still check old neighbours
	GRID mutMap;
	mutMap.resize(_width, std::vector<bool>(_width, false));

	int aliveN = 0;
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			aliveN = countAliveNeighbours(x,y, currentMap);
			if (currentMap[x][y])
			{
				if (aliveN < _deathLim)
				{
					// Starves
					mutMap[x][y] = false;
				} else {
					// Lives on
					mutMap[x][y] = true;
				}
			} else {
				if (aliveN > _birthLim)
				{
					// Born
					mutMap[x][y] = true;
				} else {
					// Stays dead
					mutMap[x][y] = false;
				}
			}
		}
	}
	return mutMap;
}


GRID CA::getMap()
{
	return _map;
}
