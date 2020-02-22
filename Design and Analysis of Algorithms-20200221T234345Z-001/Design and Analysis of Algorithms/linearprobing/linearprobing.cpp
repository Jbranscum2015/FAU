#include <iostream>
#include <functional>

using namespace std;

int main()
{
	int key = 73;
	int result;
	int inc = 1;

	result = key % 13;


	while (result > 0) {
			result = (result + inc) % 13;
			inc++;
		
	}

	cout << "The result is " << result << endl;
	return 0;
}