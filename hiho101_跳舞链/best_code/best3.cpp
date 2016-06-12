#include <stdio.h>
#include <string.h>
int data[110][110];
int flag[110][110];
int status[110][110];

int n, m;
int check(int col, int depth) {
	int i, j;
	if (col == m) return 1;
	if (status[depth][col] == 1) return check(col + 1, depth);
	else if (status[depth][col] > 1) return 0;
	for (i = 0; i < n; i++)
		if (data[i][col] && !flag[i][col]) {
			for (j = col; j < m; j++)
				status[depth + 1][j] = status[depth][j] + data[i][j];
			if (check(col + 1, depth + 1)) return 1;
		}
	return 0;
}

int main() {
	int t, i, j;
	scanf("%d", &t);
	memset(status[0], 0, 110 * sizeof(int));
	while (t--) {
		scanf("%d%d", &n, &m);
		for (i = 0; i < n; i++) {
			int f = 0;
			for (j = 0; j < m; j++) {
				flag[i][j] = f;
				scanf("%d", &data[i][j]);
				f |= data[i][j];
			}
		}
		if (check(0, 0)) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}