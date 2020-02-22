#ifndef partition_h
#define partition_h
using namespace std;

//returns the index of the pivot
int partition(vector<int> & elements, int left, int right) {
	int i = left, j = right;
	int temp;
	//creates the pivot
	int pivot = elements[(left + right) / 2];

	//finds the two indexes of the values that need to be swapped
	while (i <= j) {
		while (elements[i] < pivot) {
			i++;
		}
		while (elements[j] > pivot) {
			j--;
		}

		//swaps the two values if they're not sorted properly in respect to the pivot
		if (i <= j) {
			temp = elements[i];
			elements[i] = elements[j];
			elements[j] = temp;
			i++;
			j--;
		}
	}
	//returns the index of the partition
	return i;
}


#endif /* partition_h*/