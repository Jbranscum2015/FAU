/* Jared Branscum COP 2220
October 5, 2016
Program 1 - Letter Guessing Game*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#define MAXGUESSES 5



//paste all the function prototypes here
//with the comments

//this function provides instructions to the user on how to play the game
void LetterGuessRules();

//this function runs one game.
//input: character from the file, void return type
//all other functions to Play one round of a game
//are called from within the GuessTheLetter function
void GuessTheLetter(char);

//this function prompts the player to make a guess and returns that guess
//this function is called from inside the GuessTheLetter( ) function described above
char GetTheGuess();

//this function takes two arguments, the guess from the player
//and the solution letter from the file.
//The function returns 1 if the guess matches the solution and returns a 0 if they do not match
//This function also lets the user know if the guess comes alphabetically before or after the answer
int CompareLetters(char, char);


int main()
{
	//declare additional variables
	//declare FILE pointer
	FILE *inPtr;
	int numGames, i = 0;

	char letter;//letter from file

				//display game rules
	LetterGuessRules();

	//Ask and get number of games to play
	printf("\n\nHow many games would you like to play? ");
	scanf("%d", &numGames);

	//connect to the file HINT: use fopen
	inPtr = fopen("LetterList.txt", "r");

	//this for loop will allow the player to play more than one game
	//without recompiling
	for (i = 0; i < numGames; i++)
	{
		//get a solution letter from file - use fscanf
		fscanf(inPtr, " %c", &letter);
		//change the solution to lowercase
		letter = tolower(letter);

		//call the GuessTheLetter function and pass it the solution
		GuessTheLetter(letter);


	}

	//close file pointer
	fclose(inPtr);
	return 0;
}

//this function runs one game. 
//input: character from the file, void return type
//all other functions to Play one round of a game 
//are called from within the GuessTheLetter function
//this function lets the user know if they have won or lost the game
void GuessTheLetter(char solution)
{
	int win = 0;
	int numGuesses = 0;
	//declare additional variables
	char guess;

	while (numGuesses < MAXGUESSES && win == 0)
	{
		//get a guess from the user  by calling the GetTheGuess function
		guess = GetTheGuess();
		//change the guess to lowercase
		guess = tolower(guess);
		win = CompareLetters(guess, solution); //call the function to compare the guess with the solution
		numGuesses++;//count the number of guesses so far
	}
	//use conditions to let the user know if they won or lost the round of the game
	if (win == 1)
	{
		printf("\n\nCongratulations! You won this round!\n");
	}
	if (win == 0 && numGuesses == MAXGUESSES)
	{
		printf("\n\nYou have unfortunately lost this round.\n");
	}

}

//this function provides instructions to the user on how to play the game
void LetterGuessRules()
{
	printf("Welcome to the Letter Guessing Game!\nFirst, you will enter the number of games you want to play (1 - 10 games)\nFor each game you will have 5 chances to guess each letter.");
}

//this function prompts the player to make a guess and returns that guess
//this function is called from inside the GuessTheLetter( ) function described above
char GetTheGuess()
{
	char guess;
	printf("\n\nPlease make a guess ");
	scanf(" %c", &guess);
	return guess;
}

//this function takes two arguments, the guess from the player
//and the solution letter from the file.
//The function returns 1 if the guess matches the solution and returns a 0 if they do not match
//This function also lets the user know if the guess comes alphabetically before or after the answer
int CompareLetters(char guess, char solution)
{
	if (guess == solution)
	{
		return 1;
	}
	else if (guess > solution)
	{
		printf("\n\nYour guess is above the solution.");
		return 0;
	}
	else if (guess < solution)
	{
		printf("\n\nYour guess is below the solution.");
		return 0;
	}
	else
	{
		return 0;
	}
}

