//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiment
//
//	@Project:	Tic Tac Toe Basic Machine Learning
//
//	@Last Updated:	2015-11-18 21:01:39
//	@Created:		2015-11-18 20:57:42
//
//===============================================//


#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Game.h"

class Player
{
public:
	Player(std::string);
	virtual ~Player();

	std::string getName();

	virtual Game::TILE getMove(std::vector<Game::TOKEN>) = 0;

	virtual void prepare(bool);

	void setToken(Game::TOKEN);
	Game::TOKEN getToken();
	Game::TOKEN getOppToken();

	virtual void win();
	virtual void lose();
	virtual void draw();

private:

	std::string _name;

	Game::TOKEN _token;


};

#endif // PLAYER_H
