#include <stdio.h>
#include <stdlib.h>


typedef struct {
        int index;
        int amount;
} Sign;



void bubblesort(Sign arr[], size_t n) {
        int i, j;
        for (i = 0; i < n-1; i++)
        // Last i elements are already in place
                for (j = 0; j < n-i-1; j++)
                        if (arr[j].amount < arr[j+1].amount) {
                                Sign tmp = arr[j];
                                arr[j] = arr[j+1];
                                arr[j+1] = tmp;
                        }
}

Sign sign[10000];

int main() {
        int n;
        scanf("%d", &n);

        // Sign *sign = malloc(n*sizeof(Sign));

        for (int i = 0; i<n; i++) {
                scanf("%d", &sign[i].amount);
                sign[i].index = i+1;
        }

        bubblesort(sign, n);

        while (sign[0].amount > 0) {
                if (sign[1].amount > 0) {
                        printf("%d %d ", sign[0].index, sign[1].index);
                        sign[0].amount--;
                        sign[1].amount--;
                        if (sign[1].amount == 0) bubblesort(sign, n);
                } else {
                        printf("%d ", sign[0].index);
                        sign[0].amount--;
                }
        }


        return 0;
}