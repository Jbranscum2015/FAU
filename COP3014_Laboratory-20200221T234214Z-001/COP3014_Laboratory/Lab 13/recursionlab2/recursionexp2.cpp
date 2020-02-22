#include <iostream>
#include <string>
using namespace std;

int R_power(int count, const int & base)
{
	if (count == 0)
		return 1;
	else
		return base * R_power(count - 1, base);
}

int I_power(int count, const int & base)
{
	int multiend = 1;

	while (count > 0)
	{
		multiend *= base;
		count--;
	}
	return multiend;
}

void swap(string & original) {
	char temp;
	for (unsigned int i = 0; i < original.length()/2; i++) {
		temp = original[i];
		original[i] = original[original.length() - i-1];
		original[original.length() - i-1] = temp;
	}
}

string reverse(string & original)
{
	if (original.length() == 0)
		return "";

	string last(1, original[original.length() - 1]);
	string reversed = reverse(original.substr(0, original.length() - 1));
	return last + reversed;
}

int main()
{
	int count = 10;
	int base = 2;
	string test = "hello";
	//swap(test);
	test = reverse(test);
	cout << test;

	//cout << R_power(count, base) << endl;

	//cout << I_power(count, base) << endl;

	return 0;
}
