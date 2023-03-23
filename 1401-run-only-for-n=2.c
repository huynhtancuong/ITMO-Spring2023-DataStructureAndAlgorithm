#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define COLUMN 512

int x_0, y_0;


void fill_map(int map[][COLUMN], size_t n, int num) {
	size_t size = pow(2, n);
	for (size_t r=0; r<size; r++) {
		for (size_t c=0; c<size; c++) {
			map[r][c] = num;
		}
	}
}

void print_map(int map[][COLUMN], size_t n) {
	map[x_0][y_0] = 0;
	int size = pow(2, n);
	for (int r=0; r<size; r++) {
		for (int c=0; c<size; c++) {
			// if (r == x_0 && c == y_0) 	
			// 	printf("%2d ", 0);
			// else 	
				printf("%2d ", map[r][c]);

		}
		printf("\n");
	}
}

int is_in_map(int x, int y, size_t n) {
	if ( (x<0) || (y<0) ) return 0;
	if ( (x > pow(2,n)-1) || (y > pow(2,n)-1)) return 0;
	return 1;
}

int is_free(int map[][COLUMN], int x, int y, int state) {
	if (map[x][y]) return 0;
	switch (state)
	{
	case 1:
		return !(map[x-1][y] || map[x-1][y-1]);
		break;
	case 2:
		return !(map[x-1][y] || map[x-1][y+1]);
		break;
	case 3:
		return !(map[x][y+1] || map[x-1][y+1]);
		break;
	case 4:
		return !(map[x][y+1] || map[x+1][y+1]);
		break;
	case 5:
		return !(map[x+1][y] || map[x+1][y+1]);
		break;
	case 6:
		return !(map[x+1][y] || map[x+1][y-1]);
		break;
	case 7:
		return !(map[x][y-1] || map[x+1][y-1]);
		break;
	case 8:
		return !(map[x][y-1] || map[x-1][y-1]);
		break;
	default:
		return 0;
		break;
	}
}

int check(size_t n, int x, int y, int state) {
	if (!is_in_map(x, y, n)) return 0;
	switch (state)
	{
	case 1:
	case 8:
		return is_in_map(x-1, y-1, n);
		break;
	case 2:
	case 3:
		return is_in_map(x-1, y+1, n);
		break;
	case 4:
	case 5:
		return is_in_map(x+1, y+1, n);
		break;
	case 6:
	case 7:
		return is_in_map(x+1, y-1, n);
		break;
	default:
		return 0;
		break;
	}
}

int fill(int map[][COLUMN], size_t n, int x, int y, int state, int num_to_fill) {
	if (!check(n, x, y, state)) return 0;

	map[x][y] = num_to_fill;

	switch (state)
	{
	case 1:
		map[x-1][y] = num_to_fill;
		map[x-1][y-1] = num_to_fill;
		break;
	case 2:
		map[x-1][y] = num_to_fill;
		map[x-1][y+1] = num_to_fill;
		break;
	case 3:
		map[x][y+1] = num_to_fill;
		map[x-1][y+1] = num_to_fill;
		break;
	case 4:
		map[x][y+1] = num_to_fill;
		map[x+1][y+1] = num_to_fill;
		break;
	case 5:
		map[x+1][y] = num_to_fill;
		map[x+1][y+1] = num_to_fill;
		break;
	case 6:
		map[x+1][y] = num_to_fill;
		map[x+1][y-1] = num_to_fill;
		break;
	case 7:
		map[x][y-1] = num_to_fill;
		map[x+1][y-1] = num_to_fill;
		break;
	case 8:
		map[x][y-1] = num_to_fill;
		map[x-1][y-1] = num_to_fill;
		break;
	default:
		break;
	}
	return 1;
}

int find_empty_square(int map[][COLUMN], size_t n, int *x, int *y) {
	for (int row = 0; row < pow(2, n); row++) {
		for (int column = 0; column < pow(2, n); column++) {
			if (map[row][column] == 0 ) {
				*x= row;
				*y= column;
				return 1;
			}
		}
	}
	return 0;
}

int is_lonely_square(int map[][COLUMN], size_t n, int x, int y) {
	if (!(check(n, x, y, 1) && check(n, x, y, 5))) return 0;
	int empty_square_counter = 0;
	for (int i = -1; i<=1; i++) {
		for (int j = -1; j<=1; j++) {
			if (map[x+i][y+j] == 0) empty_square_counter++;
		}
	}
	if (empty_square_counter <=2) return 1;
	return 0;
}


int is_there_lonely_square(int map[][COLUMN], size_t n, int row_limit) {
	for (int x =0; x < row_limit; x++) {
		for (int y = 0; y<pow(2, n); y++) {
			if (is_lonely_square(map, n, x, y)) return 1;
		}
	}
	return 0;
}


void solve(int map[][COLUMN], size_t n, int k) {
	int max_depth = (pow(2, pow(2, n))-1)/3;

	// if (!find_empty_square(map, n, &x, &y)) return;

	for (int x = 0; x < pow(2, n); x++) {
		for (int y = 0; y < pow(2, n); y++) {
			if (map[x][y] == 0 ) {
				for (int state = 1; state<=8; state++) {
					if (check(n, x, y, state) && is_free(map, x, y, state)) {
						fill(map, n, x, y, state, k);
						// check stop condition
						// print_map(map, n);
						// printf("\n");
						// if (is_there_lonely_square(map, n, pow(2, n))) {
						// 	return;
						// }
						if (k >= max_depth) {
							print_map(map, n);
							exit(1);
						}
						else {
							solve(map, n, k+1);
						}
						fill(map, n, x, y, state, 0);
					}
				}
			}
		}
	}

	
}

int main() {

	size_t n;
	int map[512][COLUMN];

	scanf("%zu", &n);


	scanf("%d %d", &x_0, &y_0);
	x_0--;
	y_0--;


	fill_map(map, n, 0);
	map[x_0][y_0] = -1;

	solve(map, n, 1);
	// print_map(map, n);

	return 0;
}
