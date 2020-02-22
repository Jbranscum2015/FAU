#include <iostream>
using namespace std;

int i = 111;

int main() {
	{
		int i = 222;
		{
			int i = 333;
			cout << "i = " << i << endl;
			{
				int i = 444;
				cout << "i = " << i << endl;
				{
					cout << "i = " << i << endl;
				}
			}
		}
		cout << "i = " << i << endl;
	}
	cout << "i = " << i << endl;
	return 0;
}

