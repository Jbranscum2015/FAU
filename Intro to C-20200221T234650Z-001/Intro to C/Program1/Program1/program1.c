/*Jared Branscum COP 2220
October 3, 2016
Program 1*/

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
	//the file pointer
	FILE *inPtr;
	
	int numGames, i = 0;
	
	//letter from file
	char letter;

	//display game rules
	printf("Welcome fellow player! You have chosen to play the Letter Guessing Game! \nDo you think you can win?");
	printf("\n\nAll you have to do is follow the instructions given below \nand hope you guessed the right letter!");
	printf("\n\nThe most important rule of all is to have fun!");

	//Ask and get number of games to play
	printf("\n\n\nHow many games would you like to play? Please play 10 games or less: ");
	scanf("%d", &numGames);

	//connect to the file
	inPtr = fopen("letterList.txt", "r");
	
	//this for loop will allow the player to play more than one game
	//without recompiling
	for (i = 0; i < numGames; i++)
	{
		//get a solution letter from file - use fscanf
		fscanf(inPtr, " %c", &letter);
		//change the solution to lowercase
		letter = tolower(letter);
		//print the solution back onto the screen to test
		printf("\nThe letter is %c \n\n", letter);
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
	char guess;
	//declare additional variables 

	while (numGuesses < MAXGUESSES && win == 0)
	{
		//get a guess from the user  by calling the GetTheGuess function
		guess = GetTheGuess();
		
		//change the guess to lowercase
		guess = tolower(guess);
		//call the function to compare the guess with the solution
		numGuesses++;//count the number of guesses so far
		win = CompareLetters(guess, solution);
		
	}
	//use conditions to let the user know if they won or lost the round of the game
	if (win == 1)
	{
		printf("Congratulations! You have won the game!\n\n");
	}
	else if (win == 0 && numGuesses == MAXGUESSES)
	{
		printf("You have unfortunately lost this game.");
	}
	else
	{

	}

}

char GetTheGuess()
{
	char letter;
	printf("Please make a guess ");
	scanf(" %c", &letter);
	return letter;
}

//this function takes two arguments, the guess from the player
//and the solution letter from the file.
//The function returns 1 if the guess matches the solution and returns a 0 if they do not match
//This function also lets the user know if the guess comes alphabetically before or after the answer
int CompareLetters(char guess, char solution) {
	if (guess == solution) {
		return 1;
	}
	else if (guess > solution) {
		printf("\nYour guess is above the solution.");
		return 0;
	}
	else if (guess < solution){
		printf("\nYour guess is below the solution");
		return 0;
	}
	else {
		return 0;
	}
}