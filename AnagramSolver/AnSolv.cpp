
//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiment
//
//	@Project:	Anagram Solver
//
//	@Last Updated:	2015-12-04 22:47:39
//	@Created:		2015-12-04 22:47:21
//
//===============================================//

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <algorithm>	// sort, next_permutation
#include <cmath>		// ceil
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

#include "AnSolv.h"

AnSolv::AnSolv() : listHead(NULL) {}

// Clean up
AnSolv::~AnSolv()
{
	free(listHead);
}

void AnSolv::free(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	
	free(root->left);
	free(root->right);

	delete root;
}

// Load dictioary from external file
void AnSolv::loadWords(std::string fileName)
{
	std::ifstream file;
	file.open(fileName);

	std::string line = "";

	std::vector<std::string> words;

	if (file.good())
	{
		while(getline(file,line))
		{
			// Remove silly new line char
			line = line.substr(0, line.length()-1);
			words.push_back(line);
		}

		// Randomly shuffle the array so BST is hopefully more even
		// Pulled straight from docs :D
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle(words.begin(), words.end(), std::default_random_engine(seed));

		listHead = new Node(words[0]);

		// Add words to BST
		for (unsigned i = 1; i < words.size(); i++)
		{
			addEntry(words[i], listHead);
		}

	} else {
		std::cout << "ERROR: '" << fileName << "'' not found!" << std::endl;
		exit(1);
	}

}

// Use all combinations of query, and check if they are in the BST
std::vector<std::string> AnSolv::search(std::string query)
{
	// standardize to lower case
	for (int i = 0; i < (int)query.size(); i++)
	{
		query[i]=tolower(query[i]);
	}

	// Sort so we can use next_permutation from the start
	sort(query.begin(), query.end());

	std::vector<std::string> found;

	// Check BST
	do
	{
		if (exists(query, listHead))
		{
			found.push_back(query);
		}
	} while (next_permutation(query.begin(), query.end()));
	
	return found;
}

// Search BST
bool AnSolv::exists(std::string query, Node* root)
{
	// Shouldn't happen. But checks in case.
	if (root == NULL)
	{
		std::cout << "NULL" << std::endl;
		return false;
	}

	// Bingo! Found the word
	if (query == root->data)
	{
		return true;
	}

	// Word is less than
	if (query < root->data)
	{
		if (root->left == NULL)
		{
			// Not found
			return false;
		} else {
			// Continue search
			return exists(query, root->left);
		}

	// Greater than
	} else {
		if (root->right == NULL)
		{
			// Not found
			return false;
		} else {
			// Continue search
			return exists(query, root->right);
		}
	}
}

void AnSolv::addEntry(std::string entry, Node* root)
{
	// Should only be NULL on ini
	if (root == NULL)
	{
		root = new Node(entry);
		return;
	}

	// Word is less than
	if (entry < root->data)
	{
		if (root->left == NULL)
		{
			// New branch
			root->left = new Node(entry);
			return;
		} else {
			// Follow existing branch
			addEntry(entry, root->left);
		}

	// Words is greater than
	} else {
		if (root->right == NULL)
		{
			// New branch
			root->right = new Node(entry);
			return;
		} else {
			// Follow existing branch
			addEntry(entry, root->right);
		}
	}
}
