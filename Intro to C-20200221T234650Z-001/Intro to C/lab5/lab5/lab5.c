
/*Jared Branscum COP2220
November 16, 2016
Lab 5
*/

#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#define SIZE 20

typedef struct {
	char artist[SIZE];
	char songName[SIZE];
	int len;
	double cost;
}song;

//Function Prototypes

// fills the data fields of a song instance
//returns the filled song 
song FillSong();

//fills the data fields of a song instance
//by reference using a pointer to a song
void FillSongPtr(song *songptr);

//fills an array of songs
void FillSongArray(song arrayC[], int *size);


//displays one song
void DisplaySong(song anyCard);

int main()
{

	//Declare variables
	song mySong, mySong1, mySong2;
	song playlist[SIZE];
	int sSize;
	int i;

	//Fill structures with a function
	mySong = FillSong();
	mySong1 = FillSong();

	//print using display function
	printf("\n---------Display mySong\n");
	DisplaySong(mySong);
	printf("\n---------Display mySong1\n");
	DisplaySong(mySong1);

	//Fill structure using pointers and display it
	FillSongPtr(&mySong2);
	printf("\n---------Display mySong2\n");
	DisplaySong(mySong2);

	//Fill the array with the function
	printf("\n---------Fill array playlist\n");
	FillSongArray(playlist, &sSize);

	//display an array of songs
	printf("\n---------Display array playlist\n");
	for (i = 0; i<sSize; i++)
	{
		DisplaySong(playlist[i]);
	}

	return 0;
}

//Function Definitions


// fills the data fields of a song instance
//returns the filled song
song FillSong()
{
	//Declare local variables
	song tempS;
	//prompt and get information
	printf("\nplease enter the artist of your song:  ");
	scanf("%s", tempS.artist);
	//print to check
	printf("artist:  %s\n", tempS.artist);

	//prompt and get information
	printf("\nplease enter the song name:  ");
	scanf("%s", tempS.songName);
	//print to check
	printf("song name:  %s\n", tempS.songName);

	//prompt and get information
	printf("\nplease enter the song length in seconds of your song:  ");
	scanf("%d", &tempS.len);
	//print to check
	printf("song length:  %d\n", tempS.len);

	//prompt and get information
	printf("\nplease enter the cost of the song:  ");
	scanf("%lf", &tempS.cost);
	//print to check
	printf("cost:  %.2f\n", tempS.cost);



	return tempS;
}



//displays one song
void DisplaySong(song anySong)
{
	printf("\n\nartist:  %s\n", anySong.artist);
	printf("song name:  %s\n", anySong.songName);
	printf("song length:  %d\n", anySong.len);
	printf("cost:  %.2f\n", anySong.cost);
}


//fills the data fields of a song instance
//by reference using a pointer to a song
void FillSongPtr(song *songptr)
{
	//prompt and get information
	printf("\nplease enter the artist of your song:  ");
	scanf("%s", (*songptr).artist);

	//prompt and get information
	printf("\nplease enter the song name:  ");
	scanf("%s", songptr->songName);

	//prompt and get information
	printf("\nplease enter the song length in seconds of your song:  ");
	scanf("%d", &(*songptr).len);

	//prompt and get information
	printf("\nplease enter the cost your song:  ");
	scanf("%lf", &(*songptr).cost);
}




//fills an array of songs
void FillSongArray(song arrayS[], int *size)
{
	int i;
	//prompt the user
	printf("\nenter the number of songs:  ");
	scanf("%d", size);

	//print to check
	printf("size:  %d\n", *size);

	for (i = 0; i < *size; i++)
	{
		printf("enter artist:  ");
		scanf("%s", arrayS[i].artist);

		printf("enter song name:  ");
		scanf("%s", arrayS[i].songName);

		printf("enter song length:  ");
		scanf("%d", &arrayS[i].len);

		printf("enter cost:  ");
		scanf("%lf", &arrayS[i].cost);
	}
}
