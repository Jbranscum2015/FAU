#include <iostream>
#include <string>

using namespace std;

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void swap(string &a, string &b)
{
	string temp = a;
	a = b;
	b = temp;
}

void swap(char &a, char&b)
{
	char temp = a;
	a = b;
	b = temp;
}

int main()
{
	string x = "first", y = "second";
	int m = 10, n = 20;
	char q = 'Q', r = 'R';

	cout << "x before swap called = " << x << " and y before swap called = " << y << endl;
	swap(x, y);
	cout << "x after swap called = " << x << " and y after swap called = " << y << endl << endl;

	cout << "m before swap called = " << m << " and n before swap called = " << n << endl;
	swap(m, n);
	cout << "m after swap called = " << m << " and n after swap called = " << n << endl << endl;

	cout << "q before swap called = " << q << " and r before swap called = " << r << endl;
	swap(q, r);
	cout << "q after swap called = " << q << " and r after swap called = " << r << endl << endl;

	return 0;
}
