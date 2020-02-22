/************************************************************************************************************************
Name: Jared Branscum          Z#: 23353586
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date: 3/27/17              Due Time: 11:59 P.M.
Total Points: 10
Assignment 8: call_stats5

Description: This assignment is an extension of Programming Assignment 3. I will implement a
program to manage a dynamic array of call records called "call_stats5.cpp". I will read the contents of a data file one record
at a time in a dynamic array. I will process the data that was read from the data file one record at a time,
into a dynamic array, then print the records in a dynamic array to a datafile using an ofstream object.
I will use the operator new to allocate memory for a dynamic array. I will also use the operator delete to
de-allocate the memory allocated by the new (basically, making previously used memory available for use again).
I will copy the content of one dynamic array into another dynamic array (basically, copying memory from one location to another).
I will be able to use the fstream library, a dynamic array of record records, an ifstream object, and an ofstream object.
************************************************************************************************************************/

//preprocessor directives
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class call_record {
public:
	string firstname;
	string lastname;
	string cell_number;
	int relays;
	int call_length;
	double net_cost;
	double tax_rate;
	double call_tax;
	double total_cost;
};

//function prototypes
void Initialize(call_record *&, int &, int &); //read data file and store into call_record array
bool Is_empty(const int); //inline implementation
bool Is_full(const int, int); //inline implementation
int Search(const call_record *, const int, const string); //returns location if item in list1; otherwise, return -1
void Add(call_record * &, int &, int &, const string); //adds item in order to the list
void Remove(call_record *, int &, const string); //removes an item from the list
void Double_size(call_record * &, int &, int &); //double the capacity of the call_record array
void Process(call_record *, const int &); //processes the input and calculates the other values
void Print(const call_record *, int &); //prints all the elements in the list to the screen
void Destroy_call_DB(call_record * &); //de-allocates all memory allocate to call_DB by operator new

int main() {
	int size = 5; //total amount of memory (cells) allocated for the dynamic array of call records
	int count = 0; //count number of elements in array
	char choice; //user's response
	string key; //target string
	call_record *call_DB = new call_record[size]; //declares call_record pointer to call_record array

	Initialize(call_DB, count, size);
	do {
		//menu
		cout << "Please pick one of the following: " << endl << endl;
		cout << "Add an entry (A)" << endl << endl << "Remove an entry(R)" << endl << endl;
		cout << "Print the list(P)" << endl << endl;
		cin >> choice;
		choice = toupper(choice);
		if (choice == 'A') {
			cout << endl << "Please enter a phone number: ";
			cin >> key;
			Add(call_DB, count, size, key);
			cout << "Your entry has been added" << endl << endl;
		}
		else if (choice == 'R') {
			cout << endl << "Please enter a phone number: ";
			cin >> key;
			cout << endl;
			Remove(call_DB, count, key);
		}
		else if (choice == 'P'){
			Process(call_DB, count);
			Print(call_DB, count);
	}
		else {
			cout << endl << "Invalid option" << endl << endl;
		}
		cout << "Would you like to pick another option? (Y or N)" << endl;
		cin >> choice;
		choice = toupper(choice);
	} while (choice != 'N');
	Destroy_call_DB(call_DB);
	return 0;
}

//function definitions

//Name: Initialize
//Precondition: values in call_DB have not been initialized and call_DB is empty
//Postcondition: values in call_DB have been initialized and enough memory has been allocated to call_DB to store these values
//Description: Reads the data file of call information (cell number, relays and call length) into the 
//dynamic array of call record, //call_DB. If the count because equal to the size the function double_size 
//is called and the memory allocated to call_DB is doubled.
void Initialize(call_record *& call_DB, int & count, int & size) {
	bool capacity;
	ifstream input;
	input.open("callstats_data.txt");
	//in case file does not open correctly
	if (input.fail()) {
		cout << "The file did open correctly." << endl;
	}
	else {
		while (!input.eof()) {
			capacity = Is_empty(count);
			if (capacity == true){
				cout << "The list is empty" << endl;
			}
			capacity = Is_full(count, size);
			if (capacity == true) {
				Double_size(call_DB, count, size);
			}
			input >> call_DB[count].firstname;
			input >> call_DB[count].lastname;
			input >> call_DB[count].cell_number;
			input >> call_DB[count].relays;
			input >> call_DB[count].call_length;
			count++;
		}
	}
	cout << "The call_DB list has been initialized" << endl;
}

//Name: Is_empty
//Precondition: function has not returned a boolean value
//Postcondition: function returns true or false
//Description: function returns true if call_DB was empty, otherwise it returns false
bool Is_empty(const int count) {
	if (count == 0) {
		return true;
	}
	return false;
}

//Name: Is_full
//Precondition: function has not returned a boolean value
//Postcondition: function returns true or false
//Description: returns true if call_DB was full
bool Is_full(const int count, const int size) {
	if (count == size) {
		return true;
	}
	return false;
}

//Name: Search
//Precondition: location of key in call_DBs is undetermined
//Postcondition: location of key in call_DB will be returned
//Description: locates key in call_DB if it is there; otherwise, -1 is returned
int Search(const call_record *call_DB, const int count, const string key) {
	for (int i = 0; i < count; i++) {
		if (call_DB[i].cell_number == key) {
			return i;
		}
	}
	return -1;
}

//Name: Add
//Precondition: entry has not been added into call_DB
//Postcondition: entry has been added into call_DB
//Description: add key to call_DB; if call_DB is full, double_size is called to increase the size of call_DB
void Add(call_record *&call_DB, int & count, int & size, const string key) {
	bool capacity;
	//prompted user input
	cout << "Please enter first name: ";
	cin >> call_DB[count].firstname;
	cout << "Please enter last name: ";
	cin >> call_DB[count].lastname;
	cout << "Please enter number of relays: ";
	cin >> call_DB[count].relays;
	cout << "Please enter call length in minutes: ";
	cin >> call_DB[count].call_length;
	call_DB[count].cell_number = key;
	count++;
	//if the array is full, this allocates more memory to it
	capacity = Is_full(count, size);
	if (capacity == true) {
		Double_size(call_DB, count, size);
	}
}

//Name: Remove
//Precondition: key has not been found in call_DB and/or removed
//Postcondition: key and the contents stored at the location of key is removed from call_DB if key is in call_DB
//Description: remove key from call_DB if it is there
void Remove(call_record *call_DB, int & count, const string key) {
	int loc;
	loc = Search(call_DB, count, key);
	//if target is not in the list
	if (loc == -1)
		cout << "That cell phone number does not exist in the list" << endl << endl;
	else {
		for (int i = 0; i < count; i++) {
			loc = Search(call_DB, count, key);
			if (loc != -1) {
				for (int i = loc; i < count; i++) {
					//shifts every cell after the target to the cell before it
					call_DB[i] = call_DB[i + 1];
				}
				//decrements count
				count--;
			}
		}
		if (loc == -1)
			cout << "The contents of " << key << " in the list has been removed" << endl << endl;
	}
}

//Name: Double_size
//Precondition: call_record array is full or does not have enough allocated memory
//Postcondition: the amount of allocated memory is doubled
//Description: doubles the size (capacity) of call_DB by creating a temporary pointer 
//to a call_record array type with 2 times the amount of previous allocated memory
void Double_size(call_record *&call_DB, int & count, int & size) {
	size *= 2;
	call_record * temp = new call_record[size];
	for (int i = 0; i < count; i++) {
		temp[i] = call_DB[i];
	}
	delete[] call_DB;
	call_DB = temp;
}

//Name: Process
//Precondition: tax_rate, net_cost, call_tax, and total_cost have not been initialized in call_record array 
//Postcondition: tax_rate, net_cost, call_tax, and total_cost have been initialized in call_record array 
//Description: calculate tax rate, the net cost, call tax and total cost for every call record in call_DB
void Process(call_record * call_DB, const int & count) {
	//determine tax rate
	for (int i = 0; i < count; i++) {
		if (call_DB[i].relays >= 0 && call_DB[i].relays <= 5)
			call_DB[i].tax_rate = 0.01;
		else if (call_DB[i].relays >= 6 && call_DB[i].relays <= 11)
			call_DB[i].tax_rate = 0.03;
		else if (call_DB[i].relays >= 12 && call_DB[i].relays <= 20)
			call_DB[i].tax_rate = 0.05;
		else if (call_DB[i].relays >= 21 && call_DB[i].relays <= 50)
			call_DB[i].tax_rate = 0.08;
		else {
			call_DB[i].tax_rate = 0.12;
		}

		//calculate net cost
		call_DB[i].net_cost = (call_DB[i].relays / 50.0) * 0.40 * (call_DB[i].call_length);

		//calculate call tax
		call_DB[i].call_tax = call_DB[i].net_cost * call_DB[i].tax_rate;

		//calculate total cost
		call_DB[i].total_cost = call_DB[i].net_cost + call_DB[i].call_tax;
	}
}

//Name: Print
//Precondition: call_record array has not been printed onto the screen
//Postcondition: call_record array has been printed onto the screen
//Description: prints every field of every call_record in call_DB formatted to the screen
void Print(const call_record *call_DB, int & count) {
	unsigned int firstmaxlength = 0, secondmaxlength = 0;
	int fspacing[25];
	int lspacing[25];
	bool capacity;

	//help format the output
	cout.setf(ios::left);
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout.setf(ios::fixed);

	//max length of first name
	for (signed int i = 0; i < count; i++) {
		if (call_DB[i].firstname.length() > firstmaxlength) {
			firstmaxlength = call_DB[i].firstname.length();
		}
	}
	//max length of last name
	for (signed int i = 0; i < count; i++) {
		if (call_DB[i].lastname.length() > secondmaxlength) {
			secondmaxlength = call_DB[i].lastname.length();
		}
	}
	//spacing between first name and longest first name
	for (signed int i = 0; i < count; i++) {
		fspacing[i] = firstmaxlength - call_DB[i].firstname.length();
	}
	//spacing  between last name and longest last name
	for (signed int i = 0; i < count; i++) {
		lspacing[i] = secondmaxlength - call_DB[i].lastname.length();
	}
	//the standard output stream
	capacity = Is_empty(count);
	if (capacity == true) {
		cout << endl << "The list is empty" << endl;
	}
	else {
		for (int i = 0; i < count; i++) {
			//The spacing between the last name and the cell number is different because the full name can vary in length,
			//so setw(call_DB[i].lastname.length() + fspacing[i] + lspacing[i] + 1) spaces it out so that there are two whitespaces in between the longest full name
			//and the cell number. The spacing for the other names will vary, resulting in lined up columns.
			cout << call_DB[i].firstname << " " << setw(call_DB[i].lastname.length() + fspacing[i] + lspacing[i] + 1) << call_DB[i].lastname;
			cout << setw(13) << call_DB[i].cell_number << setw(5) << call_DB[i].relays << setw(5) << call_DB[i].call_length << setw(7) << call_DB[i].net_cost;
			cout << setw(6) << call_DB[i].tax_rate << setw(6) << call_DB[i].call_tax << call_DB[i].total_cost << endl;
		}
	}
	cout << endl;
}

//Name: Destroy_call_DB
//Precondition: memory was allocated to call_DB
//Postcondition: memory is deallocated from call_DB
//Description: de-allocates all memory allocated to call_DB; last function to be called before program is exited
void Destroy_call_DB(call_record * &call_DB) {
	delete [] call_DB;
	call_DB = 0;
}