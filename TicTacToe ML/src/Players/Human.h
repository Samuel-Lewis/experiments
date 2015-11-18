//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiment
//
//	@Project:	Tic Tac Toe Basic Machine Learning
//
//	@Last Updated:	2015-11-18 21:01:32
//	@Created:		2015-11-18 20:57:42
//
//===============================================//

#ifndef PLAYER_HUMAN_H
#define PLAYER_HUMAN_H

#include <string>
#include <vector>

#include "Game.h"

#include "Player.h"

class Human : public Player
{
public:
	Human(std::string);
	virtual ~Human();

	Game::TILE getMove(std::vector<Game::TOKEN>);

};

#endif // PLAYER_HUMAN_H
