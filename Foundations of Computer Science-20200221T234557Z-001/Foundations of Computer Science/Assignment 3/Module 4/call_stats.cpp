/************************************************************************************************************************

Name: Jared Branscum                Z#: 23353586
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date: January 30, 2017                 Due Time: 11:59pm
Total Points: 20
Assignment 3: call_stats.cpp

Description:
This assignment is an extension of Assignment#1. I will implement a
program called "call_stats.cpp" to process customer call records. Each customer
call record contains seven fields, which are as follows: 1) a ten digit cell phone
number (string, no dashes), 2) the number of relay stations used in making the
call (integer), 3) the length of the call in minutes (integer), 4) the net cost of the
call (double), 5) the tax rate (double), 6) the call tax (double) and 7) the total
cost of the call (double). The program will have 3 functions: Input, Process
and Output. The main program will call each function until the end of the
datafile has been read.
*************************************************************************************************************************/

//Include the following

#include <iostream>
#include <string>
#include <fstream> 
using namespace std;

/*********************************************************
//Following is the declaration of a call record
**********************************************************/
class call_record
{
public:
	string cell_number;
	int relays;
	int call_length;
	double net_cost;
	double tax_rate;
	double call_tax;
	double total_cost;
};


//Prototypes for your functions: Input, Output, and Process will go here
//no need to name the formal parameters

void Input(ifstream &, call_record &);
void Output(const call_record &);
void Process(call_record &);

//Function Implementations

///*************************************************************************************
//Name:  Input
//Precondition: The formal parameters have not been initialized
//Postcondition: The formal parameters have been initialized
//Description: Get input (values of cell_number, relays, and call_length) from the file "call_data.txt" and store in call record.

//PURPOSE: TO READ INPUT AND USE INPUT (CALL BY VALUE) & OUTPUT (CALL BY VALUE) PARAMETERS

//*************************************************************************************

void Input(ifstream & input, call_record & customer_record) // example using the call by reference mechanism in C++ -- call record is passed by reference --note & operator
{

	input >> customer_record.cell_number;
	input >> customer_record.relays;
	input >> customer_record.call_length;
}

///*************************************************************************************
//Name:  Output
//Precondition: The formal parameters have not been printed onto the screen
//Postcondition: Formal parameters will be printed onto the screen
//Description: Display the values received from the input and the calculations
//*************************************************************************************


void Output(const call_record & customer_record)
{
	//These following statements help format the output. These statements are called the magic formula.
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout.setf(ios::fixed);
	/********************************************/

	cout << customer_record.cell_number << "  ";
	cout << customer_record.relays << "   ";
	cout << customer_record.call_length << "   ";
	cout << customer_record.net_cost << "   ";
	cout << customer_record.tax_rate << "   ";
	cout << customer_record.call_tax << "   ";
	cout << customer_record.total_cost << endl;
}

///*************************************************************************************
//Name:  Process
//Precondition: The state what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does (purpose).
//*************************************************************************************

//Note: there is one 1 input/output parameter
void Process(call_record & customer_record)
{
	//determine tax rate
	if (customer_record.relays >= 0 && customer_record.relays <= 5)
		customer_record.tax_rate = 0.01;
	else if (customer_record.relays >= 6 && customer_record.relays <= 11)
		customer_record.tax_rate = 0.03;
	else if (customer_record.relays >= 12 && customer_record.relays <= 20)
		customer_record.tax_rate = 0.05;
	else if (customer_record.relays >= 21 && customer_record.relays <= 50)
		customer_record.tax_rate = 0.08;
	else {
		customer_record.tax_rate = 0.12;
	}

	//calculate net cost
	customer_record.net_cost = customer_record.relays / 50.0 * 0.40 * customer_record.call_length;

	//calculate call tax
	customer_record.call_tax = customer_record.net_cost * customer_record.tax_rate;

	//calculate total cost
	customer_record.total_cost = customer_record.net_cost + customer_record.call_tax;
}

//Here is your driver to test the program
int main()
{
	//declaring the customer record
	call_record customer_record;

	ifstream in;    //declaring an input file stream
	in.open("call_data.txt");

	//in case the file does not open correctly
	if (in.fail())
	{
		cout << "Input file did not open correctly" << endl;
	}
	else
	{
		cout << "The following are the call records:" << endl << endl;

		while (!in.eof())
		{
			Input(in, customer_record);
			Process(customer_record);
			Output(customer_record);
		}
	}
	in.close();

	return 0;
}
