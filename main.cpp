//*********************
// Guess-theWord
// main.cpp
//*********************
// A simple letter/word guessing game for a programming tutorial
//
// (c) 2017 Garry Kling

#include "GuessingGameTextView.cpp"

int main(int argc, char *argv[])
{
	GuessingGameTextView theView;
	GuessingGame theGame("Test");
	
	theView.displayGameStatus(theGame);
	return 0;
}