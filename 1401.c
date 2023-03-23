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

void fill_square_size_2(int x, int y, int hx, int hy) {
	// we can check if the hole is not in this square, then do nothing
	// but I don't :) 
	for (int i=0; i<2; i++) {
		for (int j=0; j<2; j++) {
			if (!((x+i == hx) && (y+j == hy))) { // if not the hole, then fill
				map[x+i][y+j] = k++/3;
			}
		}
	}
	// print_map();
}

void solve(int n, int x, int y, int hx, int hy) {
	if (n == 2) {
		fill_square_size_2(x, y, hx, hy); // simplest case
		return;
	}

	// let's find the (hi, hj) where the hole is 
	int hi, hj;
	for (int i=0; i<2; i++) {
		for (int j=0; j<2; j++) {
			if ((x+i*n/2 <= hx) && (hx <x+(i+1)*n/2) && (y+j*n/2 <= hy) && (hy < y+(j+1)*n/2))
				hi = i, hj = j;
		}
	}

	// fill the middle triagle 
	int triangle_x = x + n/2-1, triangle_y = y + n/2-1;
	fill_square_size_2(triangle_x, triangle_y, triangle_x + hi, triangle_y + hj);

	// recursively fill the 3 blocks not contain the hole
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
