#ifndef build_maxHeap_h
#define build_maxHeap_h

#include "max_Heapify.h"
using namespace std;

//builds the max heap by first calling maxHeapify at the parent node of the last node in the heap, then it decrements where maxHeapify is called up to where maxHeapify is called at the root node.
void buildMaxHeap(vector<int> & heap, int heapsize) {
	for (int i = (heapsize / 2) - 1; i >= 0; i--) {
		maxHeapify(heap, heapsize, i);
	}
}

#endif max_Heapify_h /* build_maxHeap_h*/