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
	int nGuessDigs = 1;
	int nMistakeDigs = 1;
	int nCorrect = 0;
	int nIncorrect = 0;
	int wordWidth;

	string dispBar = "|=============================|";
	string titleLine = "|Guess-the-Word               |";
	string guessText = "|Guesses: ";
	string mistakeText = "Mistakes: ";
	string scoreTrailingText = "   |";
	string emptyRowBox = "|                             |";
	string guessRow = "|                             |";
	string correctRow = "| Correct Letters:            |";
	string incorrectRow = "| Incorrect Letters:          |";

	void displayGameStatus(GuessingGame input)
	{
		// get word width, construct guess row
		// get guess/mistake widths, do score row
		// put previously guessed letters in the app. boxes

		cout<<dispBar<<std::endl;
		cout<<titleLine<<std::endl;
		cout<<dispBar<<std::endl;
		// need to resize gaps if numbers increase digit width
		cout<<guessText<<input.nGuesses<<mistakeText<<input.nMistakes<<scoreTrailingText<<std::endl;
		cout<<dispBar<<std::endl;
		cout<<emptyRowBox<<std::endl;
		// insert guessed string into guess row
		cout<<guessRow<<std::endl;
		cout<<emptyRowBox<<std::endl;
		cout<<dispBar<<std::endl;


		cout<<correctRow<<std::endl;
		cout<<emptyRowBox<<std::endl;
		cout<<emptyRowBox<<std::endl;
		cout<<emptyRowBox<<std::endl;

		cout<<incorrectRow<<std::endl;
		cout<<emptyRowBox<<std::endl;
		cout<<emptyRowBox<<std::endl;
		cout<<emptyRowBox<<std::endl;
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
|       ------                |
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