/*Jared Branscum COP 2220
November 6, 2017
Lab 4*/

//preprocessor directives

#define _CRT_SECURE_NO_WARNINGS
#define size 20
#include <stdio.h>

//function prototypes

//Puts the retrieved numbers into an array and prints the array in a column
void FillArray(FILE *inPtr, int nums[], int *number);

//calculates the sum of the integers
int CalculateSum(int i, int nums[], int *number);

//prints the sum onto an output file
void SaveSum(int sum, FILE *outPtr);

int main() {

	//variables
	FILE *inPtr;
	FILE *outPtr;
	int nums[size];
	int sum = 0, number,i=0;

	//opens the input to file to read from it and the output file to write to it
	inPtr = fopen("numInput.txt", "r");
	outPtr = fopen("resOut.txt", "w");

	//prompts the user for the number of integers to retrieve from the input file
	printf("How many numbers do you want from the input file?(0-20) ");
	scanf("%d", &number);
	printf("\n----------------------------------------------------------------------\n\n");

	FillArray(inPtr, nums, &number);

	sum = CalculateSum(i, nums, &number);

	SaveSum(sum, outPtr);

	printf("\nThe sum of the integers you picked from the array is %d.", sum);
	printf("\n\nAn output file called resOut has been created, to show the sum as well:)\n\n");

	return 0;
}

//Puts the retrieved numbers into an array and prints the array in a column
void FillArray(FILE *inPtr, int nums[], int *number) {
	int count;
	for (count = 0; count < *number; count++)
	{
		fscanf(inPtr, "%d", &nums[count]);
	}
	for (count = 0; count < *number; count++) {
		printf("%d\n", nums[count]);
	}
}

//calculates the sum of the integers
int CalculateSum(int i, int nums[], int *number) {
	int sum=0;
	for (i = 0; i < *number; i++)
	{
		sum = sum + nums[i];
	}
	return sum;
}

//prints the sum onto an output file
void SaveSum(int sum, FILE *outPtr) {
	fprintf(outPtr, "The sum of the integers is %d.", sum);
}