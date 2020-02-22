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

	virtual void CalculateAndPrintPayrollInformation(void)
	{
		cout << "This is Payroll Information for a Base Object" << endl;
		cout << "Gross Pay is 0" << endl;
		cout << "Income Tax is 0" << endl;
		cout << "Net Pay is 0" << endl << endl;
	}
};

class Employee : public Person
{
protected:
	float annual_salary;
	double gross_pay, hours_worked, hourly_rate, income_tax, net_pay;
public:
	Employee()
	{
		cout << "In Employee's constructor -- A Derived Class" << endl;
		cout << "Enter Annual Salary: ";
		cin >> annual_salary;


	}


	float getSalary(void)
	{
		return annual_salary;
	}

	void CalculateAndPrintPayrollInformation(void)
	{
		cout << "In Taxpayer's constructor -- A derived class of employe" << endl;
		cout << "Enter hours worked: ";
		cin >> hours_worked;
		cout << "Enter hourly rate: ";
		cin >> hourly_rate;
		gross_pay = hours_worked * hourly_rate;
		income_tax = gross_pay * 0.25;
		net_pay = gross_pay - income_tax;
		cout << "Gross Pay = " << gross_pay << endl;
		cout << "Income Tax  = " << income_tax << endl;
		cout << "Net Pay = " << net_pay << endl;
	}

};

int main(void)
{
	Employee John;
	Employee Mary;

	cout << endl << endl << endl;
	cout << "Enter John's information\n";
	cout << endl << John.getFirstName() << " " << John.getLastName() << endl;
	John.CalculateAndPrintPayrollInformation();

	cout << endl << endl << endl;
	cout << "Enter Mary's information\n";
	cout << endl << Mary.getFirstName() << " " << Mary.getLastName() << " salary is "
		<< Mary.getSalary() << endl;
	Mary.CalculateAndPrintPayrollInformation();

	system("PAUSE");
	return 0;
}
