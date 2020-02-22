#include <iostream>
#include <vector>

using namespace std;

void change(vector<int>& imagine) {
	imagine[0] = 9;

}


int main() {
	int yes = 5, maybe = 10;
	vector<int> oof = { yes, maybe };
	vector<int> imagine{ yes };
	cout << "test imagine: " << imagine[0] << endl;
	cout << "test oof: " << oof[0] << endl << endl;
	change(imagine);
	cout << "test imagine: " << imagine[0] << endl;
	cout << "test oof: " << oof[0] << endl << endl;

	return 0;
}