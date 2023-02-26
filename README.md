<p align="center" style ="font-size: 24px">Министерство образования и науки РФ
</p>
<p align="center" style ="font-size: 20px">Федеральное государственное автономное <br>
образовательное учреждение высшего образования <br>
«Национальный исследовательский университет ИТМО»
</p>

<p align="center" style ="font-size: 24px"><em>Факультет систем управления и робототехники </em></p>

<p align="center">
  <img src="doc/Picture1.png" />
</p>

<p align="center" style ="font-size: 24px"><strong>Лабораторные работы</br>
По дисциплине : «Алгоритмы и структуры данных»</br>
</strong>
</p>
<p align="left">Преподаватель: <strong>Тропченко Андрей Александрович</strong></br>
Выполнил: <strong>Хюинь Тан Куонг</strong></br>
Группа: <strong>R32362</strong>
</p>

# Алгоритмы и структуры данных

## 4. Problem 1207: Median on the Plane



```c
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

```
This is a C program that takes as input a number of points on a 2D plane, and then finds a line that divides the points into two sets of equal size, if such a line exists.

The program starts by defining two struct types: "point" and "line". A "point" has two members, x and y, representing the coordinates of a point on the plane. A "line" has three members, a, b, and c, which represent the coefficients of the equation for a line in the form ax + by + c = 0.

The program then defines three functions:

get_line: This function takes two points as input and returns the line that passes through those two points, by computing the coefficients of the equation for the line.

line_point_distance: This function takes a line and a point as input, and returns the signed distance from the point to the line.

is_equal_sets: This function takes an array of points, the number of points, and a line as input, and returns true if the line divides the points into two sets of equal size. It does this by counting the number of points on each side of the line, and returning true if those counts are equal.

The main function of the program starts by reading in the number of points from the user, and allocating memory for an array of that many points. It then reads in the x and y coordinates for each point from the user.

Next, the program iterates over all pairs of points, computes the line that passes through those two points using the get_line function, and checks whether that line divides the points into two sets of equal size using the is_equal_sets function. If such a line is found, the program prints the indices of the two points that define that line, and then exits.

If no such line is found, the program exits without printing anything.





