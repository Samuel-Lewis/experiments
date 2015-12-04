
//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiment
//
//	@Project:	Anagram Solver
//
//	@Last Updated:	2015-12-04 22:47:43
//	@Created:		2015-12-04 22:47:21
//
//===============================================//

#ifndef ANSOLV_H
#define ANSOLV_H

#include <string>
#include <vector>
#include <iostream>


#ifndef NULL
#define NULL 0
#endif

class AnSolv
{
public:
	AnSolv();
	~AnSolv();

	void loadWords(std::string);

	std::vector<std::string> search(std::string);

	struct Node {
		Node(std::string newWord) : left(NULL), right(NULL), data(newWord) {}
		Node* left;
		Node* right;

		std::string data;
	};

private:

	Node* listHead;

	void addEntry(std::string, Node*);
	bool exists(std::string, Node*);

	void free(Node*);

};


#endif // ANSOLV_H
