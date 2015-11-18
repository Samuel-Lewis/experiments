//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiment
//
//	@Project:	Tic Tac Toe Basic Machine Learning
//
//	@Last Updated:	2015-11-18 21:01:24
//	@Created:		2015-11-18 20:57:42
//
//===============================================//

#include <vector>
#include <string>
#include <iostream>

#include "lbLog.h"

#include "Game.h"

#include "Player.h"
#include "Human.h"

Human::Human(std::string newName) : Player(newName)
{}

Human::~Human()
{}

Game::TILE Human::getMove(std::vector<Game::TOKEN> board)
{

	// Ignore this, just to get rid of warning in compilation (for not using board)
	board.size();

	int tile;
	do
	{
		std::cout << getName() << " to move (1 - 9):" << std::endl;
		std::cin >> tile;

	} while (tile < 1 || tile > 9);

	INFO("Human ("<< getName() <<") moved.");

	return (Game::TILE)(tile-1);


}
