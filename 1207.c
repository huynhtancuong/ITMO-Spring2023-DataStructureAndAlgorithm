#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>

struct line
{
	// line: ax + by + c = 0
	int64_t a, b, c;
};

struct point
{
	// point: (x, y)
	int64_t x, y;
};


struct line get_line(struct point p1, struct point p2) {
	struct line d;
	d.a = p1.y - p2.y;
	d.b = p2.x - p1.x;
	d.c = p1.x*p2.y - p2.x*p1.y;
	return d;
}

float line_point_distance(struct line d, struct point M) {
	// float dis = (d.a*M.x + d.b*M.y + d.c)/(sqrt(d.a*d.a + d.b*d.b));
	float dis = (d.a*M.x + d.b*M.y + d.c);
	return dis;
}

int is_equal_sets(struct point p[], size_t size, struct line d) {
	int positive_counter = 0;
	int negative_counter = 0;
	for (size_t i = 0; i<size; i++) {
		if (line_point_distance(d, p[i]) > 0) positive_counter++;
		if (line_point_distance(d, p[i]) < 0) negative_counter++;
		// bypass distance == 0
	}

	return positive_counter == negative_counter;
}



int main() {

	int N;
	scanf("%d", &N);

	struct point *points;
	
	points = (struct point *) malloc(sizeof(struct point)*N);

	for (size_t i = 0; i<N; i++) {
		scanf("%" SCNd64 " %" SCNd64, &points[i].x, &points[i].y);
	}

	for (size_t i = 0; i<N; i++) {
		for (size_t j=i+1; j<N; j++) {
			struct line d = get_line(points[i], points[j]);
			if (is_equal_sets(points, N, d)) {
				printf("%d %d", i+1, j+1);
				return 0;
			}
		}
	}

	return 0;
}
