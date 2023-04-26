#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define maxN 501
#define negative_infinity -1000000000000

int graph[maxN][maxN];
unsigned int n, m;
int64_t d[maxN];


void print_graph(int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%d ", graph[i][j]);
		}
		printf("\n");
	}
}

int find_max(int u, int v, unsigned int depth) {
	if (depth == n) return 0;
	if (graph[u][v] != 0) return graph[u][v];
	unsigned int max_profit = 0;
	for (unsigned int i = 1; i <= n; i++) {
		if (graph[u][i] != 0) {
			unsigned int profit = find_max(i, v, depth+1);
			if (profit != 0) profit += graph[u][i];
			if (profit > max_profit) max_profit = profit;
		}
	}
	return max_profit;
}

void Ford_Bellman() {
	int stop;
	do
	{
		stop = 1;
		for (unsigned int u = 1; u <= n; u++) {
			for (unsigned int v = 1; v <= n; v++) {
				if (graph[u][v] != 0) {
					if (d[v] < d[u] + graph[u][v]) {
						d[v] = d[u] + graph[u][v];
						stop = 0;
					}
				}
			}
		}
	} while (!stop);
}

int main() {
	// init graph
	memset(graph, 0, sizeof(graph));

	
	scanf("%u %u", &n, &m);
	for (unsigned int i = 0; i < m; i++) {
		unsigned int a, b, c;
		scanf("%u %u %u", &a, &b, &c);
		graph[a][b] = c;
	}
	unsigned int u, v;
	scanf("%u %u", &u, &v);

	// init array d
	for (unsigned int i = 1; i <= n; i++) {
		d[i] = negative_infinity;
	}
	d[u] = 0;

	// print_graph(n);
	Ford_Bellman();
	if (d[v] <= 0) {
		printf("No solution");
	}
	else {
		printf("%ld\n", d[v]);
	}
	// printf("%ld\n", d[v]);
	

	return 0;
}
