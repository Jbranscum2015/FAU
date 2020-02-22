
#include <iostream>
#include <string>

using namespace std;

int main() {
	char his_name[20] = "James";
	char her_name[20];

	her_name[0] = 'M';
	her_name[1] = 'a';
	her_name[2] = 'r';
	her_name[3] = 'y';

	cout << "his_name length equals " << strlen(his_name) << endl;
	cout << "his_name is " << his_name << endl;
	cout << endl << endl;

	cout << "her_name length equals " << strlen(her_name) << endl;
	cout << "her_name is " << her_name << endl;
	return 0;
}