#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define maxN 30001

typedef struct point {
	int x, y;
	int id;
} point_s;

int n;
point_s points[maxN];

void transform_to_new_coord() {
	// transform to new coordinates
	for (int i = 1; i<n; i++) {
		points[i].x = points[i].x - points[0].x;
		points[i].y = points[i].y - points[0].y;
	}
	points[0].x = 0;
	points[0].y = 0;
}

void print_points_debug() {
	// print the points
	printf("Printing points...\n");
	for (int i = 0; i<n; i++) {
		printf("%d %d %d\n", points[i].id, points[i].x, points[i].y);
	}
}

void print_points() {
	// print the points
	for (int i = 0; i<n; i++) {
		printf("%d\n", points[i].id);
	}
}

int cmp_angle(float a, float b) {
	// compare two angles
	float eps = 1e-8;
	return (a - b > eps) - (a - b < -eps);
}

int cmp(const void *a, const void *b) {
	// compare two points
	point_s *a1 = (point_s *)a;
	point_s *b1 = (point_s *)b;
	if (cmp_angle(atan2(a1->y, a1->x), atan2(b1->y, b1->x)) == 0) {
		if (a1->x == b1->x) {
			if (a1->y == b1->y) {
				return 0;
			}
			else {
				return a1->y < b1->y;
			}
		}
		else {
			return a1->x < b1->x;
		}
	}
	else {
		return cmp_angle(atan2(a1->y, a1->x), atan2(b1->y, b1->x));
	}
}

int main() {

	// read the input 
	scanf("%d", &n);
	for (int i = 0; i<n; i++) {
		scanf("%d %d", &points[i].x, &points[i].y);
		points[i].id = i+1;
	}

	transform_to_new_coord();
	// print_points();
	qsort(&points[1], n-1, sizeof(point_s), cmp);
	// print_points();

	printf("%d\n", n);
	print_points();


	return 0;
}
