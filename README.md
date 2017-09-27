# Experiments
Toys, Experiments, Giggles

***

#### [10print](https://github.com/Samuel-Lewis/Experiments/tree/master/10print)
*Experiment* - 27th Sept 2017  
Looking at early creative coding, and wanted to try a quick version of the 10print pattern. For more info on the pattern, see http://10print.org/.
**To use:** Download the repo. Run `./10print` and you're done. Just watch it I guess.

***

#### [Anagram Solver](https://github.com/Samuel-Lewis/Experiments/tree/master/AnagramSolver)
*Toy* - 4th Dec 2015  
Wanted to get more practice in on Binary Search Trees, so I made an anagram solver. It stores all real words in BST, and it just checks if the permutations of your query exist.  
**To use:** Download the repo. Use `make` in Experiments/AnagramSolver, and then `./main.out` to run. It will prompt you for a word, and spit out the result. Alternatively, go `./main.out` and then specify as arguments any number of words you want to check.  

***

#### [Ascii Font Clock](https://github.com/Samuel-Lewis/Experiments/tree/master/AsciiFontClock)
*Toy* - 2nd Feb 2017
A fancy clock for your terminal. Compile it and run to see your local time in unnecessarily large text.  
**To use:** Download the repo. Use `make` in Experiments/AsciiFontClock, and it will display the time. To specify which font you want to use, make sure the font is in the `fonts` directory, and use `./clock <font_name>`.![AsciiArtClock Demo](http://i.imgur.com/29hKv2z.png)

***

#### [Boggle Solver](https://github.com/Samuel-Lewis/Experiments/tree/master/BoggleSolver)
*Toy* - 27th Feb 2016   
Too much Boggle at home lead to needing to make a solver for it. Experimented with the search, and used threaded to help performance.  
**To use:** Download the repo, and download [lunchbox](https://github.com/Samuel-Lewis/lunchbox) into `BoggleSolver/src/` to include the toolset.  
**Dependencies:** [lunchbox](https://github.com/Samuel-Lewis/lunchbox)  

***

#### [CellAuto MapGen](https://github.com/Samuel-Lewis/Experiments/tree/master/CellAuto%20MapGen)
*Experiment* - 5th Dec 2015  
Simple pattern generation that is sometimes used for game map generators, particulary forests or caves. It is based off [Celluar Automata](https://en.wikipedia.org/wiki/Cellular_automaton), and in particular I used a variant of [Game of Life's](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) rule set.  
**To use:** Download the repo, and compile with `make`. You're set! Just run the program to see its results.
![CellAuto Demo](http://i.imgur.com/fmz4NfS.png)


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

#### [quine](https://github.com/Samuel-Lewis/Experiments/blob/master/quine.cpp)
*Giggle* - 27th Feb 2016  
A silly version of making a [quine](https://goo.gl/WRBA0B). I don't even know if it qualifies.  
**To use:** Compile and run it.  

***
