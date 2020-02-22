//Jared Branscum COP3014_Lab
//January 20, 2017
//Lab 1

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	bool response = 0;
	char character = 'A';
	int integer = 123.456789;
	float single_precision_number = 1234.567890123456789;
	double double_precision_number = 1234.567890123456789;

	cout << "response =  " << response << endl;
	cout << "character =  " << character << endl;
	cout << "integer =  " << integer << endl;
	cout << "single_precision_number =  " << setprecision(17) << single_precision_number << endl;
	cout << "double_precision_number =  " << setprecision(17) << double_precision_number << endl;

	return 0;
}