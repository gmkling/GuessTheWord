//*********************
// GuessingGame.cpp
//*********************
// A simple letter/word guessing game for a programming tutorial
//
// (c) 2017 Garry Kling

#include "GuessingGame.hpp"
#include <string>

bool GuessingGame::guessLetter(std::string letterGuess)
{
	std::string::size_type resultIdx;
	int letterCount=0;

	nGuesses++;
	resultIdx = secretWord.find(letterGuess);

	// simple find & replace
	while( resultIdx != std::string::npos )
	{
		letterCount++;
		wordInProgress.replace(resultIdx, 1, letterGuess);
		resultIdx = secretWord.find(letterGuess, resultIdx+1);
	}

	// letter tracking
	if( letterCount>0)
	{	
		if(guessedCorrect.find(letterGuess) == std::string::npos )
		{
			guessedCorrect += letterGuess.substr(0,1);
		}
		return true;
	}

	if( guessedIncorrect.find(letterGuess) == std::string::npos )
	{
		guessedIncorrect += letterGuess.substr(0,1);
	}
	
	nMistakes++;
	return false;

}

bool GuessingGame::guessWord(std::string wordGuess)
{
	nGuesses++;

	if( wordGuess == secretWord)
	{
		wordInProgress = secretWord;
		return true;
	}

	nMistakes++;
	return false;
}

bool GuessingGame::isSolved()
{
	return wordInProgress==secretWord;
}

bool GuessingGame::guessesLeft()
{
	return nMistakes<maxMistakes;
}
