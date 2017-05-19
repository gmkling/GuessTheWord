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

	std::string secretWord;
	std::string wordInProgress;
	int wordWidth;

	char guessedCorrect[26];
	char guessedIncorrect[26];

    // interface
	bool guessLetter(char letterGuess);
	bool guessWord(std::string wordGuess);
	bool isSolved();

private:
};