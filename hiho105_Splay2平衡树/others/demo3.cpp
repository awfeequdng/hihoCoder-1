#include <string>
#include <iostream>
#include <math.h>
#include <string.h>
#include <vector>
#include <queue>
#include <set>
#include <stdio.h>

#define dbg(x) cout << #x << ": " << x << endl
#define zero(x) (x >= - EPSINON) && (x <= EPSINON)

#define MIN_K 0
#define MAX_K 100000001
using namespace std;

class Node;
int n, key, key1, val;
char cmd[2];
Node* root;
void print(Node* root);

struct Node {
    Node* left;
    Node* right;
    Node* father;
    int key; // id
    int val;
    long int totalVal;
    int num;
    int lazy;
    // int weight;
    Node(int k, int v, Node* f) {left=NULL;right=NULL;father=f;key=k;val=v;lazy=0;num=1;totalVal=v;}
};

void update(Node* x){
    if(x==NULL) return;
	x->num = 1;
	x->totalVal = x->val;

	if (x->left != NULL) {
		x->num = x->num + x->left->num;
		x->totalVal = x->totalVal + x->left->totalVal;
	}
	
	if (x->right != NULL) {
		x->num = x->num + x->right->num;
		x->totalVal = x->totalVal + x->right->totalVal;
	}
}

void marking(Node* node,int delta){
    if(node==NULL) return;
	node->lazy = node->lazy + delta;
	node->totalVal = node->totalVal + node->num * delta;
	node->val = node->val + delta;
}

void send(Node* node){
	if (node->left != NULL) {
		marking(node->left, node->lazy);
	}
	if (node->right != NULL) {
		marking(node->right, node->lazy);
	}
	node->lazy = 0;
	update(node);
}

void leftRotate(Node* b) {
	Node* a = b->father;
	send(a);
	send(b);
	b->father = a->father;
	if (a->father!=NULL) {
    	if (a->father->left == a) {
    		a->father->left = b;
    	} else {
    		a->father->right = b;
    	}
	} else {
	    root = b;
	}
	a->right = b->left;
	if (b->left!=NULL) b->left->father = a;
	b->left = a;
	a->father = b;
	update(a);
	update(b);
}

void rightRotate(Node* b) {
	Node* a = b->father;
	send(a);
	send(b);
	b->father = a->father;
	if (a->father != NULL) {
    	if (a->father->left == a) {
    		a->father->left = b;
    	} else {
    		a->father->right = b;
    	}
	} else {
	    root = b;
	}
	a->left = b->right;
	if (b->right!=NULL) b->right->father = a;
	b->right = a;
	a->father = b;
	update(a);
	update(b);
}

void splay(Node* x,Node* y) {
    if(x==NULL) return;
    Node* p = NULL;
    Node* g = NULL;
	while (x->father != y) {
		p = x->father;
		if (p->father == y) {
			if (p->left == x) {
			    rightRotate(x);
			}else{
				leftRotate(x);
			}
		} else{
			g = p->father;
			if (g->left == p) {
				if (p->left == x) {
					rightRotate(p);
					rightRotate(x);
				} else {
					leftRotate(x);
					rightRotate(x);
				}
			} else {
				if (p->right == x) {
					leftRotate(p);
					leftRotate(x);
				} else {
					rightRotate(x);
					leftRotate(x);
				}
			}
		}
	}
}

Node* bst_find(Node* node,int key) {
    if (key==node->key) return node;
    if (key < node->key) {
		if (node->left==NULL) {
			return NULL;
		} else {
			return bst_find(node->left, key);
		}
	} else {
		if (node->right==NULL) {
			return NULL;
		} else {
			return bst_find(node->right, key);
		}
	}
}
	
void find(int key) {
	Node* node = bst_find(root, key);
	splay(node, NULL);
}

Node* bst_insert(Node* node,int key,int val) {
    send(node);
	if (key < node->key) {
		if (node->left==NULL) {
			node->left = new Node(key,val,node);
			update(node);
			return node->left;
		} else {
			Node* res = bst_insert(node->left, key,val);
			update(node);
			return res;
		}
	} else {
		if (node->right==NULL) {
			node->right = new Node(key,val,node);
			update(node);
			return node->right;
		} else {
			Node* res = bst_insert(node->right, key,val);
			update(node);
			return res;
		}
	}
}

void insert(int k,int val=0) {
    if (root == NULL) { 
        root = new Node(k,val,NULL);
    } else {
        Node* node = bst_insert(root, k,val);
        splay(node, NULL);
    }
}


Node* findPrev(int key) {
    find(key);
	Node* node = root->left;
	while (node->right) {
		node = node->right;
	}
	return node;
}

Node* findNext(int key) {
	find(key);
	Node* node = root->right;
	while (node->left) {
		node = node->left;
	}
	return node;
}

void myDelete(int key){
    Node* prev = findPrev(key);
    Node* next = findNext(key);
    splay(prev,NULL);
    splay(next,prev);
    // delete next->left;
    next->left = NULL;
    update(next);
	update(prev);
}

void deleteInterval(int a,int b) {
    if(a<=MIN_K) a=MIN_K+1;
    if(b>=MAX_K) b=MAX_K-1;
    if(a>b) return;
    
    Node* aa = bst_find(root, a);
    if(aa==NULL) insert(a);
	Node* prev = findPrev(a);
	
    Node* bb = bst_find(root, b);
    if(bb==NULL) insert(b);
	Node* next = findNext(b);
	
	splay(prev, NULL);
	splay(next, prev);
// 	delete next->left;
	if (next!=NULL) next->left = NULL;
	
	update(next);
	update(prev);
}

long int query(int a, int b) {
    if(a<=MIN_K) a=MIN_K+1;
    if(b>=MAX_K) b=MAX_K-1;
    if(a>b) return 0;
    
    Node* aa = bst_find(root, a);
    if(aa==NULL) insert(a);
	Node* prev = findPrev(a);
	
    Node* bb = bst_find(root, b);
    if(bb==NULL) insert(b);
	Node* next = findNext(b);
	
    splay(prev,NULL);
    splay(next,prev);
    long int ans = next->left->totalVal;
    
    if(aa==NULL) myDelete(a);
    if(bb==NULL) myDelete(b);
    return ans;
}

void modify(int a, int b, int delta) {
    if(a<=MIN_K) a=MIN_K+1;
    if(b>=MAX_K) b=MAX_K-1;
    if(a>b) return;
    
    Node* aa = bst_find(root, a);
    if(aa==NULL) insert(a);
	Node* prev = findPrev(a);
	
    Node* bb = bst_find(root, b);
    if(bb==NULL) insert(b);
	Node* next = findNext(b);
	
    splay(prev,NULL);
    splay(next,prev);
    
    marking(next->left,delta);
    update(next);
	update(prev);
    
    if(aa==NULL) myDelete(a);
    if(bb==NULL) myDelete(b);
}

void print(Node* r) {
    if (r == NULL) {
        printf("null\n");
        return;
    }
    printf("%d\n",r->key);
    printf("left ");
    print(r->left);
    printf("right ");
    print(r->right);
}
void solve() {
    scanf("%d",&n);
    root = NULL;
    insert(MIN_K);
    insert(MAX_K);
    for(int i=0;i<n;i++) {
        scanf("%s%d%d", cmd, &key, &val);
        if (cmd[0]=='I') insert(key,val);
        else if (cmd[0]=='Q') {
           long  int ans = query(key, val);
            printf("%ld\n",ans);
        } else if(cmd[0]=='D') {
            deleteInterval(key,val);
        } else if(cmd[0]=='M') {
            scanf("%d",&key1);
            modify(key,val,key1);
        }
    }
    // I 1 1
    // I 2 2
    // I 3 3
    // Q 1 3
    // M 1 2 2
    // Q 1 3
    // D 2 3
    // I 4 2
    // Q 1 4
    // insert(MIN_K);
    // insert(MAX_K);
    // insert(1,1);
    // insert(2,2);
    // insert(3,3);
    // printf("%d\n",query(1,MAX_K));
    // modify(1,2,-2);
    // printf("%d\n",query(1,MAX_K));
    // deleteInterval(2,3);
    // insert(4,2);
    // printf("%d\n",query(1,MAX_K));
}

int main() {
    solve();
    return 0;
}