//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiment
//
//	@Project:	Tic Tac Toe Basic Machine Learning
//
//	@Last Updated:	2015-11-18 21:18:33
//	@Created:		2015-11-18 20:57:42
//
//===============================================//

#include <vector>
#include <iostream>
#include <string>

#include "lbLog.h"
#include "lbRNG.h"

#include "Game.h"

#include "Player.h"

Game::Game()
{
	_board.resize(9,NONE);

	p1Wins = 0;
	p2Wins = 0;
	draws = 0;
}

Game::~Game()
{

}

void Game::playGame()
{
	INFO("Started new game");
	int numPlays = 0;

	INFO("NONE'd out board");
	_board.clear();
	_board.resize(9,NONE);

	// Random choice of who goes first
	TOKEN toMove = lbRNG::linear(0.0,1.0) > 0.5 ? X : O;

	_p1->setToken(X);
	_p2->setToken(O);

	// Prepare contenders
	if (toMove == X)
	{
		INFO(_p1->getName() << " goes first");
		_p1->prepare(true);
		_p2->prepare(false);
	} else {
		INFO(_p2->getName() << " goes first");
		_p1->prepare(false);
		_p2->prepare(true);
	}

	TOKEN winner = NONE;

	while(winner == NONE && numPlays < 9)
	{
		INFO("New move");
		printBoard();
		// Switch between players making their moves
		if (toMove == X)
		{
			TILE move;
			do
			{
				move = _p1->getMove(_board);
			} while (_board[move] != NONE);

			_board[move] = X;
			toMove = O;
		} else {
			TILE move;
			do
			{
				move = _p2->getMove(_board);
			} while (_board[move] != NONE);

			_board[move] = O;
			toMove = X;
		}

		winner = detWinner(_board);
		numPlays++;
	}

	INFO("Game ended");

	printBoard();

	std::cout << "=== GAME OVER! ===" << std::endl;

	// determine actual winner from result
	if (winner == X)
	{
		_p1->win();
		_p2->lose();
		p1Wins++;
		INFO("Player 1 wins");
		std::cout << _p1->getName() << " WINS!" << std::endl;
	} else if (winner == O) {
		_p1->win();
		_p2->lose();
		p2Wins++;
		INFO("Player 2 wins");
		std::cout << _p2->getName() << " WINS!" << std::endl;
	} else {
		// run out of turns, so it's a draw
		_p1->draw();
		_p2->draw();
		draws++;
		INFO("Draw match");
		std::cout << "DRAW!" << std::endl;
	}

	int totalRounds = p1Wins + p2Wins + draws;

	// Scores (with percentages)
	std::cout << "SCORES:" << std::endl;
	std::cout << _p1->getName() <<": " << p1Wins << " (" << (float)(100*p1Wins/(totalRounds)) << "%)  |  ";
	std::cout << _p2->getName() <<": " << p2Wins << " (" << (float)(100*p2Wins/(totalRounds)) << "%)" << std::endl;
	std::cout << "Draws: " << draws << " (" << (float)(100*draws/(totalRounds)) << "%)" << std::endl;

}

Game::TOKEN Game::detWinner(std::vector<TOKEN> board)
{
	// LEFT col win
	if (checkNeigh(W,NW,SW, board) && board[W] != NONE)
	{
		return board[W];
	}

	// CENTER col win
	if (checkNeigh(C,N,S, board) && board[C] != NONE)
	{
		return board[C];
	}

	// RIGHT col win
	if (checkNeigh(E,NE,SE, board) && board[E] != NONE)
	{
		return board[E];
	}

	// TOP row win
	if (checkNeigh(N,NW,NE, board) && board[N] != NONE)
	{
		return board[N];
	}

	// CENTER row win
	if (checkNeigh(C,W,E, board) && board[C] != NONE)
	{
		return board[C];
	}

	// BOTTOM row win
	if (checkNeigh(S,SW,SE, board) && board[S] != NONE)
	{
		return board[S];
	}

	// LT->RB diag win
	if (checkNeigh(C,NW,SE, board) && board[C] != NONE)
	{
		return board[C];
	}

	// RT->LB diag win
	if (checkNeigh(C,NE,SW, board) && board[C] != NONE)
	{
		return board[C];
	}

	// No win
	return NONE;

}

// '==' on 3 tiles
bool Game::checkNeigh(TILE a, TILE b, TILE c, std::vector<TOKEN> board)
{
	return (board[a] == board[b] && board[a] == board[c]);
}

void Game::printBoard()
{
	// Print into a 3x3 grid pattern. Eg:
	//  X | O | X
	// -----------
	//    | O | X 
	// -----------
	//    | X | O

	std::string out = "\n";

	out += "\t " + tokenToIcon(_board[NW]) + " | " + tokenToIcon(_board[N]) + " | " + tokenToIcon(_board[NE]) + "\n";
	out += "\t-----------\n";
	out += "\t " + tokenToIcon(_board[W]) + " | " + tokenToIcon(_board[C]) + " | " + tokenToIcon(_board[E]) + "\n";
	out += "\t-----------\n";
	out += "\t " + tokenToIcon(_board[SW]) + " | " + tokenToIcon(_board[S]) + " | " + tokenToIcon(_board[SE]) + "\n";

	INFO("Board print: " << out);
	std::cout << out << std::endl;
}

// Convert enum to string
std::string Game::tokenToIcon(TOKEN m)
{
	switch (m)
	{
		case X : return "X";
		case O : return "O";
		default: return " ";
	}
}

void Game::setPlayers(Player* p1, Player* p2)
{
	// Want to call a ->getName so we can check that it actually was asigned properly
	_p1 = p1;
	INFO("Set p1 as " << _p1->getName());

	_p2 = p2;
	INFO("Set p2 as " << _p2->getName());

	std::cout << _p1->getName() << " has entered the game as player 1!" << std::endl;
	std::cout << _p2->getName() << " has entered the game as player 2!" << std::endl;

}
