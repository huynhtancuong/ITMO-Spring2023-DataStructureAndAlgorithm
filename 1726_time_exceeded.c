#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/**
 * O(N^2) algorithm
*/

typedef struct {
	int64_t x, y;
} Coordinate;

Coordinate coordinate[100000];

uint64_t f(size_t i, Coordinate coordinate[], size_t n) {
	if (i == n-1) return 0;
	uint64_t distance = 0; // distance from node i-th to (i+1)th, ... n-th node
	for (size_t j = i+1; j<n; j++) {
		distance += _abs64(coordinate[i].x - coordinate[j].x) + _abs64(coordinate[i].y - coordinate[j].y);
	}
	distance *=2;
	return distance;
} 

int main() {
	
	size_t n;
	scanf("%zu", &n);

	for (size_t i = 0; i<n; i++) {
		scanf("%" SCNd64 " %" SCNd64, &coordinate[i].x, &coordinate[i].y);
	}
	
	uint64_t total_distance = 0;

	for (size_t i = 0; i<n; i++) {
		total_distance += f(i, coordinate, n);
	}

	// printf("%" PRId64, total_distance);
	uint64_t averrage_distance = total_distance/(n*(n-1));
	printf("%" PRId64, averrage_distance);

	return 0;
}
