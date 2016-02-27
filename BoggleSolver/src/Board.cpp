
#include <vector>
#include <set>
#include <string>
#include <iostream>

#include <thread>
#include <mutex>

#include "lunchbox/lunchbox.h"

#include "Board.h"
#include "Dictionary.h"


Board::Board(std::string filePath)
{
	INFO("Creating new board");

	// Ini dictionary
	Dict::loadWords("data/words.txt");
	_charLimit = Dict::longestWord();

	INFO("Char limit set to " << _charLimit);

	// Get board size from config
	_boardSize = lbConfig::file("data/config.txt").get<int>("board_size");

	loadDice(filePath);
	shuffle();
}

Board::~Board()
{}


// Generate the board, and shuffle it
void Board::shuffle()
{
	LOG("Generating the board");
	// Use a pool of dice to draw from
	std::vector<std::vector <std::string> > remDice = _dice;

	_board.resize(_boardSize);

	LOG("Shuffle the dice onto the board");
	for (int i = 0; i < _boardSize; i++)
	{
		_board[i].resize(_boardSize);
		for (int j = 0; j < _boardSize; j++)
		{

			// Make sure we don't run out of dice
			if (remDice.empty())
			{
				WARN("Ran out of dice. Reusing old ones.");
				remDice = _dice;
			}

			int die = lbRNG::linear(0,(int)remDice.size());
			int side = lbRNG::linear(0,(int)remDice[die].size());

			TRACE("die: " << die << ". side: " << side);
			TRACE("size: " << remDice[die].size());
			TRACE("val: " << remDice[die][side]);

			_board[i][j] = new Die(remDice[die][side]);

			remDice.erase(remDice.begin() + die);
		}
	}
}

// Load dice values from text file
void Board::loadDice(std::string filePath)
{
	LOG("Loading dice from file");
	// Load file
	std::vector<std::string> fileLines = lbFile::getFileContents(filePath);

	for (int i = 0; i < (int)fileLines.size(); i++)
	{
		lbString::trim(fileLines[i]);
		std::vector<std::string> diceLine = lbString::split(fileLines[i], " ");
		_dice.push_back(diceLine);
	}

	_connectDice();

	INFO("Loaded " << _dice.size() << " dice.");
}

// Cosmetic visualization of the board
std::string Board::getAsString()
{
	LOG("Getting board as string");
	std::string returnStr = "";

	for (int i = 0; i < (int)_board.size(); i++)
	{
		for (int j = 0; j < (int)_board[i].size(); j++)
		{
			returnStr += _board[i][j]->value + " ";
		}

		returnStr += "\n";
	}

	return returnStr;
}

std::vector<std::string> Board::getSolutions()
{
	std::cout << "Please wait a moment..." << std::endl;
	LOG("Getting solutions");
	_sols.clear();

	// DANGER ZONE :D
	std::vector<std::thread> threads;

	// Search for a word, starting with each letter on the board
	for (int i = 0; i < (int)_board.size(); i++)
	{
		for (int j = 0; j < (int)_board[i].size(); j++)
		{
			std::map<Die*, bool> used;
			threads.push_back(std::thread(&Board::_extendWord, this, "", _board[i][j], used));
		}
	}

	// Close the threads
	for (int i = 0; i < (int)threads.size(); i++)
	{
		threads[i].join();
	}

	LOG("Converting from set to vector");
	// Convert to vector for return
	std::vector<std::string> v(_sols.begin(), _sols.end());

	INFO(v.size() << " solutions found!");

	return v;
}

void Board::_extendWord(std::string str, Die* curr, std::map<Die*, bool> used)
{

	if (curr == nullptr || curr == NULL)
	{
		FATAL("Somehow a nullptr passed through");
		return;
	}

	str += curr->value;

	used[curr] = true;

	std::mutex mut;
	if (Dict::isValid(str))
	{
		INFO("Valid word found! '" << str <<"'");
		mut.lock();
		_sols.insert(str);
		mut.unlock();
	}

	// No point in searching for words that are longer than the longest possible.
	if ((int)str.size() > _charLimit)
	{
		return;
	}

	// If a dice hasn't been used, and it actually exists, try it.
	if (curr->n != nullptr && !used.count(curr->n)) _extendWord(str, curr->n, used);
	if (curr->w != nullptr && !used.count(curr->w)) _extendWord(str, curr->w, used);
	if (curr->s != nullptr && !used.count(curr->s)) _extendWord(str, curr->s, used);
	if (curr->e != nullptr && !used.count(curr->e)) _extendWord(str, curr->e, used);

	if (curr->nw != nullptr && !used.count(curr->nw)) _extendWord(str, curr->nw, used);
	if (curr->ne != nullptr && !used.count(curr->ne)) _extendWord(str, curr->ne, used);
	if (curr->sw != nullptr && !used.count(curr->sw)) _extendWord(str, curr->sw, used);
	if (curr->se != nullptr && !used.count(curr->se)) _extendWord(str, curr->se, used);
}



void Board::enterValues()
{
	_board.clear();

	std::cout << "Please enter the dice, seperated by a space.\nPress ENTER to add a new row. Press ENTER twice to finish.\n" << std::endl;

	int width = -1;

	std::string str;
	while(getline(std::cin, str))
	{
		// New line, therefore finished entering
		if (str == "")
		{
			break;
		}

		// Split the row into letters
		std::vector<std::string> diceLine = lbString::split(str," ");
		int lineSize = (int)diceLine.size();

		// Set the board width (if not already set)
		if (width <= 0)
		{
			width = (int)lineSize;
		}

		if (lineSize == 0 || lineSize != width)
		{
			break;
		}

		// Convert all the letters into Dice
		std::vector<Die*> newRow;
		for (int i = 0; i < lineSize; i++)
		{
			if (diceLine[i].size() == 0)
			{
				continue;
			}

			lbString::toUpper(diceLine[i]);

			TRACE("Adding user input " << diceLine[i]);
			newRow.push_back(new Die(diceLine[i]));
		}

		_board.push_back(newRow);
	}

	_connectDice();

	std::cout << "Board entered." << std::endl;

}

// Link the dice to each their neighbours, so there is now a graph
void Board::_connectDice()
{
	for (int i = 0; i < (int)_board.size(); i++)
	{
		for (int j = 0; j < (int)_board[i].size(); j++)
		{
			if (i > 0)
			{
				_board[i][j]->n = _board[i-1][j];
				if (j > 0) _board[i][j]->nw = _board[i-1][j-1];
				if (j < (int)_board.size()-1) _board[i][j]->ne = _board[i-1][j+1];
			}

			if (i < (int)_board.size()-1)
			{
				_board[i][j]->s = _board[i+1][j];
				if (j > 0) _board[i][j]->sw = _board[i+1][j-1];
				if (j < (int)_board.size()-1) _board[i][j]->se = _board[i+1][j+1];
			}

			if (j < (int)_board[i].size()-1) _board[i][j]->e = _board[i][j+1];
			if (j > 0) _board[i][j]->w = _board[i][j-1];
		}
	}

	LOG("Connected dice");
}
