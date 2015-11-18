//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiment
//
//	@Project:	Tic Tac Toe Basic Machine Learning
//
//	@Last Updated:	2015-11-18 21:01:45
//	@Created:		2015-11-18 20:57:42
//
//===============================================//


#ifndef PLAYER_TREE_H
#define PLAYER_TREE_H

#include <string>
#include <vector>

#include "Game.h"

#include "Player.h"

class Tree : public Player
{
public:
	Tree(std::string);
	virtual ~Tree();

	Game::TILE getMove(std::vector<Game::TOKEN>);

	enum STAT
	{
		NONE,
		LOSE,
		DRAW,
		WIN
	};

	struct Node
	{
		std::vector<Game::TOKEN> board;
		std::vector<Node*> perms;

		STAT winStatus;
		float weight;
		bool myTurn;

	};

	void prepare(bool);

	void win();
	void lose();

private:
	Node* goesFirstTree;
	Node* goesSecondTree;

	Node* currentState;

	float _countStat(Node*, STAT, int);
	int _calcPerm();

	int _numLose(Node*);
	int _numWin(Node*);

	void _popBranch(Node*, bool);

	std::vector<Node*> _dec;

};

#endif // PLAYER_TREE_H
