#include <stdio.h>



void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void printArray(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void BuildMaxHeap(int arr[], int n) {
	for (int i = n / 2; i >= 0; i--) {
		maxHeapify(arr, n, i);
	}
}

void maxHeapify(int arr[], int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if ((left < n) && (arr[left] > arr[i])) 
		largest = left;
	else	
		largest = i;
	
	if ( (right < n) && (arr[right] > arr[largest])) 
		largest = right;

	if (largest != i) {
		swap(&arr[largest], &arr[i]);
		maxHeapify(arr, n, largest);
	}

}

void Heapsort(int arr[], int n) {
	BuildMaxHeap(arr, n);
	for (int i = n-1; i>=0; i--) {
		swap(&arr[0], &arr[i]);
		n--;
		maxHeapify(arr, n, 0);
	}
}

int main() {
	int arr[] = {10, 20, 30, 40, 50};
	int n = sizeof(arr) / sizeof(arr[0]);
	
	printArray(arr, n);

	BuildMaxHeap(arr, n);

	printArray(arr, n);

	Heapsort(arr, n);

	printArray(arr, n);
	
	return 0;
}
