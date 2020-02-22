#ifndef extract_maximum_h
#define extract_maximum_h

#include "heap_node.h"
#include "max_Heapify.h"
#include <iostream>
using namespace std;

void extract_maximum (int heap[], int heapsize) {
	if (heapsize < 1) {
		cout << endl << endl << "The Heap is empty";
	}
	heap[0] = heap[heapsize - 1];
	heapsize --;
	maxHeapify(heap, heapsize, 0);
}

#endif /* extract_maximum_h*/