#ifndef max_Heapify_h
#define max_Heapify_h

#include "heap_node.h"
using namespace std;

//transforms the heap into a max heap where it swaps the node with the largest value between the parent node and the child nodes and calls itself recursively until the node with the largest index is equal to the node passed into the function
void maxHeapify(vector<int> & heap, int heapsize, int node) {
	int leftChildindex = left(node);
	int rightChildindex = right(node);
	int indexoflargest;

	//if left child is larger than the node then it's the largest, else the node is larger
	if (leftChildindex < heapsize && heap[leftChildindex] > heap[node]) {
		indexoflargest = leftChildindex;
	}
	else {
		indexoflargest = node;
	}

	//if right child is larger than the left child and node, then it becomes the largest
	if (rightChildindex < heapsize && heap[rightChildindex] > heap[indexoflargest]) {
		indexoflargest = rightChildindex;
	}

	if (indexoflargest != node) {
		swap(node, indexoflargest, heap);
		maxHeapify(heap, heapsize, indexoflargest);
	}
}


#endif max_Heapify_h /* max_Heapify_h*/