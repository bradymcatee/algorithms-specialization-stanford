// C++ code to implement quicksort

#include <bits/stdc++.h>
#include <fstream>
using namespace std;
unsigned int comps = 0;
long long comps2 = 0;
const int ARRAY_SIZE = 10000;
// This function takes last element as pivot,
// places the pivot element at its correct position
// in sorted array, and places all smaller to left
// of pivot and all greater elements to right of pivot
int partition(int arr[], int low, int high)
{
	// Choosing the pivot
	comps += (high - low);
	int pivot = arr[low];
	// Index of smaller element and indicates
	// the right position of pivot found so far
	int i = (low + 1);

	for (int j = low+1; j <= high; j++) {
		comps2++;
		// If current element is smaller than the pivot
		if (arr[j] < pivot) {
			// Increment index of smaller element
			swap(arr[j], arr[i]);
            i++;
		}
	}
	swap(arr[low], arr[i-1]);
	return (i-1);
}

int partition_r(int arr[], int low, int high){
	int subarr[3] = {arr[low], arr[(high/2)], arr[high]};
	int size = 3;
	int swapIndex;

	for (int step = 0; step < size -1; step++){
		int min_idx = step;
		for (int i = step + 1; i < size; i++){
			if (subarr[i] < subarr[min_idx])
				min_idx = i;
		}
		swap(subarr[min_idx], subarr[step]);
	}
	if (subarr[1] == arr[low]){
		swapIndex = low;
	}
	else if(subarr[1] == arr[(high/2)]){
		swapIndex = (high / 2);
	}
	else {
		swapIndex = high;
	}

	swap(arr[low], arr[swapIndex]);

	return partition(arr, low, high);
}
// The main function that implements QuickSort
// arr[] --> Array to be sorted,
// low --> Starting index,
// high --> Ending index

void quickSort(int arr[], int low, int high)
{
	if (high == low){
		return;
	}


		// pi is partitioning index, arr[p]
		// is now at right place
		int pi = partition(arr, low, high);
		//int pi = choosePivot(arr, low, high);
		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		//comps += (pi - low);
		quickSort(arr, pi + 1, high);	
		//comps+= (high - pi);

	}


// Driver Code
int main()
{
	// int arr[] = {10, 2, 4, 8, 7, 1, 3, 5, 6, 9};
	// int N = sizeof(arr) / sizeof(arr[0]);
	int arr[ARRAY_SIZE];
	ifstream inFile;
	int index = 0;
	int number;

	inFile.open("QuickSortInts.txt");

	while (inFile >> number && index < ARRAY_SIZE){
		arr[index] = number;
		index++;
	}
	inFile.close();
	// Function call
	quickSort(arr, 0, (ARRAY_SIZE - 1));
	cout << "Sorted array: " << endl;
	for (int i = 0; i < ARRAY_SIZE; i++){
		cout << arr[i] << " ";
	}
	
	cout << "actual comps: " << comps2 << endl;
	cout << "comps " << comps << endl;
	return 0;
}
