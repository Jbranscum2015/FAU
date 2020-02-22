/*Jared Branscum COP 2220
October 12, 2016
October 12 loops and pointers*/

#include <stdio.h>
#include <ctype.h>
#define _CRT_SECURE_NO_WARNINGS

int main() {
	int i, num, prod = 1;
	printf("Enter number ");
	scanf("%d", &num);

	for (i = 0; i < num; i++)
	{
		printf("%d\n", i + 1);
		prod = prod * (i + 1);
	}
}