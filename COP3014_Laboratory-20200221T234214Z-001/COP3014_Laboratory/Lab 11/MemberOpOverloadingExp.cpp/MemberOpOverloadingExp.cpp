#include <iostream>
#include <string>

using namespace std;

const int SIZE = 10;

class Bank_Acct
{
public:
	Bank_Acct();  //default constructor
	Bank_Acct(double new_balance, string Cname); //explicit value 										    
												 //constructor
	void Print(); //accessor function
	Bank_Acct & operator+(double amount); //mutator function

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

void Bank_Acct::Print()
{
	cout << endl << "Object " << name;
	cout << endl << "The new balance is " << balance << endl;
}

Bank_Acct & Bank_Acct::operator+(double amount)
{

	balance += amount;
	return *this;
}

int main()
{
	Bank_Acct my_Acct;

	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	cout.precision(2);

	cout << "Original balance of my_Acct" << endl;
	my_Acct.Print();

	//the following statement contains chaining
	my_Acct + 18.75 + 14.35 + 10054.96;

	cout << "The balance of my_Acct after addition to balance 3 times" << endl;
	my_Acct.Print();

	return 0;
}

