/*
Name: Jared Branscum          Z#: 23353586
Course: Data Structures
Professor: Dr. Mehrad Nojoumian
Due Date: 11/01/17              Due Time: 11:59 P.M.
Total Points: 100
Assignment 2

Description: BinaryK implements Modular Exponentiation (ME) using the square and multiply
approach as a function which is called in main. ME calculates a^k mod n. The program gets values
for a, k and n from the user. This code requires two steps. First k is converted to a binary
representation K consisting of a list of 0s and 1s. Second, Modular Exponentiation is performed
using a, n and K[] as arguments
*/

#include <iostream>
#include <vector>
using namespace std;

vector <int> BinaryK(int);
int ModularExpo(int, int, int);

int main() {
	int result, a, k, n;
	cout << "Enter your value for a: ";
	cin >> a;
	cout << "Enter your value for k: ";
	cin >> k;
	cout << "Enter your value for n: ";
	cin >> n;

	result = ModularExpo(a, k, n);
	cout << endl << "The result of a^k mod n is " << result << endl;

	return 0;
}

vector <int> BinaryK(int k) {
	vector<int> K;
	int tmp = k;
	int i = 0;
	while (tmp > 0) {
		K.push_back(tmp % 2);
			tmp = (tmp - K[i]) / 2;
			i++;
	}
	return K;
}

int ModularExpo(int a, int k, int n) {
	vector<int> K;
	K = BinaryK(k);
	if (n == 1) {
		return 0;
	}
	int b = 1;
	if (k == 0) {
		return b;
	}
	int A = a;
	if (K[0] == 1) {
		b = a;
	}
	for (unsigned int i = 1; i <= K.size() - 1; i++) {
		A = (A*A) % n;
		if (K[i] == 1)
			b = (A*b) % n;
	}
	return b;
}
