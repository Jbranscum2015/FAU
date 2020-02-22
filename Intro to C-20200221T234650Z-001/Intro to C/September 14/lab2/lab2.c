/*Jared Branscum COP 2220
September 26, 2016
Lab 2*/

//preprocessor  directive
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>

//function prototypes

//gets an integer from the user and returns it
int GetInt(void);

//gets a double from the user and returns it
double GetDouble(void);

//gets a letter from the user and returns it
char GetInitial(void);

/*takes two arguments, an integer  and a double
adds 10 to the integer and returns the result
multiplies the double argument by .5 and prints the result onto the screen*/
int FunctionOne(int arg1, double arg2);

/*takes one character argument and returns an integer
change the letter to uppercase (use ctype.h)
return a 1 if the letter is in the first half of the alphabet(A-M)
return a 2 if the letter is in the second half of the alphabet (N-Z)*/
int FunctionTwo(char arg1);

int main() {
	int number;
	double fraction;
	char letter;

	//function calls, retrieves values from the user
	number = GetInt();
	fraction = GetDouble();
	letter = GetInitial();

	// More function calls, but with printf statements! Additionally, the values are being computed through the equations and returning the new corresponding values.
	number = FunctionOne(number, fraction);
	printf("\nThe integer you inserted + 10 equals %d", number);
	letter = FunctionTwo(letter);
	printf("\n\nBased on the letter that was entered, \nthis program shall return %d \n\n", letter);

}

//function definitions

//gets an integer from the user and returns it
int GetInt(void) {
	int num;
	printf("Please insert an integer ");
	scanf("%d", &num);
	return num;
}

//gets a double from the user and returns it
double GetDouble(void) {
	double dub;
	printf("\nPlease insert a double ");
	scanf("%lf", &dub);
	return dub;
}

//gets a letter from the user and returns it
char GetInitial(void) {
	char letter;
	printf("\nPlease insert a letter ");
	scanf(" %c", &letter);
	return letter;
}

/*takes two arguments, an integer  and a double
adds 10 to the integer and returns the result
multiplies the double argument by .5 and prints the result onto the screen*/
int FunctionOne(int arg1, double arg2) {
	int num;
	num = arg1 + 10;
	
	double dubl;
	dubl = arg2 * 0.5;
	printf("\nThe double you inserted times 0.5 is %.2f\n", dubl);

	return num;
}

/*takes one character argument and returns an integer
change the letter to uppercase (use ctype.h)
return a 1 if the letter is in the first half of the alphabet(A-M)
return a 2 if the letter is in the second half of the alphabet (N-Z)*/
int FunctionTwo(char arg1) {
	char let;
	let = toupper(arg1);
	
	if (let <= 'M') {
		return 1;
	}
	else if (let >= 'N')
	{
		return 2;
	}
	else {
		return 0;
	}
	
}







