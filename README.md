# Experiments
Toys, Experiments, Giggles

***

#### [Anagram Solver](https://github.com/Samuel-Lewis/Experiments/tree/master/AnagramSolver)
*Toy* - 4th Dec 2015  
Wanted to get more practice in on Binary Search Trees, so I made an anagram solver. It stores all real words in BST, and it just checks if the permutations of your query exist.  
**To use:** Download the repo. Use `make` in Experiments/AnagramSolver, and then `./main.out` to run. It will prompt you for a word, and spit out the result. Alternatively, go `./main.out` and then specify as arguments any number of words you want to check.  

***

#### [CellAuto MapGen](https://github.com/Samuel-Lewis/Experiments/tree/master/CellAuto%20MapGen)
*Experiment* - 5th Dec 2015  
Simple pattern generation that is sometimes used for game map generators, particulary forests or caves. It is based off [Celluar Automata](https://en.wikipedia.org/wiki/Cellular_automaton), and in particular I used a variant of [Game of Life's](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) rule set.  
**To use:** Download the repo, and compile with `make`. You're set! Just run the program to see its results.

***

#### [lolz](https://github.com/Samuel-Lewis/Experiments/tree/master/lolz)
*Giggle* - 1st Jul 2015   
`HIA BEGIN_THAT VISIBLE "Hello World" TLDR EH KTHXBYE END_THAT` . Legitmate C++ "Hello World" program. A selection of silly macros to spice up your project.  
**To use:** Include `lolz.h` in your code, and you're set.  
**Dependencies:** A bad sense of humour  

***

#### [TicTacToe ML](https://github.com/Samuel-Lewis/Experiments/tree/master/TicTacToe%20ML)
*Experiment* - 18th Nov 2015  
First attempt at something machine learning based. A game of Tic Tac Toe, human vs AI, where the more you play, the more the AI learns *how* you play. After every game, the AI rewards its decisions based on what the final results were, which then influence future decisions.  
**To use:** Download the repo, and the [lunchbox toolset](https://github.com/Samuel-Lewis/lunchbox). Put `lunchbox` in the libs directory of `TicTacToe ML`. Then compile using `make` in root. Run and play!  
**Dependencies:** [lunchbox](https://github.com/Samuel-Lewis/lunchbox)  

***

Samuel Lewis 2015
