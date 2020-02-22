/*Jared Branscum COP 2220
November 19, 2016
Program 3*/

//preprocessor directive
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//function prototypes

//greets the user
void Greeting();

//Asks the user if they want to use the pluralizer
void DoIt(char *agreePtr);

//gets the word from the user
void GetWord(char word[]);

//finds the null character in the word array
int FindNull(char word[]);

//copies the word to plural and changes plural to lowercase 
void ChangeCaseandCopy(char word[], char plural[], int count);

//determines which rule applies to the word
int DetermineRule(char plural[], int count);

//removes y and adds ies to the end of the word
void RuleOne(char plural[], int count);

//adds es to the end of the word
void RuleTwo(char plural[], int count);

//adds s to the end of the word
void RuleThree(char plural[], int count);

//saves original word and plural form into the output file "pluralWords.txt"
void SaveWords(char word[], char plural[], int count, FILE *outPtr);

int main() {
	//declare variables
	FILE *outPtr;
	char word[20]="";
	char plural[25]="";
	char agree;
	int null, rule, i;

	Greeting();
	outPtr = fopen("pluralWords.txt", "w");

	DoIt(&agree);
	agree = tolower(agree);

	while (agree == 'y') {
		GetWord(word);
		//this is equivalent to the number of elements in the array
		null = FindNull(word);
		ChangeCaseandCopy(word, plural, null);
		rule = DetermineRule(plural, null);

		if (rule == 1) {
			RuleOne(plural, null);
			null += 2;
		}
		else if (rule == 2) {
			RuleTwo(plural, null);
			null += 2;
		}
		else if (rule == 3) {
			RuleThree(plural, null);
			null += 1;
		}
		printf("\nWord is ");
		for (i = 0; i < null; i++) {
			if (word[i] != '\0') {
				printf("%c", word[i]);
			}
		}
		printf(" Plural is ");
		for (i = 0; i < null; i++) {
			if (plural[i] != '\0') {
				printf("%c", plural[i]);
			}
		}
		printf("\nAdding the words to the file ...");
		SaveWords(word, plural, null, outPtr);
		DoIt(&agree);
	}
	printf("\n\nThanks for checking out the Pluralizer!");
	printf("\nThe output file pointer is closing now.\n");
	fclose(outPtr);
	return 0;
}

//greets the user
void Greeting() {
	printf("*********  Welcome to the Pluralizer   ***********");
	printf("\n\nThe output file pluralWords.txt  is open");
}

//Asks the user if they want to use the pluralizer
void DoIt(char *agreePtr)
{
	printf("\n\nWould you like to pluralize a word? y (yes) or n (no) ");
	scanf(" %c", agreePtr);
}

//gets the word from the user
void GetWord(char word[]) {
	printf("\nPlease insert the word you'd like to pluralize: ");
	scanf("%s", word);
}

//finds the null character in the word array
int FindNull(char word[]) {
	int i;
	for (i = 0; i<19; i++) {
		if (word[i] == '\0') {
			return i;
		}
	}
	return 0;
}

//copies the word to plural and changes plural to lowercase 
void ChangeCaseandCopy(char word[], char plural[], int count) {
	int i;
	for (i = 0; word[i] != '\0'; i++) {
		plural[i] = word[i];
	}
	plural[i] = '\0';

	for (i = 0; i < count; i++) {
		plural[i] = tolower(plural[i]);
	}
}

//determines which rule applies to the word
int DetermineRule(char plural[], int count) {
	if (plural[count - 1] == 'y') {
		return 1;
	}
	else if (plural[count - 1] == 's') {
		return 2;
	}
	else if (plural[count - 2] == 's' && plural[count - 1] == 'h') {
		return 2;
	}
	else if (plural[count - 2] == 'c' && plural[count - 1] == 'h') {
		return 2;
	}
	else {
		return 3;
	}
}

//removes y and adds ies to the end of the word
void RuleOne(char plural[], int count) {
	plural[count - 1] = 'i';
	plural[count] = 'e';
	plural[count + 1] = 's';
	plural[count + 2] = '\0';

}

//adds es to the end of the word
void RuleTwo(char plural[], int count) {
	plural[count] = 'e';
	plural[count + 1] = 's';
	plural[count + 2] = '\0';
}

//adds s to the end of the word
void RuleThree(char plural[], int count) {
	plural[count] = 's';
	plural[count + 1] = '\0';
}

//saves original word and plural form into the output file "pluralWords.txt"
void SaveWords(char word[], char plural[], int count, FILE *outPtr) {
	int i;

	fprintf(outPtr, "Word is ");
	for (i = 0; i < count; i++) {
		if (word[i] != '\0') {
			fprintf(outPtr, "%c", word[i]);
		}
	}

	fprintf(outPtr, " Plural is ");
	for (i = 0; i < count; i++) {
		if (plural[i] != '\0') {
			fprintf(outPtr, "%c", plural[i]);
		}
	}
	fprintf(outPtr, "\n");
}