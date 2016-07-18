#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>

using namespace std;

#define MAXN 101

struct node
{
	int v;
	int f[MAXN];
	vector<int> children;
	node() { memset(f, 0, sizeof(f)); }
} tree[MAXN];

int main(int argc, char **argv)
{
	int N, M, a, b, i, j, k, s[MAXN + 2], sp = 1, *pf, *pfc;
	static bool visited[MAXN];
	scanf("%d%d", &N, &M);
	vector<vector<int> > g(N + 1, vector<int>());

	for (i = 1; i <= N; ++i)
		scanf("%d", &(tree[i].v));
	for (i = 1; i < N; ++i)
	{
		scanf("%d%d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}

	//bfs build tree with root 1, a -> queue head, b -> queue tail
	a = 0, b = 1, s[0] = 1;
	while (a < b)
	{
		sp = s[a++];
		visited[sp] = true;
		k = g[sp].size();
		for (i = 0; i < k; ++i)
		{
			j = g[sp][i];
			if (!visited[j])
			{
				visited[j] = true;
				tree[sp].children.push_back(j);
				s[b++] = j;
			}
		}
	}

	//post order traversal
	memset(visited, false, sizeof(visited));
	sp = 1, s[1] = 1;
	while (sp)
	{
		k = s[sp];
		if (!visited[k])
		{
			//push children
			visited[k] = true;
			j = tree[k].children.size();
			for (i = 0; i < j; ++i)
				s[++sp] = tree[k].children[i];
		}
		else
		{
			//pop
			pf = tree[k].f;
			pf[1] = tree[k].v;
			for (j = 0; j < tree[k].children.size(); ++j)
			{
				pfc = tree[tree[k].children[j]].f;
				for (a = M; a >= 2; --a)
				{
					for (b = 1; b < a; ++b)
						pf[a] = max(pf[a], pf[a - b] + pfc[b]);
				}
			}
			--sp;
		}
	}
	printf("%d\n", tree[1].f[M]);
	return 0;
}