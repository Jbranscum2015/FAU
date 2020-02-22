
/*Jared Branscum COP2220
December 7, 2016
Program 4
*/

#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define SIZE 50

typedef struct {
	char artist[20];
	char songName[25];
	int id;
	int len;
	double cost;
	double retail;
}song;

//Function Prototypes

//Greets the user
void Greeting();

//Hardcode Six entries
void HardCodeSix(song[]);

//runs the menu and gets the user's choice
void Menu(char *choice);

//prints the contents of the list onto the screen
void PrintList(song[], int count);

//prints a report to a file
void PrintReport(song[], int count);

//adds an item to the list
void Add(song[], int count);

//removes an item from the list
//takes three arguments, the list, the number of items, and the location
void Delete(song[], int count, int loc);

//updates the sale/retail price
//takes three arguments, the list, the number of items, and the location
void UpdatePrice(song[], int count, int loc);

//searches the list by id and returns the index, if there is a match or returns -1
//three arguments: list, number of items, id
int Search(song[], int count, int loc);

//diplays the ids in the list, gets the id from the user and returns it
int DisplayIds(song[], int count);


int main()
{
	//Declare variables
	song list[SIZE];
	int count = 0, loc, id;
	char choice;

	Greeting();
	HardCodeSix(list);
	count = 6;
	Menu(&choice);
	choice = toupper(choice);

	while (choice != 'Q' && choice != 'q') {
		if (choice == 'P') {
			PrintList(list, count);
		}
		else if (choice == 'A') {
			Add(list, count);
		}
		else if (choice == 'C') {
			count = 0;
			printf("\nAll records have been cleared...");
		}
		else if (choice == 'S') {
			PrintReport(list, count);
			printf("\nA save file has been created called report.txt");
		}
		else if (choice == 'D') {
			id = DisplayIds(list, count);
			loc = Search(list, count, id);
			if (loc != -1) {
				Delete(list, count, loc);
				count--;
			}
			printf("\nThe item is deleted.");
		}
		else if (choice == 'U') {
			id = DisplayIds(list, count);
			loc = Search(list, count, id);
			UpdatePrice(list, count, loc);
		}
		Menu(&choice);
		choice = toupper(choice);
	}
	
	printf("\nThank you!\n");
	return 0;
}

//Function Definitions

//Greets the user
void Greeting() {
	printf("Welcome to the song inventory");
	printf("\n\nThis program manages a list of songs");
	printf("\n\nEach song has a unique id");
	printf("\n\nChoose an option from the menu");
	printf("\n\n-----------------------------------------");
}

//Hardcode Six entries
void HardCodeSix(song list[]) {
	//first entry
	list[0].id = 123;
	strcpy(list[0].artist, "Michael Buble");
	strcpy(list[0].songName, "Cry Me A River");
	list[0].len = 256;
	list[0].cost = 0.50;
	list[0].retail = 1.99;

	//second entry
	list[1].id = 234;
	strcpy(list[1].artist, "Journey");
	strcpy(list[1].songName, "Don't Stop Believin'");
	list[1].len = 250;
	list[1].cost = 0.60;
	list[1].retail = 2.99;

	//third entry
	list[2].id = 345;
	strcpy(list[2].artist, "AC/DC");
	strcpy(list[2].songName, "Back in Black");
	list[2].len = 255;
	list[2].cost = 0.70;
	list[2].retail = 1.50;

	//fourth entry
	list[3].id = 456;
	strcpy(list[3].artist, "Queen");
	strcpy(list[3].songName, "We Are The Champions");
	list[3].len = 191;
	list[3].cost = 0.80;
	list[3].retail = 3.99;

	//fifth entry
	list[4].id = 567;
	strcpy(list[4].artist, "The Buggles");
	strcpy(list[4].songName, "Video Killed The Radio Star");
	list[4].len = 189;
	list[4].cost = 0.20;
	list[4].retail = 0.99;

	//sixth entry
	list[5].id = 678;
	strcpy(list[5].artist, "Fall Out Boy");
	strcpy(list[5].songName, "Thnks Fr Th Mmrs");
	list[5].len = 253;
	list[5].cost = 1.99;
	list[5].retail = 4.99;
}

//runs the menu and gets the user's choice
void Menu(char *choice) {
	printf("\n\nSelect an option:");
	printf("\n\nP....Print the inventory list onto the screen");
	printf("\n\nA....Add a new song entry");
	printf("\n\nC....Clear all records");
	printf("\n\nS....Create a current report (save it to a file)");
	printf("\n\nD....Delete an item from the list (inventory)");
	printf("\n\nU....Update retail price");
	printf("\n\nQ....Quit\n\n");
	
	scanf(" %c", choice);
}

//prints the contents of the list onto the screen
void PrintList(song list[], int count) {
	int i;
	if (count == 0) {
		printf("\n\nEmpty list");
	}
	for (i = 0; i < count; i++) {
		printf("\n\n\nId: %d", list[i].id);
		printf("\n\nArtist: %s", list[i].artist);
		printf("\n\nSong name: %s", list[i].songName);
		printf("\n\nSong length: %d", list[i].len);
		printf("\n\nCost: $%.2f", list[i].cost);
		printf("\n\nRetail cost: $%.2f", list[i].retail);
	}
}

//prints a report to a file
void PrintReport(song list[], int count) {
	int i;
	FILE *outPtr;

	outPtr = fopen("report.txt", "w");
	if (count == 0) {
		fprintf(outPtr, "Empty list");
	}
	for (i = 0; i < count; i++) {
		fprintf(outPtr, "\n\n\nId: %d", list[i].id);
		fprintf(outPtr, "\n\nArtist: %s", list[i].artist);
		fprintf(outPtr, "\n\nSong name: %s", list[i].songName);
		fprintf(outPtr, "\n\nSong length: %d", list[i].len);
		fprintf(outPtr, "\n\nCost: $%.2f", list[i].cost);
		fprintf(outPtr, "\n\nRetail cost: $%.2f", list[i].retail);
	}

	fclose(outPtr);
}

//adds an item to the list
void Add(song list[], int count) {
	printf("\n\nEnter id(make sure none of them are the same): ");
	scanf("%d", &list[count].id);
	printf("\n\nEnter artist: ");
	scanf("%s", list[count].artist);
	printf("\n\nEnter the name of the song: ");
	scanf("%s", list[count].songName);
	printf("\n\n\nEnter the length of the song(in seconds): ");
	scanf("%d", &list[count].len);
	printf("\n\nEnter the cost of the song: ");
	scanf("%lf", &list[count].cost);
	printf("\n\nEnter the retail price of the song: ");
	scanf("%lf", &list[count].retail);

	count++;
}

//removes an item from the list
//takes three arguments, the list, the number of items, and the location
void Delete(song list[], int count, int loc) {
	if (count == 0) {
		printf("\n\nThe list is empty, so nothing was deleted.");
	}
	else {
		list[loc] = list[count - 1];
	}
}

//updates the sale/retail price
//takes three arguments, the list, the number of items, and the location
void UpdatePrice(song list[], int count, int loc) {
	if (count != 0) {
		printf("\nThe current retail price is $%.2f", list[loc].retail);
		printf("\n\nPlease insert the new price: ");
		scanf("%lf", &list[loc].retail);
	}
	else {
		printf("\nNothing can be updated ...");
	}
}

//searches the list by id and returns the index, if there is a match or returns -1
//three arguments: list, number of items, id
int Search(song list[], int count, int id) {
	int i;
	for (i = 0; i < count; i++) {
		if (id == list[i].id) {
			return i;
		}
	}
	return -1;
}

//diplays the ids in the list, gets the id from the user and returns it
int DisplayIds(song list[], int count) {
	int i, num;
	printf("\n\nHere are the Id numbers and the Song Titles:\n");
	for (i = 0; i < count; i++) {
		printf("\n\n%d ", list[i].id);
		printf("%s", list[i].songName);
	}
	printf("\n\nInsert the id you'd like to change: ");
	scanf("%d", &num);
	return num;
}
