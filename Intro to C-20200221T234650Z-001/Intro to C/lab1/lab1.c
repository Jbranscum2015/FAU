/*Jared Branscum COP 2220
September 7, 2016
lab 1*/

//preprocessor  directive
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>

int main()
{
	int num;
	int product;
	char letter;
	printf("Hello my name is Jared. \n \n");
	printf("Please insert a number here ");
	scanf("%d", &num);
	product = num * 2;
	printf("\nThe number you put in is %d and the product of %d and 2 is equal to %d\n\n", num, num, product);
	printf("Please insert a letter ");
	scanf(" %c", &letter);
	char lowercase = tolower(letter);
	//letter = tolower(letter);
	//printf("%c \n", letter);
	char uppercase = toupper(letter);
	letter = toupper(letter);
	//printf("%c \n", letter);
	printf("\nThe lowercase version of %c is %c and the uppercase version of %c is %c \n", letter, lowercase, letter, uppercase);

	return 0;
}