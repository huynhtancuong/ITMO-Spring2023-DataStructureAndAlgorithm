#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/// @brief This function return the different betweent two piles of stone. If the bit from bitMask is 1, the stone will be added to the first pile. And the second pile for the bit 0.
/// @param bitMask bitMask
/// @param n size of bitMask
/// @param a array of stones
/// @return long int different between 2 piles
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


/// @brief This function print the bit by bit in the bitMask. Just for debugging
/// @param bitMask bitMask
/// @param size size of bitMask
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

    // Input n and array

	int n;
    scanf("%d", &n);
    int *arr;
    arr = malloc(n*sizeof(int));
    for (int i = 0; i< n; i++) {
        scanf("%d", &arr[i]);
    }
    
    long int min = 100000000; // set the min to a big int value
	int size = pow(2, n); // n bit represent the value of 2^n
    
    // find the minimum value of different between 2 piles
    for (int bitMask = 0; bitMask < size; bitMask++) {
		long int diff = getDifference(bitMask, n, arr);
		if (min > diff) min = diff;
		if (min == 0) break;
	}

    // Print the output
    printf("%ld", min);

    // Free the array
    free(arr);
	return 0;
}
