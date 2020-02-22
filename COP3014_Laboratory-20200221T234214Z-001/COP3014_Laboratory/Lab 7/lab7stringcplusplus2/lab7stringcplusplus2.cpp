#include <iostream>
#include <string>
using namespace std;

int main() {
	string my_name = "Thomas Jefferson";
	string her_name("Michelle Obama");
	string his_name = "Joe Biden";

	for (int i = 0; i < her_name.length(); i++) {
		cout << her_name[i];
	}
	cout << endl << endl;

	if (my_name == "Thomas Jefferson") {
		cout << "my_name is equal to Thomas Jefferson"
			<< endl << endl;
	}

	if (my_name > her_name) {
		cout << my_name << " is lexicographically greater than "
			<< her_name << endl << endl;
	}

	if (my_name < his_name) {
		cout << my_name << " is lexicographically less than "
			<< his_name << endl << endl;
	}

	if (my_name >= her_name) {
		cout << my_name << " is lexicographically greater than or equal to "
			<< her_name << endl << endl;
	}

	if (my_name <= his_name) {
		cout << my_name << " is lexicographically less than or equal to "
			<< his_name << endl << endl;
	}

	return 0;
}