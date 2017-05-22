//*********************
// GuessingGame.hpp
//*********************
// A simple letter/word guessing game for a programming tutorial
//
// (c) 2017 Garry Kling

#include <string>

class GuessingGame
{
public:
	GuessingGame(std::string newSecret): 
		nGuesses(0), 
		nMistakes(0), 
		secretWord(newSecret), 
		wordInProgress(" "),
		wordWidth(0)
	{
		wordWidth = newSecret.size();
		std::string s(wordWidth, '-');
		wordInProgress = s;
	}

	int nGuesses;
	int nMistakes;
	const int maxMistakes=8; 

	std::string secretWord;
	std::string wordInProgress;
	int wordWidth;
	std::string guessedCorrect;
	std::string guessedIncorrect;

    // interface
	bool guessLetter(std::string letterGuess);
	bool guessWord(std::string wordGuess);
	bool isSolved();
	bool guessesLeft();

};