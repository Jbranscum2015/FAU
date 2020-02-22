/*Jared Branscum COP 2220
August 31, 2016
variables and printf, scanf*/

//preprocessor  directive
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int num;
	double money;
	char initial;

	printf("Enter an integer: \n");
	scanf("%d", &num);
	printf("Enter a character> \n");
	scanf(" %c", &initial);
	printf("Enter a double ");
	scanf("%lf", &money);

	printf(("the number is %d and the money is $%.2f\n"), num, money );

	printf("The number + 5 equals %d \n", num + 5);

	return 0;
}