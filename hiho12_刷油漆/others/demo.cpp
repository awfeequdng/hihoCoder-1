#include <cstdio>

#define MAX(x,y) ((x)>(y)?(x):(y))

int f[101][101] = {}, header[101] = {};
int n, m;
struct {
	int next, to;
} tree_node[100];

void dfs(int);

int main() {
	int i, from, to;
	scanf("%d%d", &n, &m);
	for(i = 1; i <= n; i++)
		scanf("%d", &f[i][1]);
	for(i = 1; i < n ; i++) {
		scanf("%d%d", &from, &to);
		tree_node[i].to = to;
		tree_node[i].next = header[from];
		header[from] = i;
	}
	dfs(1);
	printf("%d\n", f[1][m]);
	return 0;
}

void dfs(int t) {
	int p = header[t];
	int i, j;
	while(p) {
		dfs(tree_node[p].to);
		p = tree_node[p].next;
	}

	p = header[t];
	while(p) {
		for(j = m; j > 1; j--)
			for(i = 1; i < j; i++)
				f[t][j] = MAX(f[t][j], f[t][j-i] + f[tree_node[p].to][i]);
		p = tree_node[p].next;
	}
}
