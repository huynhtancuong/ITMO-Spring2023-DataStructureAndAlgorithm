#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxN 500

int graph[maxN][maxN];
unsigned int n, m;

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

	// print_graph(n);
	unsigned int max_profit = find_max(u, v, 1);
	if (max_profit != 0) printf("%d\n", max_profit);
	else printf("No solution\n");

	return 0;
}
