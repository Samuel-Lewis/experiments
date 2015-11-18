//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiment
//
//	@Project:	Tic Tac Toe Basic Machine Learning
//
//	@Last Updated:	2015-11-18 21:01:42
//	@Created:		2015-11-18 20:57:42
//
//===============================================//

#include <vector>
#include <string>
#include <iostream>

#include "lbLog.h"

#include "Game.h"

#include "Player.h"
#include "Tree.h"

#define SWING 0.5

Tree::Tree(std::string newName) : Player(newName)
{
	goesFirstTree = NULL;
	goesSecondTree = NULL;
	currentState = NULL;
}

Tree::~Tree()
{}

void Tree::prepare(bool goesFirst)
{
	// Tree hasn't been generated, so do so now
	if (goesFirstTree == NULL)
	{
		INFO("No goesFirstTree detected. Building now...");
		goesFirstTree = new Node;
		goesFirstTree->board = std::vector<Game::TOKEN>(9,Game::NONE);
		_popBranch(goesFirstTree, true);
	}

	if (goesSecondTree == NULL)
	{
		INFO("No goesSecondTree detected. Building now...");
		goesSecondTree = new Node;
		goesSecondTree->board = std::vector<Game::TOKEN>(9,Game::NONE);
		_popBranch(goesSecondTree, false);

	}

	if (goesFirstTree == NULL)
	{
		ERROR("First tree did not build");
	}

	if (goesSecondTree == NULL)
	{
		ERROR("Second tree did not build");
	}

	// Determine which logic "path" to follow
	if (goesFirst)
	{
		currentState = goesFirstTree;
		INFO("Set currentState to goesFirstTree");
	} else{
		currentState = goesSecondTree;
		INFO("Set currentState to goesFirstTree");
	}

	if (_dec.size() > 0)
	{
		_dec.clear();
	}
}

void Tree::win()
{
	for (int i = 0; i < (int)_dec.size(); i++)
	{
		_dec[i]->weight *= 1.0 + SWING;
	}
}

void Tree::lose()
{
	for (int i = 0; i < (int)_dec.size(); i++)
	{
		_dec[i]->weight *= 1.0 - SWING;
	}
}


Game::TILE Tree::getMove(std::vector<Game::TOKEN> board)
{
	std::cout << getName() << " is thinking..." << std::endl;

	// Determine oppositions move
	for (int i = 0; i < (int)board.size(); i++)
	{
		if (board[i] != currentState->board[i])
		{
			INFO("Attempting to move to next perm...");
			currentState = currentState->perms[i];
			INFO("Moved to next permutation");
			break;
		}
	}

	if (currentState == NULL)
	{
		FATAL("currentState = NULL");
	}
	
	INFO("Calculate perm...");
	int permToUse = _calcPerm();
	INFO("Calc'd perm");

	currentState = currentState->perms[permToUse];
	_dec.push_back(currentState);

	return (Game::TILE)permToUse;

}

int Tree::_calcPerm()
{

	float mostEffect = -100000.0;
	int permToUse = -1;

	// Calculate the most effective piece to place down for each alternative
	for (int i = 0; i < (int)currentState->board.size(); i++)
	{
		// Only worry about placing on empty tiles
		if (currentState->board[i] == Game::NONE)
		{
			// Make sure things work
			if (currentState->perms[i] == NULL)
			{
				FATAL("Perm is NULL (shouldn't be)");
			}

			// Winner of next round
			Game::TOKEN nextRWinner = Game::detWinner(currentState->perms[i]->board);

			// Determine if can win in next move
			if (nextRWinner == getToken())
			{
				INFO("Go for win");
				return i;

			} else {
				// Determine if opponenet will win in their next move
				for (int j = 0; j < (int)currentState->perms[i]->perms.size(); j++)
				{
					if (currentState->perms[i]->perms[j] != NULL)
					{
						// They can win, so try to block
						if (Game::detWinner(currentState->perms[i]->perms[j]->board) == getOppToken())
						{
							INFO("Go for block");
							return j;
						}
					}
				}

				// Try and choose best option
				float numWin = (float)_countStat(currentState->perms[i], WIN, 1);
				float numLose = (float)_countStat(currentState->perms[i], LOSE, 1);

				float effect = 0;

				// Divide by 0 check. If 0 though, is a pretty good score. would follow this path
				if (numLose == 0)
				{
					effect = numWin;
				} else {
					effect = (numWin / numLose) * currentState->perms[i]->weight;
				}

				if (effect < 0)
				{
					WARN("Effect < 0: " << effect);
				}

				// Get max
				if (effect > mostEffect)
				{
					mostEffect = effect;
					permToUse = i;
					
				}		
			}
		}
	}

	return permToUse;

}

float Tree::_countStat(Node* root, STAT check, int depth)
{

	if (root == NULL)
	{
		WARN("Bad root in countStat");
		return 0;
	}

	// Check if this layer satisfies the value
	float calc = 0;
	if (root->winStatus == check)
	{
		calc++;
	}

	if (root->winStatus != NONE)
	{
		return calc/depth;
	}

	// For all the 9 links down, check if they have permutations
	// Count the stats in them
	for (int i = 0; i < (int)(root->board).size(); i++)
	{
		if (root->perms[i] != NULL)
		{
			calc += _countStat(root->perms[i], check, depth+1);
		}
	}

	return calc/depth;
}

void Tree::_popBranch(Node* root, bool myFirst)
{
	root->weight = 1.0;
	root->myTurn = myFirst;

	// Determine current Node's result (if played)
	Game::TOKEN winner = Game::detWinner(root->board);
	if (winner == Game::NONE)
	{
		// Determine if there was no winner because it was a draw or because it's not over
		bool full = true;
		for (int i = 0; i < (int)(root->board).size(); i++)
		{
			if (root->board[i] == Game::NONE)
			{
				full = false;
				break;
			}
		}
		if (full)
		{
			// Was a draw
			root->winStatus = DRAW;
		} else {
			// Not over
			root->winStatus = NONE;
		}

	} else if (winner == getToken()) {
		// Wins
		root->winStatus = WIN;
	} else {
		// Loses
		root->winStatus = LOSE;
	}

	// Populate next layer only if move is viable and game didn't end
	if (root->winStatus == NONE)
	{
		root->perms.resize(9, NULL);
		for (int i = 0; i < (int)(root->board).size(); i++)
		{
			// If nothing played on tile, branch down a play on it
			if (root->board[i] == Game::NONE)
			{
				root->perms[i] = new Node;
				root->perms[i]->board = root->board;
				if (root->myTurn)
				{
					root->perms[i]->board[i] = getToken();
				} else {
					root->perms[i]->board[i] = getOppToken();
				}

				_popBranch(root->perms[i], !(root->myTurn));

			}
		}

	}

}
