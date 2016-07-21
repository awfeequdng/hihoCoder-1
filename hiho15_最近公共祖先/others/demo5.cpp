#include <bits/stdc++.h>

using namespace std;

class TreeNode {
public:
	string name;
	struct TreeNode *parent;
	vector<TreeNode *> children;
	int color;
	TreeNode(string name_) : name(name_) { parent = NULL; color = 0; }
};

#define N 100010
string result[N];
map<string, TreeNode *> table;
typedef pair<TreeNode*,int> pti;
map<TreeNode*, vector<pti> > queries;

TreeNode *find_root(TreeNode *p)
{
	if (p->color == 1)
		return p;
	else { // color == 2
		p->parent = find_root(p->parent);
		return p->parent;
	}
}

void dfs(TreeNode *p1)
{
	p1->color = 1;

	vector<pti> &ptiv = queries[p1];
	for (int i = 0; i < ptiv.size(); i++) {
		TreeNode *p2 = ptiv[i].first;
		int idx = ptiv[i].second;
		if (p2->color == 0)
			continue;
		result[idx] = find_root(p2)->name;
	}

	for (int i = 0; i < p1->children.size(); i++)
		dfs(p1->children[i]);

	p1->color = 2;
}

int main()
{
	int n, m;
	string n1, n2;
	TreeNode *root;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> n1 >> n2;
		if (table.find(n1) == table.end()) table[n1] = new TreeNode(n1);
		if (table.find(n2) == table.end()) table[n2] = new TreeNode(n2);
		table[n1]->children.push_back(table[n2]);
		table[n2]->parent = table[n1];
		if (i == 0) root = table[n1];
	}

	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> n1 >> n2;
		TreeNode *p1 = table[n1], *p2 = table[n2];
		if (queries.find(p1) == queries.end()) queries[p1] = vector<pti>();
		if (queries.find(p2) == queries.end()) queries[p2] = vector<pti>();
		queries[p1].push_back(pti(p2,i));
		if (p1 != p2)
			queries[p2].push_back(pti(p1,i));
	}

	dfs(root);

	for (int i = 0; i < m; i++)
		cout << result[i] << endl;
}
