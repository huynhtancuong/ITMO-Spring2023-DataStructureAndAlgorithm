#include <stdio.h>

int f(int b, int a, int va, int vb) {
	if (b > 0) {
		return (b-1)*(vb*vb) + a*(vb*va) + f(b-1, a, va, vb);
	}
	if (a > 0) {
		return (a-1)*(va*va) + b*(va*vb) + f(b, a-1, va, vb);
	}
	return 0;
}

int main() {

	int T;
	scanf("%d", &T);

	int n, k;
	for (int i = 0; i<T; i++) {
		scanf("%d %d", &n, &k);


		int a, b, va, vb;

		a = n%k;
		b = k - a;
		va = n/k +1;
		vb = n/k;

		int max = f(b, a, va, vb);

		printf("%d\n", max);

	}
	return 0;
}
