#include <stdio.h>
#include <math.h>

size_t n;
int map[512][512];
int k = 3;

void fill_map(int map[][512], size_t n, int num) {
	size_t size = pow(2, n);
	for (size_t r=0; r<size; r++) {
		for (size_t c=0; c<size; c++) {
			map[r][c] = num;
		}
	}
}

void print_map() {
	int size = pow(2, n);
	for (int r=0; r<size; r++) {
		for (int c=0; c<size; c++) {
			printf("%2d ", map[r][c]);

		}
		printf("\n");
	}
	printf("\n");
}

/**
 * It fills a 2x2 square with numbers, except for the hole. 
 * 
 * If square is not the hole, then we fill the square with a number.
 * We use i, j for interate for each square in the 2x2 square.
 * 
 * @param x the x coordinate of the top left corner of the square
 * @param y the y coordinate of the top left corner of the square
 * @param hx the x coordinate of the hole
 * @param hy the y coordinate of the hole
 */
void fill_square_size_2(int x, int y, int hx, int hy) {
	// we can check if the hole is not in this square, then do nothing
	// but I don't :) 
	for (int i=0; i<2; i++) {
		for (int j=0; j<2; j++) {
			int is_the_hole = ((x+i == hx) && (y+j == hy));
			if (!is_the_hole) { // if not the hole, then fill
				map[x+i][y+j] = k++/3;
			}
		}
	}
	// print_map();
}

/**
 * > The function recursively fills the square with size n, with the hole at (hx, hy), by filling the
 * middle triangle, and recursively filling the 3 blocks not containing the hole
 * 
 * @param n the size of the square
 * @param x the x coordinate of the top left corner of the square
 * @param y the y coordinate of the top left corner of the square
 * @param hx the x coordinate of the hole
 * @param hy the y coordinate of the hole
 * 
 * @return the number of ways to fill a square of size n with a hole at (hx, hy).
 */
void solve(int n, int x, int y, int hx, int hy) {

/* The simplest case. If the size of the square is 2, then we just fill the square with numbers, except
for the hole. */
	if (n == 2) {
		fill_square_size_2(x, y, hx, hy); // simplest case
		return;
	}

/* It finds the block that contains the hole. */
	// let's find the (hi, hj) where the hole is 
	int hi, hj;
	for (int i=0; i<2; i++) {
		for (int j=0; j<2; j++) {
			if ((x+i*n/2 <= hx) && (hx <x+(i+1)*n/2) && (y+j*n/2 <= hy) && (hy < y+(j+1)*n/2))
				hi = i, hj = j;
		}
	}

	/* It fills the middle triangle with numbers, except for the hole. */
	int triangle_x = x + n/2-1, triangle_y = y + n/2-1;
	fill_square_size_2(triangle_x, triangle_y, triangle_x + hi, triangle_y + hj);

	/* Recursively filling the 3 blocks not contain the hole. */
	for (int i=0; i<2; i++) {
		for (int j=0; j<2; j++) {
			if (!(i==hi && j==hj)) {// if not the block contain the hole
				solve(n/2, x+i*n/2, y+j*n/2, x + n/2 - 1 + i, y + n/2 - 1 + j);
			}
			else {
				solve(n/2, x+i*n/2, y+j*n/2, hx, hy);
			}
		}
	}

}


int main() {
	
	

	scanf("%zu", &n);

	int hx, hy; // hole x, hole y

	scanf("%d %d", &hx, &hy);
	hx--;
	hy--;

	// fill_map(map, n, 0); // fill the entire map with 0

	// print_map();

	int size = pow(2, n);

	solve(size, 0, 0, hx, hy);



	print_map(map, n);


	return 0;
}
