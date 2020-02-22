/************************************************************************************************************************
Name: Jared Branscum          Z#: 23353586
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date: 2/13/17              Due Time: 11:59 P.M.
Total Points: 10
Assignment 5: call_stats3

Description:
This assignment is an extension of Assignment#2. I will implement a
program called "call_stats3.cpp" to process customer call records. Each
customer call record contains seven fields, which are as follows: 1) a ten digit
cell phone number (string, no dashes), 2) the number of relay stations used in
making the call (integer), 3) the length of the call in minutes (integer), 4) the net
cost of the call (double), 5) the tax rate (double), 6) the call tax (double) and 7)
the total cost of the call (double). This program will have 3 functions: Input,
Process and Output. The main program will call each function until the end of
the datafile has been read. Each call record will be printed to a data file.
*************************************************************************************************************************/

//preprocessor directives
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//class record
class call_record {
public:
	string cell_number;
	int relays, call_length;
	double net_cost, tax_rate, call_tax, total_cost;
};

//function prototypes

void Input(ifstream &, call_record &);
void Process(call_record &);
void Output(ofstream &, const call_record &);


int main() {
	//declare call record
	call_record customer_record;

	//declare input and output file stream
	ifstream in;
	ofstream out;

	//read file
	in.open("call_data.txt");
	out.open("weekly_call_info.txt");

	if (in.fail()) {
		cout << "Input file did not open correctly." << endl;
	}
	else {
		cout << "The weekly call info is in an output file called 'weekly_call_info.txt'." << endl << endl;
		cout << "Check this program's directory" << endl << endl;

		while (!in.eof()) {
			Input(in, customer_record);
			Process(customer_record);
			Output(out, customer_record);
		}
	}
	in.close();
	out.close();
	return 0;
}

//function implementations

//function name: Input
//Precondition: The formal parameters have not been initialized
//Postcondition: The formal parameters have been initialized
//Description: Get input (values of cell_number, relays, and call_length) from the file "call_data.txt" and store in call record.
void Input(ifstream & input, call_record & customer_record) {
	input >> customer_record.cell_number;
	input >> customer_record.relays;
	input >> customer_record.call_length;
}

//function name: Process
//Precondition: The net cost, tax rate, call tax, and total cost variables in customer_record have not been initialized
//Postcondition: The net cost, tax rate, call tax, and total cost variables in customer_record have been initialized
//Description: This function calculates the net cost, tax rate, call tax, and total cost variables and assigns them to to values in customer_record
void Process(call_record & customer_record) {
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

//function name: Output
//Precondition: The formal parameter have not been printed onto the output file
//Postcondition: Formal parameter will be printed onto the output file
//Description: Print the values received from the input and the calculations into the output file
void Output(ofstream & output, const call_record & customer_record) {
	//help format the output
	output.setf(ios::showpoint);
	output.precision(2);
	output.setf(ios::fixed);

	output << customer_record.cell_number << "\t";
	output << customer_record.relays << "\t";
	output << customer_record.call_length << "\t";
	output << customer_record.net_cost << "\t";
	output << customer_record.tax_rate << "\t";
	output << customer_record.call_tax << "\t";
	output << customer_record.total_cost << endl;
}