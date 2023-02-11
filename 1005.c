#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int getDifference(int arr[], int size, int bitMask) {
	int pile1 = 0;
	int pile2 = 0;
	for (int i = 0; i < size; i++) {
		if (bitMask&(1<<i)) {
			pile1 += arr[i];
		}
		else {
			pile2 += arr[i];
		}
	}
	return pile1 - pile2;
}

int main() {
	int n;
    scanf("%d", &n);
    int *arr;
    arr = malloc(n*sizeof(int));
    for (int i = 0; i< n; i++) {
        scanf("%d", &arr[i]);
    }

	int bitMask = 7;

	printf("%d", getDifference(arr, n, bitMask));

	return 0;
}
