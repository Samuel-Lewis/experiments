//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiment
//
//	@Project:	Tic Tac Toe Basic Machine Learning
//
//	@Last Updated:	2015-11-18 21:05:03
//	@Created:		2015-11-18 20:57:42
//
//===============================================//

#include <iostream>

#include "lbLog.h"

#include "Game.h"

#include "Human.h"
#include "Tree.h"

int main()
{
	lbLog::startLog("logs/","",true);


	Game game;

	game.setPlayers(new Human("HumanSteve"), new Tree("TreeJake"));

	do
	{
		std::cout << "=== NEW GAME! ===" << std::endl;
		game.playGame();
	} while (true);



	lbLog::endLog();
	return 0;
}
