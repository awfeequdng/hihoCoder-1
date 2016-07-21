#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

const int N = 100005;
const int M = 200005;

int n, m;
int tot, head[N], to[N], next[N];
int tot1, head1[N], to1[M], id[M], next1[M];
int fa[N], ans[N];
char name[100005][100], name1[100], name2[100];
bool visit[N];
map <string, int> ns;

void addEdge(const int& u, const int& v) {
	to[tot] = v;
	next[tot] = head[u];
	head[u] = tot++;
}

void addEdge1(const int& u, const int& v, const int& i) {
	to1[tot1] = v;
	id[tot1] = i;
	next1[tot1] = head1[u];
	head1[u] = tot1++;
}

void addDoubleEdge(const int& u, const int& v, const int& i) {
	addEdge1(u, v, i), addEdge1(v, u, i);
}

int find(const int& u) {
	return fa[u] < 0 ? u : (fa[u] = find(fa[u]));
}

void tarjan(const int& u) {
	visit[u] = true;
	fa[u] = -1;
	for (int i = head[u]; i != -1; i = next[i]) {
		int v = to[i];
		tarjan(v);
		fa[v] = u;
	}

	for (int i = head1[u]; i != -1; i = next1[i]) {
		int v = to1[i];
		if (visit[v])
			ans[id[i]] = find(v);
	}
}

int main()
{
	while (scanf("%d", &n) != EOF) {
		memset(head, -1, sizeof(head));
		memset(head1, -1, sizeof(head1));
		tot = tot1 = 0;
		ns.clear();
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%s %s", name1, name2);
			string fa(name1), son(name2);
			if (ns.find(fa) == ns.end())
				strcpy(name[cnt], name1), ns[fa] = cnt++;
			if (ns.find(son) == ns.end())
				strcpy(name[cnt], name2), ns[son] = cnt++;
			addEdge(ns[fa], ns[son]);
		}
		scanf("%d", &m);
		for (int i = 0; i < m; ++i) {
			scanf("%s %s", name1, name2);
			string fa(name1), son(name2);
			addDoubleEdge(ns[fa], ns[son], i);
		}
		memset(visit, false, sizeof(visit));
		tarjan(0);
		for (int i = 0; i < m; ++i)
			printf("%s\n", name[ans[i]]);
	}
	return 0;
}
