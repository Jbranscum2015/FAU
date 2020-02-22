#include <iostream>
using namespace std;

void Function_One() {
	cout << "You are in Function One" << endl;
	cout << "Function_One called no one" << endl << endl;
}

void Function_Two() {
	cout << "You are in Function_Two" << endl;
	cout << "Function_Two will call Function_One" << endl << endl;
	Function_One();
}

void Function_Three() {
	cout << "You are in Function_Three" << endl;
	cout << "Function_Three will call Function_Two" << endl << endl;
	Function_Two();
}

int main() {
	int x = 5;
	Function_Three();
	Function_Two();
	Function_One();

	return 0;
}