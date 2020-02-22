#include <iostream>
#include <string> 
using namespace std;

int main() {
	char s[] = "123";
	char r[] = "abc";
	char x[] = "124";
	char y[] = "abc";

	if (strcmp(r, y) == 0) {
		cout << "String " << r << " and string " << y << " are equal." << endl << endl;
	}

	if (strcmp(s, x) == -1) { 
		cout << "String " << s << " has a lower lexicographical " << "order than string " << x << "." << endl << endl; 
	}

	if (strcmp(x, s) == 1) { 
		cout << "String " << x << " has a higher lexicographical " << "order than string " << s << "." << endl << endl; 
	}

	return 0;
}