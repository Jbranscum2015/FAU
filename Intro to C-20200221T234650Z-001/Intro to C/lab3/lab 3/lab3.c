/*Jared Branscum COP 2220
October 19, 2016
Lab 3*/

//preprocessor directives

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>

//takes two integer arguments and two integer pointer arguments
//1. calculate the product and stores the result in prodPtr
//2. calculate sum and store the result in sumPtr
void CalculateBoth(int num1, int num2, int*prodPtr, int*sumPtr);

int main()
{
	//variables
	int num;
	int x = 0, z = 0;
	int y, a, b, prod, sum;

	//prompts the user for a number and gets it
	printf("Hello, please enter a number from 1-9: ");
	scanf("%d", &num);
	printf("\n");

	//while loop
	while (x < num)
	{
		printf("FAU Owls-Hoot Hoot\n");
		x++;
	}

	//for loop
	for (y=0;y<num;y++)
	{
		printf("Programming is fun\n");
	}

	//do/while loop
	do
	{
		printf("Florida beaches are beautiful\n");
		z++;
	} while (z < num);

	printf("\n\nPlease enter two numbers (put a space to separate the numbers):");
	scanf("%d %d", &a, &b);

	CalculateBoth(a, b, &prod, &sum);

	printf("\nFrom the main function, the product is %d", prod);
	printf("\n\nFrom the main function, the sum is %d\n\n", sum);

}

void CalculateBoth(int num1, int num2, int*prodPtr, int*sumPtr)
{
	*prodPtr = num1 * num2;
	*sumPtr = num1 + num2;
	printf("\nThe product is %d", *prodPtr);
	printf("\n\nThe sum is %d\n\n", *sumPtr);
}
