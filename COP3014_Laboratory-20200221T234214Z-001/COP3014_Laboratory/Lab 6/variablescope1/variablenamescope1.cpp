#include <iostream>
using namespace std;

void Function_One();
void Function_Two();
void Function_Three(int);

int i = 100;



void Function_Two() {
	int i = 555;
	cout << "i in Function_Two = " << i << endl;
}

void Function_Three(int i) {
	cout << "i in Function_Three = " << i << endl;
}

int main() {
	int i = 777;
	Function_Three(666);
	Function_Two();
	Function_One();
	cout << "i in main = " << i << endl;
	return 0;
}

void Function_One() {
	cout << "i in Function_One = " << i << endl;
}