/*Jared Branscum
September 14, 2016
COP 2220
September 14*/

//preprocessor  directive
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<ctype.h> //toupper, tolower

//function prototypes

//ask for and get an age
int GetAge();

//ask for and get an initial
char GetInitial();

//takes three arguments of type int
//and returns the sum
int CalculateSum(int, int, int);

//takes two arguments
//divides the first argument by the second argument and 
//returns the quotient as a double
double CalculateAvg(int, int);

int main()
{
	char initial1, initial2, initial3;
	int age1, age2, age3;
	int sum;
	double avg;
	char lower;
	//1. ask for an initial //2. get the initial
	initial1 = GetInitial();
	//3. change it to lowercase
	initial1 = tolower(initial1);
	//4. ask the age //5. get the age
	age1 = GetAge();
	printf("The age is %d and the initial is %c\n", age1, initial1);

	//6. ask for an initial //7. get the initial
	initial2 = GetInitial();
	//8. change it to uppercase
	initial2 = toupper(initial2);
	//9. ask the age	//10. get the age
	age2 = GetAge();
	printf("The age is %d and the initial is %c\n", age2, initial2);

	//11. ask for an initial	//12. get the initial
	initial3 = GetInitial();
	//13. change it to lowercase
	initial3 = tolower(initial3);
	//14. ask the age	//15. get the age
	age3 = GetAge();
	printf("The age is %d and the initial is %c\n", age3, initial3);

	//16. calculate the sum
	sum = CalculateSum(age1, age2, age3);
	//17. calculate the average
	avg = CalculateAvg(sum, 3);
	//18. print the results
	printf("\n\nThe sum is %d and the avg is %.2f\n", sum, avg);

	return 0;
}


//ask for and get an age
int GetAge()
{
	int age;
	printf("\nEnter your age: ");
	scanf("%d", &age);
	return age;
}

//ask for and get an initial
char GetInitial()
{
	char initial;
	printf("\nEnter your first initial: ");
	scanf(" %c", &initial);
	return initial;
}

//takes two arguments of type int
//and returns the sum
int CalculateSum(int arg1, int arg2, int arg3)
{
	int sum = arg1 + arg2 + arg3;
	return sum;
}

//takes two arguments
//divides the first argument by the second argument and 
//returns the quotient as a double
double CalculateAvg(int arg1, int arg2)
{
	double quo = (double)arg1 / (double)arg2;
	return quo;
}