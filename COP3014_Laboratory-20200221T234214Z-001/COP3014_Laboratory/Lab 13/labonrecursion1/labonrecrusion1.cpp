#include <iostream>
using namespace std;

void recursive_countdown(int count)
{
	if (count == 0)
		cout << "count=" << count << endl;
	else
	{
		cout << "count=" << count << endl;
		recursive_countdown(--count);
	}
}

void interative_countdown(int count)
{
	for (count; count >= 0; count--) {
		cout << "count= " << count << endl;
	}
}


int main(void)
{
	int count = 10;

	//recursive_countdown(count);
	interative_countdown(count);

	return 0;
}
