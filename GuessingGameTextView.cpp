//*********************
// GuessingGameTextView.hpp
//*********************
// A simple letter/word guessing game for a programming tutorial
//
// (c) 2017 Garry Kling

#include "GuessingGame.hpp"
#include <iostream>

using namespace std;

class GuessingGameTextView
{
public: 
	const int width = 32;

	string dispBar = "|==============================|";
	string titleLine = "|Guess-the-Word                |";
	string guessText = "|Guesses: ";
	string mistakeText = "Mistakes: ";
	string scoreTrailingText = "   |";
	string emptyRowBox = "|                              |";
	string guessRow = "|                              |";
	string correctRow = "| Correct Letters:             |";
	string incorrectRow = "| Incorrect Letters:           |";

	void displayGameStatus(GuessingGame input)
	{
		int padding;
		// get guess/mistake widths, do score row
		// put previously guessed letters in the app. boxes

		// header/title block
		cout<<dispBar<<std::endl;
		cout<<titleLine<<std::endl;
		cout<<dispBar<<std::endl;

		// score block
		padding = width - guessText.size() - mistakeText.size() - scoreTrailingText.size() - 2;
		if(input.nGuesses>9) padding--;
		if(input.nMistakes>9) padding--;
		std::string scoringPad(padding, ' ');
		cout<<guessText<<input.nGuesses<<scoringPad<<mistakeText<<input.nMistakes<<scoreTrailingText<<std::endl;
		cout<<dispBar<<std::endl;

		// guess progress block
		cout<<emptyRowBox<<std::endl;
		guessRow.replace(2, input.wordWidth, input.wordInProgress);
		cout<<guessRow<<std::endl;
		cout<<emptyRowBox<<std::endl;
		cout<<dispBar<<std::endl;

		// correct letters block
		cout<<correctRow<<std::endl;
		std::string correctRow(emptyRowBox);
		correctRow.replace(2, input.guessedCorrect.size(), input.guessedCorrect);
		cout<<correctRow<<std::endl;
		cout<<dispBar<<std::endl;

		// incorrect letters block
		cout<<incorrectRow<<std::endl;
		std::string incorrectRow(emptyRowBox);
		incorrectRow.replace(2, input.guessedIncorrect.size(), input.guessedIncorrect);
		cout<<incorrectRow<<std::endl;
		cout<<dispBar<<std::endl;

	};
};

/*

|=============================|
|Guess-the-Word               |
|=============================|
|Guesses: 0     Mistakes: 0   |
|=============================|
|                             |
| ------                      |
|                             |
|=============================|
| Correct Letters:            |
|                             |
|                             |
|                             |
|=============================|
| Incorrect Letters:          |
|                             |
|                             |
|                             |
|=============================|

*/