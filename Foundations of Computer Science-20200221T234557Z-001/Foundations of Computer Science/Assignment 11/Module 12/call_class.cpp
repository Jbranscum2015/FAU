//preprocessor directives
#include <iostream>
#include "call_class.h"
#include <fstream>
#include <iomanip>

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
		cout << "The call_DB list has been initialized in the default constructor" << endl;
	}
	input.close();
}

/************************************************************************************************************************************/
//Name: copy constructor
//Precondition: call_class has not been copied into a new object with distinct memory
//Postcondition: call_class has been copied into a new object with distinct memory
//Decription: performs a deep copy and allocates different memory to the copy
/************************************************************************************************************************************/
call_class::call_class(const call_class & Org) {
	cout << "copy constructor has been called" << endl << endl;
	(*this).count = Org.count;
	this-> size = Org.size;
	call_DB = new call_record[size];
	for (int i = 0; i<count; i++)
	{
		call_DB[i] = Org.call_DB[i];
	}
}

/***********************************************************************************************************************************/
//Name: is_empty
//Precondition: function has not returned a boolean value
//Postcondition: function returns true or false
//Decription: returns true if call_DB is empty
/**********************************************************************************************************************************/
bool call_class::is_empty()
{
	return count == 0;
}

/**********************************************************************************************************************************/
//Name: is_full 
//Precondition: function has not returned a boolean value
//Postcondition: function returns true or false
//Decription: returns true if call_DB is full
/*********************************************************************************************************************************/
bool call_class::is_full()
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
	cout << endl << "Please enter first name: ";
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
//Name: operator-
//Precondition: key has not been found in call_DB and/or removed
//Postcondition: key and the contents stored at the location of key is removed from call_DB if key is in call_DB
//Decription: remove key from call_DB if it is there.
/*******************************************************************************************************************************/
call_class & call_class::operator-(const string key)
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
		if (is_empty() == true) {
			cout << "The list is now empty" << endl << endl;
		}
		else {
			cout << "The contents of " << key << " in the list has been removed" << endl << endl;
		}
	}
	return *this;
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
//Name: operator<<
//Precondition: call_record array has not been printed onto the screen
//Postcondition: call_record array has been printed onto the screen
//Decription: Overloading operator<< as a friend function. Prints every field of every call_record in call_DB 
//                   formatted to the screen.
/***************************************************************************************************************************/
ostream & operator<<(ostream & out, call_class & Org)
{
	unsigned int firstmaxlength = 0, secondmaxlength = 0;
	int fspacing[25];
	int lspacing[25];

	//help format the output
	out.setf(ios::left);
	out.setf(ios::showpoint);
	out.precision(2);
	out.setf(ios::fixed);

	//max length of first name
	for (signed int i = 0; i < Org.count; i++) {
		if (Org.call_DB[i].firstname.length() > firstmaxlength) {
			firstmaxlength = Org.call_DB[i].firstname.length();
		}
	}
	//max length of last name
	for (signed int i = 0; i < Org.count; i++) {
		if (Org.call_DB[i].lastname.length() > secondmaxlength) {
			secondmaxlength = Org.call_DB[i].lastname.length();
		}
	}
	//spacing between first name and longest first name
	for (signed int i = 0; i < Org.count; i++) {
		fspacing[i] = firstmaxlength - Org.call_DB[i].firstname.length();
	}
	//spacing  between last name and longest last name
	for (signed int i = 0; i < Org.count; i++) {
		lspacing[i] = secondmaxlength - Org.call_DB[i].lastname.length();
	}
	//the standard output stream
	if (Org.is_empty()) {
		out << endl << "The list is empty" << endl;
	}
	else {
		for (int i = 0; i < Org.count; i++) {
			//The spacing between the last name and the cell number is different because the full name can vary in length,
			//so setw(call_DB[i].lastname.length() + fspacing[i] + lspacing[i] + 1) spaces it out so that there are two whitespaces in between the longest full name
			//and the cell number. The spacing for the other names will vary, resulting in lined up columns.
			out << Org.call_DB[i].firstname << " " << setw(Org.call_DB[i].lastname.length() + fspacing[i] + lspacing[i] + 1) << Org.call_DB[i].lastname
				<< setw(13) << Org.call_DB[i].cell_number << setw(5) << Org.call_DB[i].relays << setw(5) << Org.call_DB[i].call_length << setw(7) << Org.call_DB[i].net_cost
				<< setw(6) << Org.call_DB[i].tax_rate << setw(6) << Org.call_DB[i].call_tax << Org.call_DB[i].total_cost << endl;
		}
	}
	//must have this statement
	return out;
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
	cout << endl << "Inside the destructor" << endl;
	delete[] call_DB;
	call_DB = 0;
}