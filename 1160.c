#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define maxN 1001

// Struct for Edge
typedef struct {
	int u, v, c; // hai dinh va trong so
	int mark; // danh dau co duoc ket nap vao khung cay hay chua
} Edge_s;

// Global variables
int Lab[maxN];
int Count[maxN];
Edge_s E[maxN];
int count = 0;
int connected = 0;
int maximum_length = 0;


void swap(Edge_s *a, Edge_s *b) {
	Edge_s temp = *a;
	*a = *b;
	*b = temp;
}

void printArray(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void BuildMaxHeap(Edge_s arr[], int n) {
	for (int i = n / 2; i >= 0; i--) {
		maxHeapify(arr, n, i);
	}
}

void maxHeapify(Edge_s arr[], int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if ((left < n) && (arr[left].c > arr[i].c)) 
		largest = left;
	else	
		largest = i;
	
	if ( (right < n) && (arr[right].c > arr[largest].c)) 
		largest = right;

	if (largest != i) {
		swap(&arr[largest], &arr[i]);
		maxHeapify(arr, n, largest);
	}

}

void Heapsort(Edge_s arr[], int n) {
	BuildMaxHeap(arr, n);
	for (int i = n-1; i>=0; i--) {
		swap(&arr[0], &arr[i]);
		n--;
		maxHeapify(arr, n, 0);
	}
}

void Kruskal(Edge_s E[], int n, int m) {
	for (int i = 0; i < m; i++) {
		int r1 = getRoot(E[i].u);
		int r2 = getRoot(E[i].v);
		if (r1 != r2) { // canh E[i] noi hai cay khac nhau
			E[i].mark = 1;
			count++;
			if (count == n-1) { // Neu da dem du so canh
				connected = 1;
				break;
			}
			merge(r1, r2);
		}
	}
}

int getRoot(int v) {
	while (Lab[v] > 0) {
		v = Lab[v];
	}
	return v;
}

void merge(int r1, int r2) {
	if (Count[r1] < Count[r2]) { // merge r1 into r2
		Count[r2] = Count[r1] + Count[r2];
		Lab[r1] = r2;
	}
	else { // merge r2 into r1
		Count[r1] = Count[r2] + Count[r1];
		Lab[r2] = r1;
	}
}

void printResult(int n, int m) {
	if (!connected) {
		printf("0\n");
	}
	else {
		// printf("Minimal spanning tree:\n");
		int count = 0;
		int W = 0;
		for (int i = 0; i < m; i++) {
			if (E[i].mark == 1) {
				W += 1;
				count++;
				if (maximum_length < E[i].c) {
					maximum_length = E[i].c;
				}
			}
			if (count == n-1) {
				break;
			}
		}
		printf("%d\n", maximum_length);
		printf("%d\n", W);

		count = 0;
		for (int i = 0; i < m; i++) {
			if (E[i].mark == 1) {
				count++;
				printf("%d %d\n", E[i].u, E[i].v);
			}
			if (count == n-1) {
				break;
			}
		}

	}
}

void loadGraph(int m) {
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &E[i].u, &E[i].v, &E[i].c);
	}
}

void init(int n, int m) {
	for (int i = 0; i < n; i++) {
		Lab[i] = -1; // Rừng ban đầu, mọi đỉnh là gốc của cây gồm đúng một nút
		Count[i] = 1;
	}
	for (int i = 0; i < m; i++) {
		E[i].mark = 0;
	}
}

int main() {

	int n, m;
	scanf("%d %d", &n, &m);
	loadGraph(m);
	
	init(n, m);

	Heapsort(E, m);

	Kruskal(E, n, m);
	printResult(n, m);

	return 0;
}
