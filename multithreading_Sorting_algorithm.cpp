/*Multithreaded sorting program
A list of integers is divided into two smaller lists of equal size.
Two separate threads (which wewill term sorting threads) 
sort each sublist using a sorting algorithm. The two sublists are 
then merged by a third thread—a merging thread
—which merges the two sublists into a single sorted list.

To divide the array into 2 threads I will use work-sharing construct "sections"
in OpenMP
*/

#include < iostream>
#include < omp.h>

using namespace std; 

#define N 10

void printArray(int arr[], int start, int end) {
	for (int i = start; i < end; i++) {
		cout << arr[i] << "  ";
	}
	cout << endl;
}

void selectionSort(int arr[], int start, int end) {
	for (int i = start; i < end; i++) {
		int temp = arr[i];
		for (int j = start; j < end; j++) {
			if (temp < arr[j]) {
				temp = arr[j];
				arr[j] = arr[i];
				arr[i] = temp; 
			}
		}
	}
//	printArray(arr, start, end);
}

//merge sort at the end
int mergeSort(int *arr) {
	int mid = N / 2, i =0, j = mid, k =0;
	int *temp = NULL; 
	temp = new int[10];
	while (j < N && i < mid) { //for second part of array
		if (arr[i] > arr[j]) {
			temp[k] = arr[j];
			j++; k++;
			//cout << "arr[i]>arr[j] " << i << " " << j << endl;
		}
		else if (arr[i] < arr[j]) {
			temp[k] = arr[i];
			i++;  k++;
			//cout << "arr[i]<arr[j] " << i << " " << j << endl;
		}
	}
	if ((i == mid) && j <N) {
				for (j; j < N; j++) {
					temp[k] = arr[j];
					k++;
					//cout << "i == mid-1 && j <N-1 " << i << " " << j << endl;
				}
			}
	else if (i <mid  && j ==N) {
				for (i; i< mid; i++) {
					temp[k] = arr[i];
					k++;
					//cout << "i<mid-1 && j ==N-1 " << i << " " << j << endl;
				}
			}
		//}
		//cout << "I am in merge";
		printArray(temp, 0, N);
		arr = temp;
		printArray(arr, 0, N);
		return *temp;// sth wrong here...... how to reurn pointer object??
}

void main() {
	int *arr = NULL; 
	arr = new int[10]; 
	int myArr[]= { 7, 12, 19, 3, 18, 4, 2, 6, 15, 8 };
	arr = myArr;
	cout << "Unsorted Array: "; printArray(arr, 0, 10);

	//I want to use 2 threads one will sort first half of array next will 
	//sort second half of array to do it I am using sections
	omp_set_num_threads(2);
#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
				selectionSort(arr, 0, N / 2 );
			#pragma omp section
				selectionSort(arr, N / 2 , N);
		}
	}
	cout << "After partial sorting: "; printArray(arr, 0, N);
	//after section completes we will only use one thread
	*arr = mergeSort(arr);
	cout << "Sorted Array: "; printArray(arr, 0, N);

	system("pause");
}
