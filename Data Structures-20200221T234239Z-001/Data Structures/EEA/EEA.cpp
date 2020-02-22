/*
Name: Jared Branscum          Z#: 23353586
Course: Data Structures
Professor: Dr. Mehrad Nojoumian
Due Date: 11/01/17              Due Time: 11:59 P.M.
Total Points: 100
Assignment 2

Description: Extended Euclidean Algorithm: asks for and
gets two integers, then computes and displays their greatest common divisor using the Extended Euclidian
Algorithm (EEA)
*/

#include <iostream>
#include <cstdlib>

using namespace std;

struct st {
public:
	int gcd, s, t;
};

st ExtendedEuclideanAlgorithm(int, int, st);
int main(){
	st EEA = { 0, 0 };
	int a, b;
	cout << "Welcome to the EEA Program!" << endl << "Please insert an integer: ";
	cin >> a;
	cout << "Please insert another integer: ";
	cin >> b;
	if (a < b) {
		int temp = a;
		a = b;
		b = temp;
	}
	EEA = ExtendedEuclideanAlgorithm(a, b, EEA);
	cout << "GCD= " << EEA.gcd << endl;
	cout << "S = " << EEA.s << endl;
	cout << "T = " << EEA.t << endl;
	cout << "Therefore," << endl;
	cout << EEA.gcd << " = " << a << " * " << EEA.s << " +  " << b << " * " << EEA.t << endl;
	return 0;
}

st ExtendedEuclideanAlgorithm(int a, int b, st result) {
	int quo;
	result.s = 0;
	int old_s = 1;
	int temp_s;

	int temp_t;
	result.t = 1;
	int old_t = 0;
	                         
	int rem = b; //198
	int old_rem = a; //252 

	while (rem != 0) {
		quo = old_rem / rem;
		rem = old_rem % rem;
		old_rem = b;
		b = rem;
		

		temp_s = result.s;
		result.s = old_s - (quo * result.s);
		old_s = temp_s;

		temp_t = result.t;
		result.t = old_t - (quo * result.t);
		old_t = temp_t;

	}
	result.gcd = old_rem;
	result.s = old_s;
	result.t = old_t;
	return result;
}