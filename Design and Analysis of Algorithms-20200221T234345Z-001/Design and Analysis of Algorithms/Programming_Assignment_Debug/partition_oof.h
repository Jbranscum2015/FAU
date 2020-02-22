#ifndef partition_h
#define partition_h
#include <vector>
using namespace std;

//returns the index of the pivot
int partition(vector<int> & elements, int left, int right) {
	int i = left, j = right;
	int temp;
	int pivot = elements[(left + right) / 2];
	while (i <= j) {
		while (elements[i] < pivot) {
			i++;
		}
		while (elements[j] > pivot) {
			j--;
		}
		if (i <= j) {
			temp = elements[i];
			elements[i] = elements[j];
			elements[j] = temp;
			i++;
			j--;
		}
	}
	return i;
}


#endif /* partition_h*/