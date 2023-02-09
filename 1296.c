#include <stdio.h>
#include <stdlib.h>


int maxSubArraySum(int a[], int size) {
    int max_so_far = 0;
    int max_ending_here = 0;

    for (int i = 0; i<size; i++) {
        max_ending_here += a[i];
        if (max_so_far < max_ending_here) max_so_far = max_ending_here;
        if (max_ending_here < 0) max_ending_here=0;
    }

    return max_so_far;
}


int main() {
	int n;
    scanf("%d", &n);
    int *arr;
    arr = malloc(n*sizeof(int));
    for (int i = 0; i< n; i++) {
        scanf("%d", &arr[i]);
    }
    int max = maxSubArraySum(arr, n);

    printf("%d", max);

    free(arr);
	return 0;
}
