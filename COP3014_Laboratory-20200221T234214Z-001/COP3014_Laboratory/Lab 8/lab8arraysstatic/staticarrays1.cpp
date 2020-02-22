#include <iostream>
#include <string>
using namespace std;

struct student_record {
	string name;
	double age;
	char sex;
};

int main() {
	student_record Student_DB[3] = { "Lofton",53,'M',"Thomas",55,'M',
		"Tami",25,'F' };

	cout << endl;

	for (int i = 0; i < 3; i++) {
		cout << Student_DB[i].name << " "
			<< Student_DB[i].age << " "
			<< Student_DB[i].sex << endl << endl;
	}

	Student_DB[0].name = "William";
	Student_DB[2].age = 100;
	Student_DB[1].sex = 'F';
	cout << "+++++++++++++++++++++++++++++++\n";

	cout << endl;

	for (int i = 0; i < 3; i++) {
		cout << Student_DB[i].name << " "
			<< Student_DB[i].age << " "
			<< Student_DB[i].sex << endl << endl;
	}
	return 0;

}