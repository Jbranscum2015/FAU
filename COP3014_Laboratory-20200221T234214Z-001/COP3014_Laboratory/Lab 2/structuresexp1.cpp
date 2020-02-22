#include <iostream> 
#include <string>

using namespace std;



int main() {

	struct student_record {
		string firstname, lastname;
		double age, income;
		int number_of_children;
		char sex;
	};
	student_record Mary;
	student_record Susan;

	cout << "Enter the firstname and lastname: ";
	cin >> Mary.firstname;
	cin >> Mary.lastname;
	cout << "Enter age: ";
	cin >> Mary.age;
	cout << "Enter income: ";
	cin >> Mary.income;
	cout << "Enter number of children: ";
	cin >> Mary.number_of_children;
	cout << "Enter sex: ";
	cin >> Mary.sex;

	Susan = Mary;

	if (Susan = Mary) {
		cout << Susan.firstname << "    " << Mary.lastname << endl;
		cout << Susan.age << endl;
		cout << Susan.income << endl;
		cout << Susan.number_of_children << endl;
		cout << Susan.sex << endl;
	}
	
	//cout << Mary.firstname << "    " << Mary.lastname << endl;
	//cout << Mary.age << endl;
	//cout << Mary.income << endl;
	//cout << Mary.number_of_children << endl;
	//cout << Mary.sex << endl;

	return 0;
}