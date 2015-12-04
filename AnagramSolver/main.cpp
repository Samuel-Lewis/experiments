
//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiment
//
//	@Project:	Anagram Solver
//
//	@Last Updated:	2015-12-04 22:47:48
//	@Created:		2015-12-04 22:47:21
//
//===============================================//

#include <iostream>
#include "AnSolv.h"

void showResults(std::string in, std::vector<std::string> results)
{
	// Show input
	std::cout << "\nINPUT: " << in << std::endl;

	if (results.empty())
	{
		std::cout << "\t[No results found]" << std::endl;
	}

	// List of results
	for (int i = 0; i < (int)results.size(); i++)
	{
		std::cout << "\t" << results[i] << std::endl;
	}
}

int main(int numArgs, char* args[])
{
	AnSolv as;
	as.loadWords("words.txt");

	// No args given, hence ask for word
	if (numArgs <= 1)
	{
		std::string q = "";
		std::cout << "Query: ";
		getline(std::cin, q);

		showResults(q, as.search(q));

	// Use given args
	} else {
		for (int i = 1; i < numArgs; i++)
		{
			showResults(args[i], as.search(args[i]));
		}
	}
	return 0;
}
