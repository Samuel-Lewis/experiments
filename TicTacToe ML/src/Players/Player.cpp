//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiment
//
//	@Project:	Tic Tac Toe Basic Machine Learning
//
//	@Last Updated:	2015-11-18 21:01:36
//	@Created:		2015-11-18 20:57:42
//
//===============================================//

#include <vector>
#include <string>

#include "lbLog.h"

#include "Player.h"

#include "Game.h"

Player::Player(std::string newName)
{
	_name = newName;
	_token = Game::X;
}

Player::~Player()
{

}

std::string Player::getName()
{

	return _name + "("+ Game::tokenToIcon(_token) +")";
}


void Player::setToken(Game::TOKEN m)
{
	_token = m;
}

Game::TOKEN Player::getToken()
{
	return _token;
}

Game::TOKEN Player::getOppToken()
{
	if (_token == Game::X)
	{
		return Game::O;
	} else if (_token == Game::O) {
		return Game::X;
	}

	ERROR("Don't have a valid token to get opp of");
	return Game::O;
}

void Player::prepare(bool meFirst)
{
	// Something to use meFirst so no more warning
	meFirst = false;
}

void Player::win()
{

}

void Player::lose()
{

}

void Player::draw()
{
	
}
