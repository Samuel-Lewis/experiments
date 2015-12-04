//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiment
//
//	@Project:	Cellular Automaton Map Gen
//
//	@Last Updated:	2015-12-05 08:22:43
//	@Created:		2015-12-05 08:22:32
//
//===============================================//

#ifndef CA_H
#define CA_H

#include <vector>

typedef std::vector< std::vector<bool> > GRID;

class CA
{
	public:
		CA();
		CA(int, int);
		~CA();

		GRID getMap();

	private:
		GRID _map;

		int _width;
		int _height;

		float _pStartAlive;
		int _numIts;
		
		int _deathLim;
		int _birthLim;

		GRID step(GRID);
		int countAliveNeighbours(int, int, GRID);

};

#endif // CA_H
