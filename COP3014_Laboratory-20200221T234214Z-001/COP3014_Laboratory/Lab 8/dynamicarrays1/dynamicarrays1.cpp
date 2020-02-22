#include <iostream>
using namespace std;

int main() {
	int static_Array[5];
	int *dynamic_Array = new int[5];

	int i;

	for (i = 0; i < 5; i++) {
		static_Array[i] = i;
		dynamic_Array[i] = i;
	}

	for (i = 0; i < 5; i++) {
		cout << "static_Array[" << i << "] = " << static_Array[i] << endl;
		cout << "dynamic_Array[" << i << "] = " << dynamic_Array[i] << endl;
	}
	return 0;
}