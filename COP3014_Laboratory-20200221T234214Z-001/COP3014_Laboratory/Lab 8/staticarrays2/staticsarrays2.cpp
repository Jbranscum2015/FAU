#include <iostream>
#include <string>

using namespace std;

struct student_record {
	string name;
	double age;
	char sex;
};


int main() {
	student_record *Student_DB = new student_record[3];
	Student_DB[0].name = "Lofton"; 
	Student_DB[0].age = 53;
	Student_DB[0].sex = 'M';

	Student_DB[1].name = "Thomas";
	Student_DB[1].age = 55;
	Student_DB[1].sex = 'M';

	Student_DB[2].name = "Tami";
	Student_DB[2].age = 25;
	Student_DB[2].sex = 'F';

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
	delete[] Student_DB;
	return 0;
}