#include <stdio.h>

/// @brief This function calculate the matches between fighters in diffent teams.
/// @param b amount of basic team
/// @param a amount of advanced team
/// @param va amount of team member in advanced team
/// @param vb amount of team member in basic team
/// @return matches between fighters in diffent teams
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

	// Input

	int T;
	scanf("%d", &T);

	int n, k;
	
	// Find answer for every (n, k), where n - number of fighters, k - number of teams.

	for (int i = 0; i<T; i++) {
		// Input n and k
		scanf("%d %d", &n, &k);


		int a, b, va, vb;
		/**
		 * a - number of advanced team, which is the team with more member (n/k+1)
		 * b - number of basic team, which is the team with basic member (n/k)
		 * va - the amount of team member in advanced team.
		 * vb - the amount of team member in basic team.
		*/

		a = n%k;
		b = k - a;
		va = n/k +1;
		vb = n/k;

		int max = f(b, a, va, vb);

		printf("%d\n", max);

	}
	return 0;
}
