####Word Games
Word games are a fun way to build our vocabulary or flex our spelling skills. Many word games are based on guessing the letters of a secret word or phrase, like *Wheel of Fortune* or *Hangman*. These games are popular group activities in classrooms that teach students new words and how to spell them. But how can we make a simple computer version of the "Guess-the-Word" game?

####Game Overview
Let's discuss in detail how the game works. A secret word is selected by the "host" of the game, often a teacher drawing on a whiteboard. The word may not be a proper noun (name, place names, companies, etc.), and the host draws a line for each letter in the secret word.

![Figure 1: The game begins](/content/images/2017/05/GuessTheWord_Fig1.png)
> Figure 1: The game begins

Students take turns guessing letters, and if any letter matches, the teacher fills in the blank space. Incorrect letters are placed below in the "graveyard" of failed guesses. Students can also make guesses at what the word is, but wrong answers count as mistakes. Mistakes are tallied, and sometimes the total number of guesses are too. 

![Figure 2: The game in progress](/content/images/2017/05/GuessTheWord_Fig2.png)
>Figure 2: The game in progress

The game is won when the students either finish the word or guess the word. The game is lost when too many mistakes are made.

![Figure 3: The game is won](/content/images/2017/05/GuessTheWord_Fig3.png)

> Figure 3: The game is won

It's a good idea to play a few games by hand to get a handle on the details. Talk out the game with a friend, and take turns guessing and hosting the game.

####Coding the Game
Now that we a have a handle on the game, we can get to work on the code (we'll use C++ to create a simple command-line game). It is not a complex game, but we will get some practice with handling strings, and with a little care we can dabble in some intermediate programming concepts. Its always a good idea to read and play with a working version of the code, you can see/clone it on my [github](https://github.com/gmkling/GuessTheWord.git). 

We're going to divide the code up into three areas. Each will cover it's own section of the game, and will have its own set of files. Like many C++ programs, we will have a main.cpp which will contain the driving code and user interaction details. This will in turn work with a GuessingGame object, which will contain the data and logic for the game itself. Finally, the visual interface of the game will be handled in the GuessingGameTextView object, which will do most of the printing of the game state. We are going to keep it simple - and leave problematic drawings for later.

#####The Game Controller
The ```int main()``` function will act as a simple controller for our game. User interaction is handled here, and the controller coordinates between the game model and view. So remember when our game starts up, we need a secret word. We can get this when the game is started from the command line by calling the program along with the secret word as the first argument: 

```
user@computer: ./GuessTheWord locomotive
```
Remember our rule: no proper nouns. We want to enforce this rule simply, so we'll just make sure none of the letters are capitalized as a quick check for now. Advanced programmers may have some ideas about ways to improve this check. 

```
int main(int argc, char *argv[])
{
    std::string secretWord(argv[1]);
    if(isupper(secretWord.at(0))) 
    {
        std::cout<<"No capital letters allowed in the secret word. Exiting."<<std::endl;
        return 0;
    }
...
```
We retrieve the secret word from the command line and pack it into a ```std::string```, and we use the helper function ```isupper()``` to check the first letter of the word to see if it is uppercase. We tell the user and exit if we detect this error. What further error checking should we do on the ```secretWord``` string?

Now that we have a good word to use, we can create the ```GuessingGame``` object using that word, along with the ```GuessingGameView``` object. We also need a variable to store each of our guesses, and whether the guess is right or wrong. 

``` C++
...
    GuessingGame theGame(secretWord);
    GuessingGameTextView theView;
    std::string input;
    bool guessResult;
...
```
We will go over most of the details of these later, but we need to talk about how we can get guesses from the user for each turn. We need to take that guess, and ask ```theGame``` if it is right, update the letters on the display, and then ask for the next guess until it's time to stop. 

When we need to do something over and over, usually we're talking about a loop. In this case, we'll use a *while* loop. Think of it as a function that repeats while something is true. 
``` C++
while(testIsTrue)
{
    // do what is in here again
}
```
In our case, we keep accepting and testing guesses while the puzzle is unsolved and we have not yet made too many mistakes. This loop is a common feature in games, fittingly called the **game loop**. Player input is gather, game logic is triggered, and the game is displayed. The loop exits when the game is won or lost. 

Remember what we said about how the game is won and lost:
>The game is won when the students either finish the word or guess the word. The game is lost when too many mistakes are made.

We ask ```theGame``` for the answer to both these questions before we get a new guess from the player. If either is ```false```, then the game is over and we don't need any more guesses. We put these questions together with the ```&&``` operator. They both have to be true - the puzzle is NOT solved, AND there are guesses left.

``` C++
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
	} // end of while loop
...
```
Lets look at this code. At the beginning of each loop, we ask the view to display the current state so the player can see the status of the game. The dashes, the score, and what letters have already been found. We ask for the guess with the usual ```iostream``` operators, storing the guess in ```input``` and we check to be sure it is not empty (we complain and count it as mistake if it is). Then we have to handle a word guess differently than a letter guess. To keep this simple, we see how long the input is and count anything longer than one character as a word guess. The input is sent as a guess to the game, which updates its internal state, and returns a ```bool``` to indicate whether a guess is good or not. We do a line feed, and the loop repeats.

When the loop exits due to win or loss, we need to display the game one more time so the player can enjoy their victory, and then we print either a victory message or a loss message:

```C++
... (while loop exits)    
    // display the view a final time
	theView.displayGameStatus(theGame);

	if(theGame.isSolved())
	{
		// ask the view to print the victory
		std::cout<<"Congratulations, you won in "<< 
        theGame.nGuesses<<" guesses with only "<<theGame.nMistakes<<" mistakes!"<<std::endl;
	} else {
		// print the failure
		std::cout<<"Too many mistakes. Better luck next time!"<<std::endl;
	}

	return 0;
}
```
That is the gist of the user interaction and the coordination with the model and the view. Not very complicated. Now we are ready to talk about how the internals of the game and the view objects work.

#####Game Model Interface and Data
In order to play the game, we need to track some data. To keep the code easy to read, I've named everything after what role it plays in the game. This is all stored in the object we called ```theGame``` in main.cpp.
```
	int nGuesses;
	int nMistakes;
	const int maxMistakes=8; 

	std::string secretWord;
	std::string wordInProgress;
	int wordWidth;
	std::string guessedCorrect;
	std::string guessedIncorrect;
```
In the ```main()``` function, we create the ```GuessingGame``` object by passing the secret word to the constructor function, which tells the computer how to build the game object. We provide the starting values for all the variables other than the secret word in parentheses next to the variable name so the computer will know how to start the game. Don't worry if you don't understand this code yet.

```C++
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
```
Now we get to the guts of the game. During the main function, we call the following methods on the ```GuessingGame``` object during the game loop:

``` C++
    bool isSolved();
    bool guessesLeft();
    bool guessLetter(std::string letterGuess);
    bool guessWord(std::string wordGuess);
```
We'll look at each of these since they're short.

``` C++
bool GuessingGame::isSolved()
{
	return wordInProgress==secretWord;
}

bool GuessingGame::guessesLeft()
{
	return nMistakes<maxMistakes;
}
```
These are pretty self-explanatory, the puzzle is solved if the ```wordInProgress``` is exactly equal to the ```secretWord``` (luckily C++ makes that a one-liner), and we have guesses left if we've made less mistakes than the maximum. 

Guessing a word is also easy:
```C++
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
```
Each guess (word or letter) we take adds one to the ```nGuesses``` variable with the increment operator (```++```). If the guess is equal to the secret word, the ```wordInProgress``` is replaced with the ```secretWord```, and ```true``` is returned. If the guess is incorrect, we increment the ```nMistakes``` count and return ```false```.

The most interesting function for the game model is the ```guessLetter()``` function:

```C++
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
```
There are a couple of fun tricks in here with the ```std::string``` library. The ```find()``` function is a very useful thing, and in this case we use it to see if we've made a good guess. We call ```find()``` on the ```secretWord```, and it returns the index of any place where our guess is, which we store in ```resultIdx```. If there is no match, ```resultIdx``` is set to a special value called ```std::string::npos``` which is the size of the string, meaning ```find()``` went past the end without finding anything. 

We see our old friend the ```while()``` loop. This repeatedly looks for a letter in the secret word, in case there are more than one of them in the word, until ```npos``` is reached. Can you think of some examples of words that have multiple occurrences of the same letter? 

At each loop, we ```find()``` an index of a letter in the ```secretWord``` and use that to insert our guess into the ```wordInProgress``` with the ```replace()``` function.

Remember that we want to keep track of the letters we've tried before. We use ```find()``` and ```npos``` again to make sure we only add them to ```guessedCorrect``` and ```guessedIncorrect``` strings once via **concatenation**. Concatenation is just the adding together of things one right after the other, like adding railcars to a train. For ```std::string``` you can do this with the ```+``` or ```+=``` operators to make bigger strings from small ones. The ```guessedCorrect``` and ```guessedIncorrect``` strings are printed at the bottom of the game screen after every turn, but nothing stops players from guessing the same letters over and over other than adding to their mistakes. But if we keep adding the same letters over and over they will run off the screen! 

##### The Game View

The game view we are using is very simple. We are going to draw Figure 3 above in plain text. Here it is below.

```c++
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

```
> Fig. 4: Guessing Game Plain Text Schematic

All it needs to do is take data from the game model, mix it in with boxes above, and send it to ```std::cout```. We can do this with one method, and use local variables to make templates for these lines and shapes. We aren't going to draw any crazy ascii art to track the game just yet.

``` C++
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
	
        cout<<guessText<<input.nGuesses
            <<scoringPad<<mistakeText<<input.nMistakes
            <<scoreTrailingText<<std::endl;
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
```
A couple of notable thing here. First is that the ```GuessingGame``` object is passed directly to the display function. This is simple to do, but will cause problems that we can't quite explain yet. There are better ways to do this that advanced programmers will quickly discover. The second thing is that if you look at each section, it draws a block of the display by inserting data into the lines using the ```replace()``` method. For the block containing the "score" of mistakes and guesses, we have to calculate how much padding to add. If either ```nGuesses``` or ```nMistakes``` is greater than or equal to ten (which starts our two-digit numbers), we need to remove a space from the padding or it will ruin our layout. Take a close look at those lines to make sure you understand them.

#####Compile and Run
The above code is not complete, so please download the code from github:
https://github.com/gmkling/GuessTheWord
You can either download it with the green "Clone or Download" button, or download it by cloning from the command-line of your computer with the command:

``` 
git clone https://github.com/gmkling/GuessTheWord
```
The code online has a couple more features that are useful for display. It clears the scrollback of the terminal (so you don't see the secret word) and resizes compatible windows to a proper size.

To build, you can do the following command on one line:

```
gcc -std=c++11 -o GuessTheWord main.cpp GuessingGame.cpp GuessingGameTextView.cpp -lstdc++
```
You can play by typing ```./GuessTheWord {your secret word}```. It's better to have a friend pick your words.  

#####Ideas for Improvement
The game is very basic, but there are several ways that it can be improved. A future tutorial may cover some of these things, but interested programmers will be able to implement these themselves. Contemplate solutions that implement the following ideas, or come up with improvements of your own.

First, support for phrases or multi-word puzzles could be added. The main challenge is to adjust the view component to accommodate phrases that we can't predict. Some combination of limits and intelligent processing will create an elegant solution. This would be a step in the direction of a *Wheel of Fortune* game.

What happens if you enter a mix of letters, numbers, and punctuation? Can you find a way to prevent this?

Do you think listing the correctly guessed letters is a good idea or bad idea? Why?

One weakness of the game is that someone needs to enter a new word each time it is played, which is inconvenient and can result in misspelled words. If you pre-selected words and store them in a text file, you could load a random one each time you play. More advanced users may be able to find a way to do this with much work.

There is some code in the ```main()``` function that may be more appropriate in the ```GuessingGame``` object since it processes guesses. Can you think of a way to create one method to submit guesses instead of having separate methods for letter and word guesses?

In this tutorial, I've mentioned the Model-View-Controller pattern. This powerful paradigm helps make code reusable. For example, one could easily swap out the ```GuessingGameTextView``` with new code to change the way the game is displayed. What new way of displaying the game can you imagine coding? What would you need to learn about to do that?



