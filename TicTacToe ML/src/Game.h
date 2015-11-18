//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiment
//
//	@Project:	Tic Tac Toe Basic Machine Learning
//
//	@Last Updated:	2015-11-18 21:16:49
//	@Created:		2015-11-18 20:57:42
//
//===============================================//

#ifndef GAME_H
#define GAME_H

#include <vector>

#include "lbLog.h"

// Stop cyclic inclusions
class Player;

class Game
{
public:

	Game();
	~Game();

	enum TOKEN
	{
		X,
		O,
		NONE
	};

	enum TILE
	{
		NW,
		N,
		NE,
		W,
		C,
		E,
		SW,
		S,
		SE
	};

	void setPlayers(Player*, Player*);

	void playGame();

	void printBoard();

	static std::string tokenToIcon(TOKEN);

	static TOKEN detWinner(std::vector<TOKEN>);


private:
	std::vector<TOKEN> _board;

	Player* _p1;
	Player* _p2;

	int p1Wins;
	int p2Wins;
	int draws;

	static bool checkNeigh(TILE,TILE,TILE, std::vector<TOKEN>);

};

#endif // GAME_H
