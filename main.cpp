//*********************
// Guess-theWord
// main.cpp
//*********************
// A simple letter/word guessing game for a programming tutorial
//
// (c) 2017 Garry Kling

#include "GuessingGameTextView.cpp"
#include <cstring>
#include <cctype>
#include <algorithm>

int main(int argc, char *argv[])
{
	GuessingGameTextView theView;
	std::string input;
	bool guessResult;

    // Some error checks
    std::string secretWord(argv[1]);

	//if(std::any_of(secretWord.begin(), secretWord.end(), &::isupper)) 
    if(isupper(secretWord.at(0)))
    {
        std::cout<<"No capital letters allowed in the secret word. Exiting."<<std::endl;
        return 0;
    }

	if(strlen(argv[1])>26)
	{
		std::cout<<"Error: Secret word is limited to 26 characters in width. Exiting."<<std::endl;
		return 0;
	}

	// These two lines have control chars that may not work on Windows or in IDE debuggers
	cout << "\e[8;16;100t";
	cout<<"\033[2J\033[1;1H";
	GuessingGame theGame(secretWord);
	
	while(!theGame.isSolved() && theGame.guessesLeft())
	{
		theView.displayGameStatus(theGame);

		std::cout<<"Please guess a letter or the word: ";
		std::cin>>input;

		if(input.size()<1)
		{
			std::cout<<"You wasted a guess by entering no letters! Do better."<<std::endl;
			theGame.nMistakes += 1;
			continue;
		}

		if(input.size()==1)
		{
			guessResult = theGame.guessLetter(input.substr(0, 1));
		} else if (input.size()>1)
		{
			guessResult = theGame.guessWord(input);
		}
		std::cout<<std::endl;
	}

	// display the view a final time
	theView.displayGameStatus(theGame);

	if(theGame.isSolved())
	{
		// ask the view to print the victory
		std::cout<<"Congratulations, you won in "<< theGame.nGuesses<<" guesses with only "<<theGame.nMistakes<<" mistakes!"<<std::endl;
	} else {
		// print the failure
		std::cout<<"Too many mistakes. Better luck next time!"<<std::endl;
	}

	return 0;
}