#include <iostream>
using namespace std;

int main() {
	int i;
	int *p;
	int &temp = i;

	cout << &i << endl;
	cout << p << endl;
	cout << &temp << endl << endl;

	i = 90;
	p = &i;

	cout << i << endl;
	cout << (*p) << endl;
	cout << temp << endl;


	return 0;
}