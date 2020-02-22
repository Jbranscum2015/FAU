/************************************************************************************************************************
Name: Jared Branscum          Z#: 23353586
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date: 3/13/17              Due Time: 11:59 P.M.
Total Points: 10
Assignment 7: charword_freq

Description: In this assignment, I will implement a program called "charword_freq.cpp"
to determine the number of words and the number of occurrences of each letter
in a block of text stored in a data file called “mytext.dat”. I will define a word to be
any string of letters that is delimited at each end by either whitespace, a period, a
comma, or the beginning or end of a line. I will assume that the input consists
entirely of letters, whitespace, commas and periods. When outputting the
number of words and letters that occur in a line, I will count upper- and
lowercase versions of a letter as the same letter. The output of the letters will be in
alphabetical order and I will only list the letters that occur in the input data file.
*************************************************************************************************************************/

//preprocessor directives
#include <string>
#include <fstream>
#include <iostream>
#include <cctype>
#include <iomanip>

using namespace std;

//function prototypes
void Input(ifstream &, string [], int &);
void LowerCase(string &);
void DetermineTarget(string, string &);
void Process(string [], int [], int, string &);
int Search(string, char);
void Output(int, const int [], string);

int main() {
	//open and connect to file stream
	ifstream in;
	in.open("mytext.dat");

	//declare variables
	string s1[60], target;
	int frequency[13], wordcount = 0;
	//in case file does not open correctly
	if (in.fail()) {
		cout << "The input file did not open correctly." << endl;
	}
	else {
		Input(in, s1, wordcount);
		Process(s1, frequency, wordcount, target);
		Output(wordcount, frequency, target);
	}
	return 0;
}

//Function Implementation

//Function name: Input
//Precondition: The string word array and int & wordcount have not been initialized
//Postcondition: The string word array and int & wordcount have been initialized
//Description: Gets input (characters) from the file "mytext.dat" and stores it into string word[]. 
//Additionally, it calls the LowerCase function for each word the getline function reads from the file 
//and calculates how many words are in the file and passes it to int wordcount by reference.
void Input(ifstream & input, string word[], int & wordcount) {
	while (!input.eof()) {
		getline(input, word[wordcount], ' ');
		LowerCase(word[wordcount]);
		wordcount++;
	}
}

//Function name: LowerCase
//Precondition: The characters in the string can be uppercase or lowercase
//Postcondition: The characters in the string are in lowercase
//Description: This changes the value of each character in the string to the lowercase value of each character
void LowerCase(string & word) {
	for (unsigned int i = 0; i < word.length(); i++) {
		word[i] = tolower(word[i]);
	}
}

//Function name: Process
//Precondition: The frequency of each letter(int frequency[]) and which letters are in the file(string & target) have not been initialized
//Postcondition: int frequency[] and string & target have been initialized
//Description: Combines all of the words in the string word[] into the first element of the word array, 
//calls the DetermineTarget function to determine which letters are in the file, and calls the Search function in a for loop to
//determine the frequency of each letter in the file
void Process(string word[], int frequency[], int wordcount, string & target) {
	//combines the words in the word array into the first element of the word array
	for (int i = 1; i < wordcount; i++) {
		word[0] += word[i];
	}
	DetermineTarget(word[0], target);
	for (unsigned int i = 0; i <= target.length(); i++) {
		frequency[i] = Search(word[0], target[i]);
	}
}

//Function name: DetermineTarget
//Precondition: The list of letters in the file(string & target) has not been initialized
//Postcondition: string & target has been initialized
//Description: It finds which letters are in the string word by rearranging the characters into lexicographical order, 
//then erases unwanted characters and characters that repeat in the string and passes this string to string target by reference.
//This target string will be compared with string word[0] to find the frequency of each letter in the data file.
void DetermineTarget(string word, string & target) {
	int j;
	char temp;
	//rearranges the string into lexicographical order
	for (unsigned int i = 0; i < word.length(); i++) {
		j = i;
		while (j > 0 && word[j] < word[j - 1]) {
			temp = word[j];
			word[j] = word[j - 1];
			word[j - 1] = temp;
			j--;
		}
	}
	//removes unwanted characters
	while (word[0] < 'a') {
		word.erase(0, 1);
	}
	//removes identical characters in the string
	for (unsigned int i = 0; i < word.length(); i++) {
		while (word[i] == word[i + 1]) {
			word.erase(i, 1);
		}
	}
	//assigns the current value of the string word to the string target
	target = word;
}

//Function name: Search
//Precondition: the number of occurences of target in the string has not been found
//Postcondition: the frequency of target in the string has been found and returned
//Description: It finds the number of times the char target is present in string word and returns that value. 
int Search(string word, char target) {
	int frequency=0;
	//compares each character in string word with the char target to determine if both are the same,
	//if so, then frequency is incremented by 1
	//Therefore, after each character in string word has been compared with target,
	//the function returns the value of frequency which is equal to the number of times the value of target is found in string word.
	for (unsigned int i = 0; i < word.length(); i++) {
			if (word[i] == target) {
				frequency ++;
		}
	}
	return frequency;
}

//Function name: Output
//Precondition: the formal parameters have not been printed onto the screen
//Postcondition: the formal parameters have been printed onto the screen
//Description: Prints the number of words and the frequency of the letters from the file onto the screen
void Output(int wordcount, const int frequency[], string target) {
	cout.setf(ios::right);
	cout << wordcount << " words" << endl;
	for (unsigned int i = 0; i < target.length(); i++) {
		//formats the output so that the columns line up
		if (frequency[i] < 10) {
			cout << frequency[i] << setw(3) << target[i] << endl;
		}
		else {
			cout << frequency[i] << setw(2) << target[i] << endl;
		}
	}
}