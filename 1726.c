#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/**
 * O(nlogn + n) algorithm
*/

int cmp(const void* a, const void* b) {
	return *((int*)a) - *((int*)b);
}

int64_t X[100000], Y[100000];

int main() {
	
	size_t n;
	scanf("%zu", &n);

	for (size_t i = 0; i<n; i++) {
		scanf("%" SCNd64 " %" SCNd64, &X[i], &Y[i]);
	}

	qsort(X, n, sizeof(int64_t), cmp);
	qsort(Y, n, sizeof(int64_t), cmp);
	
	int64_t total_distance = 0;

	for (size_t i = 0; i<n-1; i++) {
		total_distance += (X[i+1]-X[i])*(i+1)*(n-i-1)*2;
		total_distance += (Y[i+1]-Y[i])*(i+1)*(n-i-1)*2;
	}
	

	// printf("%" PRId64, total_distance);
	int64_t averrage_distance = total_distance/(n*(n-1));
	printf("%" PRId64, averrage_distance);

	return 0;
}
