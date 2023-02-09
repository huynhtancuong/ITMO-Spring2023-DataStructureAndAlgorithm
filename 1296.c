#include <stdio.h>
#include <stdlib.h>


int main() {
	int n;
    scanf("%d", &n);
    int *arr;
    arr = malloc(n*sizeof(int));
    for (int i = 0; i< n; i++) {
        scanf("%d", &arr[i]);
    }
    int max = 0;
    for (int size = 1 ; size <= n; size++) {
        for (int start = 0; start <= n-size; start++) {
            int sum = 0;
            for (int index = start; index < start+size; index++) {
                sum+=arr[index];
            }
            // printf("sum= %d\n", sum);
            if (max < sum) {
                max = sum;
            }
        }
    }

    printf("%d", max);

    free(arr);
	return 0;
}
