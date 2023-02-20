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
	int32_t x, y;
};

struct answer
{
	size_t p1, p2;
};


struct line get_line(struct point p1, struct point p2) {
	struct line d;
	d.a = p1.y - p2.y;
	d.b = p2.x - p1.x;
	d.c = p1.x*p2.y - p2.x*p1.y;
	return d;
}

float line_point_distance(struct line d, struct point M) {
	float dis = (d.a*M.x + d.b*M.y + d.c)/(sqrt(d.a*d.a + d.b*d.b));
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

size_t find_P(struct point ps[], size_t size, struct line d) {
	size_t min_index;
	float min_value = 10000000;
	for (size_t i = 0; i<size; i++) {
		float dis = line_point_distance(d, ps[i]);
		if (dis < 0) dis = -dis;
		if ((dis < min_value) && (dis > 0)) {
			min_index = i;
			min_value = dis;
		}
	}
	return min_index;
}

struct answer find(size_t p1, size_t p2, struct point ps[], size_t size) {
	struct line d = get_line(ps[p1], ps[p2]);
	size_t p_index = find_P(ps, size, d);
	struct line d1 = get_line(ps[p_index], ps[p1]);
	struct line d2 = get_line(ps[p_index], ps[p2]);
	if (is_equal_sets(ps, size, d1)) return (struct answer) {.p1=p_index, .p2=p1};
	if (is_equal_sets(ps, size, d2)) return (struct answer) {.p1=p_index, .p2=p2};
	return find(p1, p_index, ps, size);
}


int main() {

	int N;
	scanf("%d", &N);

	struct point *points;
	
	points = (struct point *) malloc(sizeof(struct point)*N);

	for (size_t i = 0; i<N; i++) {
		scanf("%" SCNd32 " %" SCNd32, &points[i].x, &points[i].y);
	}

	struct point p1 = (struct point) {.x = 0, .y = 0};
	struct point p2 = (struct point) {.x = 1, .y = 1};

	struct line d = get_line(p1, p2);

	// printf("%d", is_equal_sets(points, N, d));

	// printf("P=%d", find_P(points, N, d));

	struct answer ans;

	ans = find(0, 1, points, N);

	printf("%d %d", ans.p1 + 1, ans.p2 + 1);

	// for (int i = 0; i< N; i++) {
	// 	printf("%f\n", line_point_distance(d, points[i]));
	// }

	// printf("line d : %.2fx +  %.2fy + %.2f = 0\n", d.a, d.b, d.c);

	// struct point p3 = (struct point) {.x = -1, .y = 0};

	// float distance = line_point_distance(d, p3);

	// printf("distance = %f", distance);

	return 0;
}
