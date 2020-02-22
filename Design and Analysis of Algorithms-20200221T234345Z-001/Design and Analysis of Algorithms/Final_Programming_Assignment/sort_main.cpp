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
The simulation finds the average performance from 5 trials where there are n randomly generated numbers. 
The simulation finds the average performance where n starts at 1000 and is incremented by a thousand till 
the simulation measures performance where n = 50,000. Throughout this program, vectors may be referred to as arrays
because this simulation can be modified to simulate a constant n array of values, so vectors are used to handle
the dynamic simulation where n changes.
*************************************************************************************************************************/

//preprocessor directives
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include "heap_node.h"
#include "max_Heapify.h"
#include "build_maxHeap.h"
#include "partition.h"
#include <fstream>
#include <iomanip>

using namespace std;

//function prototypes
//
vector<int> Insertion_Sort(vector<int> elements);
//
vector<int> Heap_sort(vector<int> elements, int heapsize);
//
void Quick_sort(vector<int> & elements, int left, int right);


int main() {
	//changes the time such that each time you start this program, it will generate different pseudo random numbers
	//srand(static_cast<unsigned int>(time(NULL))); // optional, but important towards generating more "random" random numbers
	
	//declared ofstream to output the results to a text file
	ofstream cut("simulation_results.txt"); //outputting results to a textfile is more readable and easier to analyze the set of data
	
	//vectors are used to store the data of the randomly generated numbers as the data set grows to a size of n
	vector<int> elements;
	vector<int> sorted;

	//for this simulation, we will be generating 1000 random numbers and incrementing that by 1000 up to 50000 random numbers;
	int n_random = 50000;
	//declaration of clock which will be used to record time
	clock_t clocks;
	
	//declaration & initialization of the arrays used to record performance time
	double time_insertion_sort[5];
	double time_heap_sort[5];
	double time_quick_sort[5];
	double avg_time_insertion_sort[50];
	double avg_time_heap_sort[50];
	double avg_time_quick_sort[50];


	//this for loop loops through the increment of n random numbers, such that the simulations are iterated where n = i random numbers
	for (int i = 1000; i <= n_random; i += 1000) {
		//h counts index of average performance time array for each sort
		int h = 0;

		//cout << "n = " << i << endl;  //can be used to track the progress of the program for debugging purposes

		//for loop interates over the five trials ran for size n and stores the performance time of the sorting algorithms in the time_sort arrays
		for (int j = 0; j < 5; j++) {

			//for loop generates i random numbers where i = n
			for (int k = 1; k <= i; k += 1) {
				elements.push_back(rand());
			}

			//calculates time to insertion sort
			clocks = clock();
			sorted = Insertion_Sort(elements);
			clocks = clock() - clocks;
			time_insertion_sort[j] = (double)clocks * 1000 / (double)CLOCKS_PER_SEC; //calculates time in milliseconds and stores in time_sort array
			//cut << endl << "j equals " << j << " " << "The time is " << time_insertion_sort[j] << endl; This is for debugging purposes and be used to verify average time

			//calculates time to heap sort
			clocks = clock();
			sorted = Heap_sort(elements, elements.size());
			clocks = clock() - clocks;
			time_heap_sort[j] = (double)clocks * 1000 / (double)CLOCKS_PER_SEC; //calculates time in milliseconds and stores in time_sort array
			//cut << endl << "j equals " << j << " " << "The time is " << time_heap_sort[j] << endl; This is for debugging purposes and be used to verify average time

			//calculates time to quick sort
			clocks = clock();
			Quick_sort(elements, 0, elements.size() - 1);
			clocks = clock() - clocks;
			time_quick_sort[j] = (double)clocks * 1000 / (double)CLOCKS_PER_SEC; //calculates time in milliseconds and stores in time_sort array
			//cut << endl << "i equals " << j << " " << "The time is " << time_quick_sort[j] << endl; This is for debugging purposes and be used to verify average time

			elements.clear(); //empties the vector of all the elements inside it so it can be reused in the next iteration of the simulation
		}

		//calculates the average time of the sorting algorithms where i = n
		avg_time_insertion_sort[h] = (time_insertion_sort[0] + time_insertion_sort[1] + time_insertion_sort[2] + time_insertion_sort[3] + time_insertion_sort[4]) / 5;
		cut << endl << "The average insertion sort time where n = " << i << " equals: " << avg_time_insertion_sort[h];

		avg_time_heap_sort[h] = (time_heap_sort[0] + time_heap_sort[1] + time_heap_sort[2] + time_heap_sort[3] + time_heap_sort[4]) / 5;
		cut << endl << "The average heap sort time where n = " << i << " equals: " << avg_time_heap_sort[h];

		avg_time_quick_sort[h] = (time_quick_sort[0] + time_quick_sort[1] + time_quick_sort[2] + time_quick_sort[3] + time_quick_sort[4]) / 5;
		cut << endl << "The average quick sort time where n = " << i << " equals: " << avg_time_quick_sort[h];
	}


	//closes output filestream
	cut.close();
	return 0;
}

/************************************************************************************************************************************/
//Name: Insertion_Sort
//Precondition: array is unsorted
//Postcondition: array is sorted with insertion sort
//Description: Insertion Sorts functions very similiarly to selection sort where an element is selected as the starting key of the sorted subarray.
//After this, the element is shifted to the left until the element to the left is no longer greater than the key. This becomes the first sorted element in the sorted subarray.
//Next, the next element is labeled as the key and the process is repeated where it is properly placed into the sorted subarray.
/************************************************************************************************************************************/
vector<int> Insertion_Sort(vector<int> elements) {
	int current, temp;

	for (int i = 1; i < (signed)elements.size(); i++) {
		current = elements[i];
		for (int j = i - 1; j >= 0; j--) {
			if (elements[j] > current) { //if the element is greater than the current key, then the key is swapped with the element to its left until the element to its left
										//is either equal to or less than the current key, so it is placed in the proper position in the sorted subarray
				temp = elements[j];
				elements[j] = current;
				elements[j+1] = temp; //element[j+1] represents an right element to a sorted subarray element
			}
		}
	}
	return elements; //returns the sorted subarray
}

/************************************************************************************************************************************/
//Name: Heap_sort
//Precondition: array is unsorted
//Postcondition: array is sorted with heap sort
//Description: Heap sort uses the nature of heaps to its advantage. The height of a heap will always be logn and a max heap will have the largest element at the root node.
//Similarly, a min heap will have the smallest element at the root node
//Using these three facts, it is possible to retrieve elements from a max heap to sort an unsorted array of numbers.
//In order to heap sort, a max heap is used, so the sort will be in descending order.
//After the max heap is made, the root node is placed into the sorted array, then the root node is swapped with the last node in the heap.
//The last node in the heap is removed, then the heap is maxHeapifyed, so that it becomes a max heap.
//This process is repeated until there's only one node left in the heap and that node is then put into the sorted array.
/************************************************************************************************************************************/
vector<int> Heap_sort(vector<int> elements, int heapsize) {
	vector<int> sorted;
	buildMaxHeap(elements, elements.size());
	for (int i = 0; i < heapsize - 1; i++) {
		sorted.push_back(elements[0]);
		swap(0, elements.size() - 1, elements);
		elements.pop_back();
		maxHeapify(elements, elements.size(), 0);
	}
	sorted.push_back(elements[0]);
	return sorted;
}

/************************************************************************************************************************************/
//Name: Quick_sort
//Precondition: array is unsorted
//Postcondition: array is sorted with quick sort
//Description: Quick sort uses partitioning to sort the array. The quick sort algorithm recursively sorts the sub partitions, and returns the sorted partitions, resulting in a sorted array.
//First, a pivot element is determined where the elements on the left and right of the array are compared to the pivot. 
//Whenever a value to the left of the pivot is greater than or equal to the pivot, it is swapped with the element to the right of the pivot that is smaller than the pivot.
//After the swap occurs, the left element becomes the new pivot. The function recursively partitions the array into multiple subarrays where the pivots points are considered sorted.
//This recursive process becomes completed untill all of the elements are pivots that have been successfully sorted.
/************************************************************************************************************************************/
void Quick_sort(vector<int> & elements, int left, int right) {
	int index = partition(elements, left, right);
	if (left < index - 1) {
		Quick_sort(elements, left, index - 1);
	}
	if (index < right) {
		Quick_sort(elements, index, right);
	}
}