#include <stdio.h>

int main() {
	int N;
	scanf("%d", &N);

	int valid = 1;
	int ball_order = N;
	for (int i = 0; i<N; i++) {
		int ball_check;
		scanf("%d", &ball_check);
		if (ball_check - ball_order < -2) {
			valid = 0;
		}
		ball_order--;
	}

	if (valid) printf("Not a proof\n");
	else printf("Cheater\n");

	return 0;
}
