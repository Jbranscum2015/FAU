//
/************************************************************************************************************************
Name: Jared Branscum          Z#: 23353586
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date: 1/23/17              Due Time: 11:59 P.M.
Total Points: 20
Assignment 2: call_info

Description:
In this assignment, a program a call management system is implemented.  The program uses three functions:
input, output, and process.  The function input gets input from the user, the function process performs
the necessary calculations, and the function output prints the results.
*************************************************************************************************************************/

#include <iostream>
#include <string>
using namespace std;

//Prototypes for your functions: Input, Output, and Process will go here

void Input(string & cell_number, int & relays, int & call_length);
void Output(const string cell_number, const int relays, const int call_length, const double & net_cost, const double & call_tax, const double & total_cost_of_call);
void Process(const int relays, const int call_length, double & net_cost, double & call_tax, double & total_cost_of_call);

//Function Implementations will go here

///*************************************************************************************
//Name:  Input
//Precondition: The variables (formal parameters) have not been initialized
//Postcondition: The variables (formal parameters) have been initialized
//Description: Get input (values of cell_number, relays, and call_length) from the user.

//PURPOSE: SHOW ME THAT YOU KNOW HOW TO READ INPUT AND USE INPUT (CALL BY VALUE) & OUTPUT (CALL BY VALUE) PARAMETERS
//FORMAL PARAMETERS ARE: cell_number (string), relays (integer), call_length (integer)
//*************************************************************************************
void Input(string & cell_number, int & relays, int & call_length) // example of all formal parameter using the call by reference mechanism in C++
{
	cout << endl << "Enter your Cell Phone Number: ";
	cin >> cell_number;
	cout << endl << "Enter the number of relay stations: ";
	cin >> relays;
	cout << endl << "Enter the length of the call in minutes: ";
	cin >> call_length;
}

///*************************************************************************************
//Name: Output
//Precondition: The calculations have been initialized
//Postcondition: The input and the results will be printed onto the screen
//Description: Print the input and the results onto the screen
//*************************************************************************************

//NOTE: ALL FORMAL PARAMETERS ARE BEING PASSED BY VALUE. ALSO WE USED CONST TO MAKE SURE THEY WOULD NOT BE CHANGED BY MISTAKE
//USE THE SAMPLE OUTPUT TO HELP YOU FORMAT YOUR OUTPUT
void Output(const string cell_number, const int relays, const int call_length, const double & net_cost, const double & call_tax, const double & total_cost_of_call)
{
	//Use these following statement to help you format your output. These statements are called the magic formula.
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout.setf(ios::fixed);
	/********************************************/

	cout << endl << endl << "Cell Phone: " << cell_number << endl << endl;
	cout << "Number of Relay Stations: " << relays << endl << endl;
	cout << "Minutes Used: " << call_length << endl << endl;
	cout << "Net Cost: " << net_cost << endl << endl;
	cout << "Call Tax: " << call_tax << endl << endl;
	cout << "Total Cost " << total_cost_of_call << endl << endl;
}

///*************************************************************************************
//Name:  Process
//Precondition: The net_cost, call_tax, and the total_cost_of_call have not been initialized
//Postcondition: The three output parameters will be initialized
//Description: This function calculates the net cost, the call tax, and the total cost of the call by using the three input parameters and the tax rate,
//which is determined by the number of relays
//*************************************************************************************

//Note: there are 3 input parameter and 3 output parameters
void Process(const int relays, const int call_length, double & net_cost, double & call_tax, double & total_cost_of_call)
{
	//declare tax rate variable
	double tax_rate;
	//determine tax rate
	if (relays >= 1 && relays <= 5)
		tax_rate = 0.01;
	else if (relays >= 6 && relays <= 11)
		tax_rate = 0.03;
	else if (relays >= 12 && relays <= 20)
		tax_rate = 0.05;
	else if (relays >= 21 && relays <= 50)
		tax_rate = 0.08;
	else {
		tax_rate = 0.12;
	}

	//calculate net cost
	net_cost = relays / 50.0 * 0.40 * call_length;

	//calculate call tax
	call_tax = net_cost * tax_rate;

	//calculate total cost
	total_cost_of_call = net_cost + call_tax;
}

//Here is your driver to test the program
int main()
{
	string cell_number, repeat;
	int relays;
	int call_length;
	double net_cost;
	double call_tax;
	double total_cost_of_call;

	cout << "Welcome User!" << endl << endl;
	cout << "Would you like to make a calculation for an employee? (y or n): ";
	cin >> repeat;

	while (repeat == "y" || repeat == "Y") {
		Input(cell_number, relays, call_length);
		Process(relays, call_length, net_cost, call_tax, total_cost_of_call);
		Output(cell_number, relays, call_length, net_cost, call_tax, total_cost_of_call);
		cout << "Would you like to make a calculation for an employee? (y or n): ";
		cin >> repeat;

	}
	cout << endl << "Have a good day!" << endl << endl;
	return 0;
}
