#include <bits/stdc++.h>
using namespace std;

int n;

struct node {
	int val;
	node *par, *child[2];

	node(int val) : val(val), par(NULL) {}
} *root;

void rotate(node* const x, int c) {
	node* const y = x->par;
	y->child[c ^ 1] = x->child[c];
	if (x->child[c] != NULL) x->child[c]->par = y;
	x->par = y->par;
	if (y->par != NULL && y->par->child[0] == y) y->par->child[0] = x;
	else if (y->par != NULL && y->par->child[1] == y) y->par->child[1] = x;
	y->par = x;
	x->child[c] = y;
}
inline bool _splay_parent(node *x, node* (&y), node* stop) {
	return (y = x->par) != stop && (x == y->child[0] || x == y->child[1]);
}
void splay(node* const x, node* const stop) {
	for (node *y, *z; _splay_parent(x, y, stop); ) {
		if (_splay_parent(y, z, stop)) {
			const int c = y == z->child[0];
			if (x == y->child[c]) rotate(x, c ^ 1), rotate(x, c);
			else rotate(y, c), rotate(x, c);
		} else {
			rotate(x, x == y->child[0]);
			break;
		}
	}
	if (stop == NULL) root = x;
}
node* insert(node *u, int val) {
	if (u->val == val) return u;

	if (u->child[val > u->val] == NULL) {
		node *v = new node(val);
		v->child[0] = v->child[1] = NULL;
		v->par = u;
		u->child[val > u->val] = v;
		return v;
	}

	return insert(u->child[val > u->val], val);
}
node* find(node *u, int val) {
	if (u->val == val) return u;

	if (u->child[val > u->val] == NULL) return NULL;

	return find(u->child[val > u->val], val);
}
node* get_max(node *u) {
	if (u->child[1] == NULL) return u;
	return get_max(u->child[1]);
}
node* get_min(node *u) {
	if (u->child[0] == NULL) return u;
	return get_min(u->child[0]);
}
void insert(int val) {
	node* u = insert(root, val);
	splay(u, NULL);
}
void erase(int l, int r) {
	insert(l), insert(r);
	
	node* u = find(root, l);
	splay(u, NULL);
	
	node* prev = get_max(root->child[0]);

	node* v = find(root, r);
	splay(v, NULL);

	node* next = get_min(root->child[1]);
	
	splay(prev, NULL);
	splay(next, prev);
	
	next->child[0] = NULL;
}
int query(int val) {
	node* u = find(root, val + 1);
	bool del = u == NULL;

	if (u == NULL) u = insert(root, val + 1);

	splay(u, NULL);

	int ret = get_max(root->child[0])->val;

	if (del) erase(val + 1, val + 1);
	
	return ret;
}
int main() {
	root = new node(-1);
	root->child[0] = root->child[1] = NULL;
	insert((int)2e9);
	
	scanf("%d", &n);

	char ope;
	int x, y;

	while (n--) {
		scanf("\n%c %d", &ope, &x);

		if (ope == 'I') insert(x);
		else if (ope == 'Q') printf("%d\n", query(x));
		else {
			scanf("%d", &y);
			erase(x, y);
		}

	}

	return 0;
}