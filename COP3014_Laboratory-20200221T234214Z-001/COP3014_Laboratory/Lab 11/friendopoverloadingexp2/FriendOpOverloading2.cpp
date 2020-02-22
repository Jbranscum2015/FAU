#include <iostream>
#include <string>

using namespace std;

const int SIZE = 10;

class Bank_Acct
{
public:
	Bank_Acct();  //default constructor
	Bank_Acct(double new_balance, string Cname); //explicit value 	//constructor overloading operator<< as a friend function with chaining

	friend void operator<<(ostream & output, Bank_Acct & Org);
private:
	double balance;
	string name;
};

Bank_Acct::Bank_Acct()
{
	balance = 0;
	name = "NoName";
}

Bank_Acct::Bank_Acct(double amount, string Cname)
{
	balance = amount;
	name = Cname;

}

void operator<<(ostream & output, Bank_Acct & Org)
{
	output << endl << "Object " << Org.name;
	output << endl << "The new balance is " << Org.balance << endl;

}

int main()
{
	Bank_Acct my_Acct;

	Bank_Acct DrB(2000.87, "Dr. Bullard");

	//the following statement does not contain chaining
	cout << DrB;
	cout << endl;
	cout << my_Acct;
	cout << endl;

	return 0;
}
