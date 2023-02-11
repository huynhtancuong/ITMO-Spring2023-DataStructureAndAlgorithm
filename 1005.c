#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long int getDifference(int bitMask, int n, int a[]) {
    long int first_pile = 0, second_pile = 0;
    for (int i = 0; i<n; i++) {
        if (bitMask&(1<<i)) {
            first_pile += a[i];
        } else {
            second_pile += a[i];
        }
    }
    return abs(first_pile-second_pile);
}


void printBitMask(int bitMask, int size) {
    int bit;
    for (int i = 0; i<size; i++) {
        bit = bitMask & (1<<i);
        if (bit) bit = 1;
        printf("%d", bit);
    }
    printf("\n");
}



int main() {
	int n;
    scanf("%d", &n);
    int *arr;
    arr = malloc(n*sizeof(int));
    for (int i = 0; i< n; i++) {
        scanf("%d", &arr[i]);
    }
    
    long int min = 100000000;
	int size = pow(2, n);
    
    for (int bitMask = 0; bitMask < size; bitMask++) {
		long int diff = getDifference(bitMask, n, arr);
		if (min > diff) min = diff;
		if (min == 0) break;
	}

    printf("%ld", min);

    free(arr);
	return 0;
}
