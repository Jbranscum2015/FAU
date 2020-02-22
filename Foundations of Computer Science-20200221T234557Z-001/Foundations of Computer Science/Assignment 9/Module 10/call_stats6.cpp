/************************************************************************************************************************
Name: Jared Branscum          Z#: 23353586
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date: 4/10/17              Due Time: 11:59 P.M.
Total Points: 20
Assignment 9: call_stats6

Description:
This assignment is an extension of Programming Assignment 5,(Unit 9’s
Programming Assignment). I will implement a class called “call_class”. The class
will manage a dynamic array of call records called "call_stats6.cpp". I will develop 
and use an ADT to define a class to manage a dynamic array, use a default constructor
to initialize the state of the class, and use a destructor to de-allocate memory allocated using the new operator
*************************************************************************************************************************/

//preprocessor directives

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

//class definition
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

class call_class {
public:
	call_class();
	//deallocates all memory allocated to call_DB by operator new
	~call_class();
	bool is_empty() const;
	bool is_full() const;
	//returns location if item in list1; otherwise return -1
	int search(const string key) const;
	//adds a call_record to call_DB
	void add();
	//removes an item from the list
	void remove(const string key);
	void double_size();
	void process();
	//prints all elements in the list to the screen
	void print();
private:
	int count;
	int size;
	call_record *call_DB;
};

int main() {
	call_class MyClass;
	char choice;
	string key;
	do {
		//menu
		cout << "Please pick one of the following: " << endl << endl;
		cout << "Add an entry (A)" << endl << endl << "Remove an entry(R)" << endl << endl;
		cout << "Print the list(P)" << endl << endl;
		cin >> choice;
		choice = toupper(choice);
		if (choice == 'A') {
			MyClass.add();
		}
		else if (choice == 'R') {
			cout << endl << "Please enter a phone number: ";
			cin >> key;
			cout << endl;
			MyClass.remove(key);
		}
		else if (choice == 'P') {
			MyClass.process();
			MyClass.print();
		}
		else {
			cout << endl << "Invalid option" << endl << endl;
		}
		cout << "Would you like to pick another option? (Y or N)" << endl;
		cin >> choice;
		choice = toupper(choice);
	} while (choice != 'N');
	return 0;
}

/************************************************************************************************************************************/
//Name: default constructor
//Precondition: Values in call_DB have not been initialized
//Postcondition: Values in call_DB have been initialized
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record, 
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
call_class::call_class()
{
	count = 0;
	size = 5;
	call_DB = new call_record[size];
	ifstream input;
	input.open("callstats_data.txt");
	//in case file does not open correctly
	if (input.fail()) {
		cout << "The file did open correctly." << endl;
	}
	else {
		while (!input.eof()) {
			if (is_full()) {
				double_size();
			}
			input >> call_DB[count].firstname
				>> call_DB[count].lastname
				>> call_DB[count].cell_number
				>> call_DB[count].relays
				>> call_DB[count].call_length;
			count++;
		}
	}
	cout << "The call_DB list has been initialized in the default constructor" << endl;
	input.close();
}

/***********************************************************************************************************************************/
//Name: is_empty
//Precondition: function has not returned a boolean value
//Postcondition: function returns true or false
//Decription: returns true if call_DB is empty
/**********************************************************************************************************************************/
bool call_class::is_empty() const
{
	return count == 0;
}

/**********************************************************************************************************************************/
//Name: is_full 
//Precondition: function has not returned a boolean value
//Postcondition: function returns true or false
//Decription: returns true if call_DB is full
/*********************************************************************************************************************************/
bool call_class::is_full() const
{
	return count == size;
}

/**********************************************************************************************************************************/
//Name: search
//Precondition: location of key in call_DBs is undetermined
//Postcondition: location of key in call_DB will be returned
//Decription: locates key in call_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int call_class::search(const string key) const
{
	for (int i = 0; i < count; i++) {
		if (call_DB[i].cell_number == key) {
			return i;
		}
	}
	return -1;
}

/*********************************************************************************************************************************/
//Name: add
//Precondition: entry has not been added into call_DB
//Postcondition: entry has been added into call_DB
//Decription: adds a call_record to call_DB; if call_DB is full, double_size is called to increase the size of call_DB. The user 
//            is prompted to enter the firstname, lastname, cell number, relays and call length. 
/********************************************************************************************************************************/
void call_class::add()
{
	//prompted user input
	cout << "Please enter first name: ";
	cin >> call_DB[count].firstname;
	cout << "Please enter last name: ";
	cin >> call_DB[count].lastname;
	cout << "Please enter call number: ";
	cin >> call_DB[count].cell_number;
	cout << "Please enter number of relays: ";
	cin >> call_DB[count].relays;
	cout << "Please enter call length in minutes: ";
	cin >> call_DB[count].call_length;
	count++;
	//if the array is full, this allocates more memory to it
	if (is_full()) {
		double_size();
	}
	cout << "Your entry has been added" << endl << endl;
}

/********************************************************************************************************************************/
//Name: remove
//Precondition: key has not been found in call_DB and/or removed
//Postcondition: key and the contents stored at the location of key is removed from call_DB if key is in call_DB
//Decription: remove key from call_DB if it is there.
/*******************************************************************************************************************************/
void call_class::remove(const string key)
{
	int loc;
	loc = search(key);
	//if target is not in the list
	if (loc == -1)
		cout << "That cell phone number does not exist in the list" << endl << endl;
	else {
		for (int i = 0; i < count; i++) {
			loc = search(key);
			if (loc != -1) {
				for (int i = loc; i < count; i++) {
					//shifts every cell after the target to the cell before it
					call_DB[i] = call_DB[i + 1];
				}
				//decrements count
				count--;
			}
		}
	}
	if (is_empty() == true) {
		cout << "The list is empty" << endl << endl;
	}
	else {
		cout << "The contents of " << key << " in the list has been removed" << endl << endl;
	}
}

/******************************************************************************************************************************/
//Name: double_size
//Precondition: call_record array is full or does not have enough allocated memory
//Postcondition: the amount of allocated memory is doubled
//Decription: doubles the size (capacity) of call_DB
/******************************************************************************************************************************/
void call_class::double_size()
{
	size *= 2;
	call_record *temp = new call_record[size];

	for (int i = 0; i<count; i++)
	{
		temp[i] = call_DB[i];
	}

	delete[] call_DB;
	call_DB = temp;
}


/******************************************************************************************************************************/
//Name: process
//Precondition: tax_rate, net_cost, call_tax, and total_cost have not been initialized in call_record array 
//Postcondition: tax_rate, net_cost, call_tax, and total_cost have been initialized in call_record array 
//Decription: calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void call_class::process()
{
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

/****************************************************************************************************************************/
//Name: print
//Precondition: call_record array has not been printed onto the screen
//Postcondition: call_record array has been printed onto the screen
//Decription: prints every field of every call_record in call_DB formatted to the screen.
/***************************************************************************************************************************/
void call_class::print()
{
	unsigned int firstmaxlength = 0, secondmaxlength = 0;
	int fspacing[25];
	int lspacing[25];

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
	if (is_empty()) {
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
}

/****************************************************************************************************************************/
//Name: destructor
//Precondition: memory was allocated to call_class
//Postcondition: memory is deallocated from call_class
//Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
//            is exited.
/***************************************************************************************************************************/
call_class:: ~call_class()
{
	cout << endl << "Inside the destructor\n";
	delete[] call_DB;
	call_DB = 0;
}