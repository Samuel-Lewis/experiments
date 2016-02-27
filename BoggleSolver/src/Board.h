
#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include <set>

class Board
{
public:
	Board(std::string);
	~Board();

	void shuffle();
	void loadDice(std::string);

	void enterValues();

	std::string getAsString();

	std::vector<std::string> getSolutions();

private:

	int _boardSize;

	struct Die
	{
		std::string value;

		Die* n;
		Die* s;
		Die* e;
		Die* w;

		Die* nw;
		Die* ne;
		Die* sw;
		Die* se;

		Die(std::string str) : value(str)
		{
			n = nullptr;
			s = nullptr;
			e = nullptr;
			w = nullptr;

			nw = nullptr;
			ne = nullptr;
			sw = nullptr;
			se = nullptr;
		}
	};

	std::vector<std::vector <Die*> > _board;
	std::vector<std::vector <std::string> > _dice;

	int _charLimit;

	void _connectDice();

	void _extendWord(std::string, Die*, std::map<Die*, bool>);
	std::set<std::string> _sols;
	// std::map<Die*, bool> _used;

};

#endif // BOARD_H
