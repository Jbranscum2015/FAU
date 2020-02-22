#include <iostream>
#include <string>
using namespace std;

int main() {
	string my_name = "Thomas Jefferson";
	string her_name("Michelle Obama");
	string his_name = my_name;

	cout << "my_name = " << my_name << endl;
	cout << "The length of my_name is " << my_name.length() << endl;
	cout << "The size of my_name is " << sizeof(my_name) << endl << endl;

	cout << "her_name = " << her_name << endl;
	cout << "The length of her_name is " << her_name.length() << endl;
	cout << "The size of her_name is " << sizeof(her_name) << endl << endl;

	his_name = "Barack Obama";
	cout << "his_name = " << his_name << endl;
	cout << "The length of his_name is " << his_name.length() << endl;
	cout << "The size of his_name is " << sizeof(his_name) << endl << endl;

	string their_name;

	their_name = my_name + " " + her_name
		+ " " + his_name + " " + my_name + " ";
	cout << "their_name = " << their_name << endl;
	cout << "The length of their_name is " << their_name.length() << endl;
	cout << "The size of their_name is " << sizeof(their_name) << endl;

	return 0;

}