/************************************************************************************************************************
Name: Jared Branscum          Z#: 23353586
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date: 2/27/17              Due Time: 11:59 P.M.
Total Points: 20
Assignment 5: call_stats4

Description: 
This assignment is an extension of Assignments 3, 4 and 5. I will implement a
program called "call_stats4.cpp" to process customer call records. I will read the
records in a datafile into an array of call records, then process each call record in the
array, and finally print the array of call records to a datafile. Each customer
call record contains seven fields, which are as follows: 1) a ten digit cell phone number
(string, no dashes), 2) the number of relay stations used in making the call (integer), 3) the
length of the call in minutes (integer), 4) the net cost of the call (double), 5) the tax rate
(double), 6) the call tax (double) and 7) the total cost of the call (double). The program
will have 3 functions: Input, Process, and Output. The main program will call each
function once.

*************************************************************************************************************************/

//preprocessor directives
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

//constant global variable
const int SIZE = 200;

//call record
class call_record {
public:
	string cell_number;
	int relays, call_length;
	double net_cost, tax_rate, call_tax, total_cost;
};

//function prototypes
void Input(call_record call[], int &);
void Process(call_record call_DB[], int & count);
void Output(const call_record call_DB[], const int & count);

int main() {
	//declare class array
	call_record call_DB[SIZE];

	//declaraion of count which will hold the number of items in the array
	int count = 0;

	//function calls
	Input(call_DB, count);
	Process(call_DB, count);
	Output(call_DB, count);

	return 0;
}

//function implementation

//function name: Input
//Precondition: The formal parameters have not been initialized
//Postcondition: The formal parameters have been initialized
//Description: Get input (values of cell_number, relays, and call_length) from the file "call_data.txt" and store into call_DB array.
void Input(call_record call_DB[], int & count) {
	int i;
	ifstream input;
	input.open("call_data.txt");
	if (input.fail()) {
		cout << "Input file did not open correctly." << endl;
	}
	else {
		//stores the values in the text file into the call_DB array
		for (i = 0; !input.eof();i++) {
				input >> call_DB[i].cell_number;
				input >> call_DB[i].relays;
				input >> call_DB[i].call_length;
				count ++;
		}
	}
	input.close();
}

//function name: Process
//Precondition: The net cost, tax rate, call tax, and total cost variables in call_DB[] have not been initialized
//Postcondition: The net cost, tax rate, call tax, and total cost variables in call_DB[] have been initialized
//Description: This function calculates the net cost, tax rate, call tax, and total cost variables and assigns them to to values in call_DB[]
void Process(call_record call_DB[], int & count) {
	int i;

	//determine tax rate
	for (i = 0; i < count; i++) {
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

//function name: Output
//Precondition: The formal parameter have not been printed onto the output file
//Postcondition: Formal parameter will be printed onto the output file
//Description: Print the values received from the input and the calculations into the output file
void Output(const call_record call_DB[], const int & count) {
	int i;
	ofstream output;
	output.open("weekly6_call_info.txt");
	
	//help format the output
	output.setf(ios::showpoint);
	output.precision(2);
	output.setf(ios::fixed);

	//in case the output file does not open correctly
	if (output.fail()) {
		cout << endl << "The output file did not open correctly.";
	}

	else {
		//prints each element in the array onto the output file
		for (i = 0; i < count; i++) {
			output << call_DB[i].cell_number << "\t" << call_DB[i].relays << "\t" << call_DB[i].call_length << "\t" << call_DB[i].net_cost << "\t";
			output << call_DB[i].tax_rate << "\t" << call_DB[i].call_tax << "\t" << call_DB[i].total_cost << endl;
		}
		//informs the user where to find the output file
		cout << "The weekly call info is in an output file called 'weekly6_call_info.txt'." << endl << endl;
		cout << "Check this program's directory" << endl << endl;
	}
	//closes output file
	output.close();
}

