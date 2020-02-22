/*
Jared Branscum	        Total Points:  10
Due Date:  1/23/17 Due Time: 11:30pm
Course:  C0P3014
Assignment:  Assignment 1
Professor: Dr. Lofton Bullard

Description: (The program calculates the net cost of a call, the tax on the call, and the total cost of the call from the information provided: 
the cellphone number, the number of relay stations, and the length in minutes of the call from the user)
*/
#include <iostream> //standard library for i/o
#include <string>

using namespace std;

//function prototype
//Uses the number of relays to determine tax rate and returns the tax rate
int DetermineTaxRate(int x);

int main()
{
	//declared variables and initialization
	string cell_num; //user provided
	int relays, call_length; //user provided
	int tax_rate; //determined by number of relays provided by the user
	double net_cost, call_tax, total_cost; //what the program calculates
	string user_response = "y";

	//round to nearest hundredth
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	//greeting
	cout << "Welcome User!" << endl << endl;

	while (user_response == "y" || user_response == "Y")
	{
		//The code to get the user's input, perform the calculations, and print
		// the results to the screen should go here. 

		//get the cell number
		cout << "Please insert cell number: ";
		cin >> cell_num;

		//get the number of relay stations
		cout << "\nPlease insert the number of relay stations: ";
		cin >> relays;

		//get the call length
		cout << endl <<"Please insert the length of the call (in minutes): ";
		cin >> call_length;

		//calculate the net cost of the call
		net_cost = (relays / 50.0 * 0.40 * (double)call_length);

		//Uses the number of relays to determine tax rate and returns the tax rate
		tax_rate = DetermineTaxRate(relays);

		//calculate call tax
		call_tax = net_cost * tax_rate / 100;

		//calculate total cost
		total_cost = net_cost + call_tax;

		//print the results
		cout << endl << "Cell Phone: " << cell_num << endl;
		cout << "Number of Relay Stations: " << relays << endl;
		cout << "Minutes Used: " << call_length << endl;
		cout << "Net Cost: " << net_cost << endl;
		cout << "Call Tax: " << call_tax << endl;
		cout << "Total Cost of Call: " << total_cost << endl;

		//repeat the loop?
		cout << endl << "Would you like to do another calculation (y or n): ";
		cin >> user_response;
		cout << endl;
	}

	return  0;
}

//Uses the number of relays to determine tax rate and returns the tax rate
int DetermineTaxRate(int relays) {
	//determine the tax rate
	if (relays >= 1 && relays <= 5)
		return 1;
	else if (relays >= 6 && relays <= 11)
		return 3;
	else if (relays >= 12 && relays <= 20)
		return 5;
	else if (relays >= 21 && relays <= 50)
		return 8;
	else {
		return 12;
	}
}