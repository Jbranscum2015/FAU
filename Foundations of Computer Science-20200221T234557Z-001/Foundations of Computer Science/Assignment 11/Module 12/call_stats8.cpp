/*
Name: Jared Branscum          Z#: 23353586
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date: 4/17/17              Due Time: 11:59 P.M.
Total Points: 20
Assignment 10: call_stats8

Description: This assignment is an extension of Unit 11 Programming Assignment. I will
modify the implementation of “call_class”. The class will still manage a dynamic
array of call records. I will call this program "call_stats8.cpp". I will separate the
declaration and implementation for the class “call_class” into two separate files.
I will put the class declaration in the file called “call_class.h”, and put the class
implementation in the file called “call_class.cpp. The driver will be called
“call_stats8.cpp” which is provided. However, I will need to modify it to test the
functionality of the program. 
*/

//preprocessor directives
#include <iostream>
#include "call_class.h"
using namespace std;

//driver to test the functionality of your class.
int main()
{
	call_class MyClass;
	call_class YourClass = MyClass;
	char choice;
	string key;
	int num;
	do {
		//menu
		cout << "Please pick one of the following: " << endl << endl;
		cout << "Add an entry (A)" << endl << endl << "Remove an entry(R)" << endl << endl;
		cout << "Print the list(P)" << endl << endl << "Chain delete(C)" << endl << endl;
		cin >> choice;
		choice = toupper(choice);
		if (choice == 'A') {
			MyClass.add();
		}
		else if (choice == 'R') {
			cout << endl << "Please enter a phone number: ";
			cin >> key;
			cout << endl;
			MyClass - key;
		}
		else if (choice == 'P') {
			MyClass.process();
			cout << MyClass;
		}
		else if (choice == 'C') {
			cout << endl << "How many phone numbers do you want to delete? (Enter 2 or more)";
			cin >> num;
			string *temp = new string[num];
			cout << "Enter each number one at a time, press enter after each time" << endl << endl;
			for (int i = 0; i < num; i++) {
				cin >> temp[i];
			}
			//chaining occurs here
			MyClass - temp[0] - temp[1];
			for (int i = 2; i < num; i++) {
				MyClass - temp[i];
			}
			delete[] temp;
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


