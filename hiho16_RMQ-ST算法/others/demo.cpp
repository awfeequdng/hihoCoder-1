#include <stdio.h>
#include <math.h>

#define N 1000010
#define GET_MIN(a, b) (a < b ? a : b)

int num[N];
int f[N][20];
int n;

//Sparse Table

int main()
{
	int i, j, m, l, r, k;

	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &f[i][0]);
	}
	k = log2(n);
	for(j = 1; j <= k; j++) {
		for(i = 0; i + (1 << j) - 1 < n; i++) {
			m = i + (1 << (j - 1));
			f[i][j] = GET_MIN(f[i][j - 1], f[m][j - 1]);
		}
	}
	scanf("%d", &m);
	for(i = 0; i < m; i++) {
		scanf("%d%d", &l, &r);
		l--;r--;
		k = log2(r - l + 1);
		printf("%d\n", GET_MIN(f[l][k], f[r - (1 << k) + 1][k]));
	}
}
