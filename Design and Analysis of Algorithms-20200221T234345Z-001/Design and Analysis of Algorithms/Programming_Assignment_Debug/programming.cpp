/************************************************************************************************************************

Name: Jared Branscum                Z#: 23353586
Course: Design & Analysis of Algorithms (COT 4400)
Professor: Dr. Saeed Rajput
Due Date: November 14, 2018                 Due Time: 11:59pm
Total Points: 100
Programming Assignment: sort_main.cpp, heap_node.h, maxHeapify.h, build_maxHeap.h, and partition.h (required files)

Description: In this assignment, I implement three different sorting algorithms (insetion-sort, heap-sort, and quicksort) and compare their performance for doing the same job by real observations.
I determine how well these algorithms actually perform compared to their theoretical performances.
This program calculates the real world observations and the theoretical performances are calculated separately.
I use simulated data (using a random number generator).
The simulation finds the average performance from 5 trials of
*************************************************************************************************************************/

//preprocessor directives
#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>

#include <fstream>
#include "partition_oof.h"

using namespace std;
//
vector<int> Insertion_Sort(vector<int> elements);

//
vector<int> Quick_sort(vector<int> elements, int left, int right);


int main() {
	//changes the time such that each time you start this program, it will generate different pseudo random numbers
	//srand(static_cast<unsigned int>(time(NULL)));
	ofstream cut("oofdebug.txt");

	//vectors are used to store the data of the randomly generated numbers as the data set grows to a size of n
	vector<int> elements;
	vector<int> sorted;


	int n_random = 10000, h = 0;
	clock_t clocks;
	double time_insertion_sort[5];
	double time_quick_sort[5];
	double avg_time_insertion_sort[50];
	double avg_time_quick_sort[50];
	cut << endl << CLOCKS_PER_SEC << endl;
	for (int i = 1000; i <= n_random; i += 1000) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < i; k++) {
				elements.push_back(rand());
			}
			clocks = clock();
			sorted = Insertion_Sort(elements);
			clocks = clock() - clocks;
			cut << "Insert completed where n = "<< i <<  ": " << (double)clocks << " clocks" << endl;
			time_insertion_sort[j] = (double)clocks / (CLOCKS_PER_SEC / 1000);

			clocks = clock();
			sorted = Quick_sort(elements, 0, elements.size() - 1);
			clocks = clock() - clocks;
			cut << "Quick completed where n = " << i << ": " << (double)clocks << " clocks" << endl << endl;
			time_quick_sort[j] = (double)clocks / (CLOCKS_PER_SEC / 1000);

			elements.clear();
		}
		avg_time_insertion_sort[h] = (time_insertion_sort[0] + time_insertion_sort[1] + time_insertion_sort[2] + time_insertion_sort[3] + time_insertion_sort[4]) / 5;
		avg_time_quick_sort[h] = (time_quick_sort[0] + time_quick_sort[1] + time_quick_sort[2] + time_quick_sort[3] + time_quick_sort[4]) / 5;
		h++;
	}
	cut << clock() << endl << endl;
	for (int i = 0; i < h; i++) {
		cut << "Average time (ms) for insertion sort when n = " << 1000 + (i * 1000) << " is " << avg_time_insertion_sort[i] << endl << endl;
		cut << "Average time (ms) for quick sort when n = " << 1000 + (i * 1000) << " is " << avg_time_quick_sort[i] << endl << endl;
	}

	//sorted = Insertion_Sort(elements);
	//sorted = Heap_sort(elements, elements.size());
	//sorted = Quick_sort(elements, 0, elements.size() - 1);


	//cut << endl;
	cut.close();
	return 0;
}

vector<int> Insertion_Sort(vector<int> elements) {
	int current, temp;

	for (int i = 0; i < (signed)elements.size(); i++) {
		current = elements[i];
		for (int j = i - 1; j >= 0; j--) {
			if (elements[j] > current) {
				temp = elements[j];
				elements[j] = current;
				elements[j + 1] = temp;
			}
		}
	}
	return elements;
}


vector<int> Quick_sort(vector<int> elements, int left, int right) {
	if (elements.size() == 0) {
		elements.push_back(0);
	}
	int index = partition(elements, left, right);
	if (left < index - 1) {
		elements = Quick_sort(elements, left, index - 1);
	}
	if (index < right) {
		elements = Quick_sort(elements, index, right);
	}
	return elements;
}