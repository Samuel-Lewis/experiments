
#include <iostream>

#include "lunchbox/lunchbox.h"

#include "Board.h"


int main()
{
	// Set logs
	lbLog::startLog("logs/","log",true);
	lbLog::setFileLogLevel(lbLog::all);

	Board solverBoard("data/dice.txt");
	std::cout << "Sample randomly generated board: " << std::endl;
	std::cout << solverBoard.getAsString() << std::endl;

	// Get user input
	solverBoard.enterValues();

	// Get solutions
	std::vector<std::string> sols = solverBoard.getSolutions();

	std::cout << "SOLUTIONS: " << std::endl;
	for (int i = 0; i < (int)sols.size(); i++)
	{
		std::cout << sols[i] << std::endl;
	}

	lbLog::endLog();

	return 0;
}
