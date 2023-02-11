#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void setBit(int *bitMask, int k) {
    *bitMask|=(1<<k);
}

void unsetBit(int *bitMask, int k) {
    *bitMask&=~(1<<k);
}

void bitmask_setvalue(int *bitMask, int k, int value) {
    if (value != 0 && value != 1) return;
    if (value == 0) unsetBit(bitMask, k);
    if (value == 1) setBit(bitMask, k);
}

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

void permute(int bitMask, int n, int k, int a[], long int *min) {

    if (k == n) {
        // printBitMask(bitMask, n);
        int diff = getDifference(bitMask, n, a);
        if (*min > diff) *min = diff;
    }
    else {
        for (int i = 0; i<=1; i++) {
            bitmask_setvalue(&bitMask, k, i);
            permute(bitMask, n, k+1, a, min);
        }
    }

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
    
    permute(0, n, 0, arr, &min);

    printf("%ld", min);

    free(arr);
	return 0;
}
