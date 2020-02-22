#include <iostream>
using namespace std;

class Bank_Acct
{
public:
	Bank_Acct();
	double Check_Balance();
	void Deposit(double);
	void Withdrawal(double);
private:
	double balance;
};




Bank_Acct::Bank_Acct()
{
	balance = 0;
}

double Bank_Acct::Check_Balance()
{
	return balance;
}

void Bank_Acct::Deposit(double amount)
{
	balance = balance + amount;
}

void Bank_Acct::Withdrawal(double amount)
{
	balance = balance - amount;
}

int main()
{
	Bank_Acct my_Acct;

	cout << "My Account Balance = " << my_Acct.Check_Balance() << endl;
	my_Acct.Deposit(2516.83);
	cout << "My Account Balance = " << my_Acct.Check_Balance() << endl;
	my_Acct.Withdrawal(25.96);
	cout << "My Account Balance = " << my_Acct.Check_Balance() << endl;
	return 0;
}
