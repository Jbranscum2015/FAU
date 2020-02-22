#include <string>
#include <iostream>

using namespace std;

class Person
{
protected:
	string firstName;
	string lastName;
public:
	Person(void)
	{
		cout << "In Person's constructor -- A Derived Class" << endl;
		cout << "Enter firstname: ";
		cin >> firstName;
		cout << "Enter lastname: ";
		cin >> lastName;
	}
	string getFirstName(void)
	{
		return firstName;
	}
	string getLastName(void)
	{
		return lastName;
	}
};

class Employee : public Person
{
protected:
	float salary;
public:
	Employee()
	{
		cout << "In Employee's constructor -- A Derived Class" << endl;
		cout << "Enter Salary: ";
		cin >> salary;
	}

	float getSalary(void)
	{
		return salary;
	}
};
int main(void)
{

	Employee Number_one; //calls Constructor of Person, then Constructor of employee
	Employee Number_two; //calls Constructor of Person, then Constructor of employee

	cout << endl << endl << endl;
	cout << "Retrieving Number_one's first name and last name from class Person\n";
	cout << "   " << Number_one.getFirstName() << " " << Number_one.getLastName() << endl;
	cout << "Retrieving Number_one's salary from class Employee\n";
	cout << "   " << Number_one.getSalary() << endl;


	cout << endl << endl << endl;
	cout << "Retrieving Number_two's first name and last name from class Person\n";
	cout << "   " << Number_two.getFirstName() << " " << Number_two.getLastName() << endl;
	cout << "Retrieving Number_two's salary from class Employee\n";
	cout << "   " << Number_two.getSalary() << endl;

	system("PAUSE");
	return 0;
}
