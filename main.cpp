//*********************
// Guess-theWord
// main.cpp
//*********************
// A simple letter/word guessing game for a programming tutorial
//
// (c) 2017 Garry Kling

#include "GuessingGameTextView.cpp"
#include <cstring>

int main(int argc, char *argv[])
{
	GuessingGameTextView theView;
	std::string input;
	bool guessResult;

	// check the word input, clearhome, start game
	if(strlen(argv[1])>26)
	{
		std::cout<<"Error: Secret word is limited to 26 characters in width. Exiting."<<std::endl;
		return 0;
	}
	cout << "\e[8;16;100t";
	std::cout<<"\033[2J\033[1;1H";
	GuessingGame theGame(argv[1]);
	
	// the control loop loops until the puzzle is solved or we run out of guesses
	while(!theGame.isSolved() && theGame.guessesLeft())
	{
		// display the view
		theView.displayGameStatus(theGame);

		// ask for a guess (letter or word)
		std::cout<<"Please guess a letter or the word: ";
		std::cin>>input;

		// error check input
		if(input.size()<1)
		{
			std::cout<<"You wasted a guess by entering no letters! Do better."<<std::endl;
			theGame.nMistakes += 1;
			continue;
		}

		// is the guess a letter or word?
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