/************************************************************************************************************************

Name: Jared Branscum                Z#: 23353586
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date: February 6, 2017                 Due Time: 11:59pm
Total Points: 10
Assignment 3: all_area_semi.cpp

Description: Include a void function call “Compute” that computes the area and perimeter of a
triangle based on the length of the sides. The function should use five parameters –
three call by value parameters (a, b, c) that provide the lengths of the edges and
two call by reference parameters (area, semiperimeter) that stores the computed
area and perimeter. Make the function is robust. The function “Compute” is called from the main program. I will print the computed area and
semiperimeter rounded to the nearest hundredths. In the main program, I will declare the
necessary variables, and include a while loop asking the user if he/she would like
to continue computing area and semiperimeters. 

*************************************************************************************************************************/

//preprocessor directives
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//function prototypes

void GetInput(double &, double &, double &);
void Compute(double, double, double, double &, double &);
void Output(double &, double &);

//Function Implementations

//*************************************************************************************

//Name: Input
//Precondition: The formal parameters have not been initialized
//Postcondition: The formal parameters have been initialized
//Description: Get input (values of the legs of the triangle) and store in variables.

void GetInput(double & a, double & b, double & c) {
	cout << "Please insert the length of the first leg of the triangle: ";
	cin >> a;

	cout << endl << "Please insert the length of the second leg of the triangle: ";
	cin >> b;

	cout << endl << "Please insert the length of the third leg of the triangle: ";
	cin >> c;

}

//Name: Compute
//Precondition: The call-by-reference parameters have not been initialized
//Postcondition: the call-by-reference parameters have been initialized
//Description:  Calculate the semiperimeter and the area of the triangle from the values of the legs of the triangle
//*************************************************************************************

void Compute(const double a, const double b, const double c, double &area, double &s) {
	s = (a + b + c) / 2;
	area = sqrt(s * (s - a) * (s - b) * (s - c));

}

//Name: Output
//Precondition: The formal parameters have not been printed onto the screen
//Postcondition: Formal parameters will be printed onto the screen
//Description: Display the values received from the input and the calculations
//*************************************************************************************
void Output(double & s, double & area) {
	//round to the nearest hundredth
	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	cout.precision(2);

	cout << endl << "The semiperimeter equals: " << s << " and the area equals: " << area << endl;
}

//program driver
int main() {
	//declare variables
	double a, b, c, area, s;
	string choice = "y";

	//while loop
	while (choice == "y" || choice == "Y") {

		//prompt the user for input
		GetInput(a, b, c);
		if (a + b > c) {
			Compute(a, b, c, area, s);
			Output(s, area);
		}

		//if invalid input
		else {
			cout << endl << "Invalid Input: Make sure the sum of the first two legs of the triangle" << endl;
			cout << "are greater than the length of the third leg." << endl << endl;
			cout <<"Try Again!" << endl << endl;
			GetInput(a, b, c);
			Output(s, area);
		}

		//repeat the loop?
		cout << endl << "Make another calculation?" << endl << endl;
		cin >> choice;
		if (choice == "y" || choice == "Y")
			cout << endl;
	}

	cout << endl << "Thank you for using this program! Farewell!" << endl << endl;
	return 0;
}