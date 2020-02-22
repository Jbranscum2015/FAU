/*
Name: Jared Branscum          Z#: 23353586
Course: Data Structures
Professor: Dr. Mehrad Nojoumian
Due Date: 11/01/17              Due Time: 11:59 P.M.
Total Points: 100
Assignment 2

Description: Selection Sort Algorithm: Prompts the user to enter how large of an array
they wish to sort, followed by the values the user wishes to be in the array. It will print the unsorted and
sorted array. The sorted array sorts from greatest to least.
*/
#include <iostream>
#include <vector>

using namespace std;

void SelectionSort(vector<int> &);


int main() {
	int size, x;
	vector<int> numarray, sortarray;

	cout << "How large of an array do you want to sort? ";
	cin >> size;
	cout << "Insert the numbers in your array (press enter after each number)" << endl;
	for (int i = 0; i < size; i++){
		numarray.push_back(x);
		cin >> numarray[i];
	}
	cout << endl;
	sortarray = numarray;
	cout << "Original Array: " << endl;
	for (unsigned int i = 0; i < numarray.size(); i++) {
		cout << numarray[i] << "\t";
	}
	SelectionSort(sortarray);
	cout << endl << endl << "Sorted Array: " << endl;
	for (int i = 0; i < size; i++) {
		cout << sortarray[i] << "\t";
	}
	return 0;
}

void SelectionSort(vector<int> & arr) {
	for (unsigned int i = 0; i < arr.size() - 1; i++) {
		int maxIndex = i;
		for (unsigned int j = i + 1; j < arr.size(); j++) {
			if (arr[j] > arr[maxIndex])
			{
				maxIndex = j;
			}
			int temp = arr[i];
			arr[i] = arr[maxIndex];
			arr[maxIndex] = temp;
		}
	}
}
