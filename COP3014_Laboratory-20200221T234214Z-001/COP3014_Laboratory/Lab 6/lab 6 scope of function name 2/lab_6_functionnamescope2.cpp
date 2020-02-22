#include <iostream>

using namespace std;

void Function_One() {
	cout << "You are in Function One" << endl;
	cout << "Function_One will call Function_Two" << endl << endl;
	Function_Two();

}

void Function_Two() {
	cout << "You are in Function_Two" << endl;
	cout << "Function_Two will call Function_Three" << endl << endl;
	Function_Three();

}

void Function_Three()
{
	cout << "You are in Function_Three" << endl;
	cout << "Function_Three calls no one" << endl << endl;
}

int main() {
	Function_Three();
	Function_Two();
	Function_One();

	return 0;
}