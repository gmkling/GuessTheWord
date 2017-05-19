//*********************
// GuessingGame.cpp
//*********************
// A simple letter/word guessing game for a programming tutorial
//
// (c) 2017 Garry Kling

#include "GuessingGame.hpp"
#include <string>

bool GuessingGame::guessLetter(char letterGuess)
{

}

bool GuessingGame::guessWord(std::string wordGuess)
{
	nGuesses++;

	if( wordGuess == secretWord)
	{
		wordInProgress = secretWord;
		return true;
	}

	return false;
}

bool GuessingGame::isSolved()
{
	return wordInProgress==secretWord;
}
