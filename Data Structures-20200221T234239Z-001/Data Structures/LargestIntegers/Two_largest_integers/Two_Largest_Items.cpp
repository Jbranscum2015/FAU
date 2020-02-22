/*
Name: Jared Branscum          Z#: 23353586
Course: Data Structures
Professor: Dr. Mehrad Nojoumian
Due Date: 11/01/17              Due Time: 11:59 P.M.
Total Points: 100
Assignment 2

Description: Two_Largest asks the user to enter a list of numbers of any size and it finds the two largest elements
*/
#include <iostream>
#include <vector>
using namespace std;

void Two_Largest(vector<int>);

int main() {
	int size;
	vector<int> list;
	

	cout << "Welcome to the Two_Largest_Items program!" << endl;
	cout << "How many elements would you like to add to your list? ";
	cin >> size;
	list.resize(size);

	cout << endl << "Insert your elements one at a time: " << endl;
	for (int i = 0; i < size; i++) {
		cin >> list[i];
	}
	
	Two_Largest(list);

	return 0;
}

void Two_Largest(vector<int> list) {
	int large_1 = 0;
	int large_2 = 0;
	for (unsigned int i = 0; i < list.size(); i++) {
		if (list[i] > large_1) {
			large_2 = large_1 + 1;
			large_1 = list[i];
		}
		else if (large_2 < list[i]) {
			large_2 = list[i];
		}
				}
	cout << endl << "The largest element is " << large_1 << endl;
	cout << "The second largest element is " << large_2 << endl;
}