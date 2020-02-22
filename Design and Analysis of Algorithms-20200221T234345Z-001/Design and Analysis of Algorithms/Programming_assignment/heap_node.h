#ifndef heap_node_h
#define heap_node_h
using namespace std;

//returns index of left child node of current node in a heap
int left(int node) {
	return ((2 * node) + 1);
}

//returns index of right child node of current node in a heap
int right(int node) {
	return (2 * (node + 1));
}

//swaps two nodes in the heap
void swap(int i, int j, vector<int> & heap) {
	int temp = heap[i];
	heap[i] = heap[j];
	heap[j] = temp;
}

#endif /* heap_node_h*/