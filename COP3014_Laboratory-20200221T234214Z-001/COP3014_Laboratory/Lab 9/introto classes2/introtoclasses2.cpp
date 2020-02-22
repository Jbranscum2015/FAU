#include <iostream>

using namespace std;

class Bank_Transaction
{
public:
	Bank_Transaction();  //default constructor
	Bank_Transaction(double);
	double Check_Balance();
	void Deposit(double);
	void Withdrawal(double);
private:
	double balance;
};


Bank_Transaction::Bank_Transaction()
{
	balance = 0;
}

Bank_Transaction::Bank_Transaction(double amount)
{

	balance = amount;
}


double Bank_Transaction::Check_Balance()
{
	return balance;
}

void Bank_Transaction::Deposit(double amount)
{
	balance = balance + amount;
}

void Bank_Transaction::Withdrawal(double amount)
{
	balance = balance - amount;
}

int main()
{
	Bank_Transaction my_Acct;
	Bank_Transaction your_Acct(10340.85);
	my_Acct.balance = 0;

	cout << "Your Account Balance = " << your_Acct.Check_Balance() << endl;
	your_Acct.Deposit(512.30);
	cout << "Your Account Balance = " << your_Acct.Check_Balance() << endl;
	your_Acct.Withdrawal(8284.56);
	cout << "Your Account Balance = " << your_Acct.Check_Balance() << endl;


	cout << "My Account Balance = " << my_Acct.Check_Balance() << endl;
	my_Acct.Deposit(2516.83);
	cout << "My Account Balance = " << my_Acct.Check_Balance() << endl;
	my_Acct.Withdrawal(25.96);
	cout << "My Account Balance = " << my_Acct.Check_Balance() << endl;

	return 0;
}

