#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#define MAX 100010
#define query edge
using namespace std;

map<string, int> idx;
int idx_cnt = 1;
int cnt = 1;
int N, M;
int ans[MAX];

struct {
	int to;
	int next;
}edge[3*MAX];

struct {
	int father;
	int edge_header;
	int flag;
	int query_header;
}node[MAX];

void dfs(int idx);
int main() {
	int i;
	char temp1[20], temp2[20];
	string s1, s2;
	string str[MAX];
	int idx1, idx2;
	memset(node, 0, sizeof(node));
	scanf("%d", &N);
	for(i = 0; i < N; i++) {
		scanf("%s%s", temp1, temp2);
		s1 = string(temp1);
		s2 = string(temp2);
		if(!(idx1 = idx[s1])) {
			idx[s1] = idx_cnt;
			str[idx_cnt] = s1;
			idx1 = idx_cnt++;
		}
		if(!(idx2 = idx[s2])) {
			idx[s2] = idx_cnt;
			str[idx_cnt] = s2;
			idx2 = idx_cnt++;
		}
		edge[cnt].next = node[idx1].edge_header;
		edge[cnt].to = idx2;
		node[idx1].edge_header = cnt++;
	}
	scanf("%d", &M);
	for(i = 0; i < M; i++) {
		scanf("%s%s", temp1, temp2);
		idx1 = idx[string(temp1)];
		idx2 = idx[string(temp2)];
		query[cnt].next = node[idx1].query_header;
		query[cnt].to = idx2;
		node[idx1].query_header = cnt++;
		query[cnt].next = node[idx2].query_header;
		query[cnt].to = idx1;
		node[idx2].query_header = cnt++;
	}
	dfs(1);
	for(i = 0; i < M; i++)
		printf("%s\n", str[ans[i]].c_str());
	return 0;
}

void dfs(int t) {
	int i, j, p;
	node[t].flag = 1;
	for(i = node[t].query_header; i; i = query[i].next) {
		j = query[i].to;
		if(node[j].flag == 1)
			ans[(i - N - 1) >> 1] = j;
		else if(node[j].flag == 2) {
			p = node[j].father;
			while(node[p].father)
				p = node[p].father;
			node[j].father = p;
			ans[(i - N - 1) >> 1] = p;
		}
	}
	for(i = node[t].edge_header; i; i = edge[i].next) {
		j = edge[i].to;
		dfs(j);
		node[j].father = t;
	}
	node[t].flag = 2;
}
