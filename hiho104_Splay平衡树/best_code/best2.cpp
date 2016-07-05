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
#define MAX_K 1000000001
using namespace std;

class Node;
int n, key, key1;
char cmd[2];
Node* root;
void print(Node* root);

struct Node {
    Node* left;
    Node* right;
    Node* father;
    int key;
    // int weight;
    Node(int k, Node* f) {left=NULL;right=NULL;father=f;key=k;}
};

void leftRotate(Node* b) {
	Node* a = b->father;
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
}

void rightRotate(Node* b) {
	Node* a = b->father;
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

Node* bst_insert(Node* node,int key) {
	if (key < node->key) {
		if (node->left==NULL) {
			node->left = new Node(key,node);
			return node->left;
		} else {
			return bst_insert(node->left, key);
		}
	} else {
		if (node->right==NULL) {
			node->right = new Node(key,node);
			return node->right;
		} else {
			return bst_insert(node->right, key);
		}
	}
}

// void rotate(Node* node) {
// 	Node* fa = NULL;
// 	while (node->father!=NULL) {
// 		fa = node->father;
// 		if (node->weight < fa->weight) {
// 			if (node == fa->left) {
// 				rightRotate(fa);
// 				// return;
// 			} else {
// 				leftRotate(fa);
// 				// return;
// 			}
// 		} else {
// 			break;
// 		}
// 	}
// }

void insert(int k) {
    if (root == NULL) { 
        root = new Node(k,NULL);
    } else {
        Node* node = bst_insert(root, k);
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
}

void deleteInterval(int a,int b) {
    if(a<=MIN_K) a=MIN_K+1;
    if(b>=MAX_K) b=MAX_K-1;

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
}

int ans;
bool quit = false;
int query(Node* node, int k) {
    // printf("%d %d\n",node->key,node->weight);
    if (node->key == k) {
        return k;
    }
    if (node->key > k) {
        if (node->left==NULL) return ans;
        else return query(node->left, k);
    }
    if (node->right==NULL) return node->key;
    else {
        ans=node->key;
        return query(node->right,k);
    }
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
        scanf("%s%d", cmd, &key);
        if (cmd[0]=='I') insert(key);
        else if (cmd[0]=='Q') {
            int ans = query(root, key);
            printf("%d\n",ans==0?key:ans);
            quit=false;
        } else if(cmd[0]=='D') {
            scanf("%d",&key1);
            deleteInterval(key,key1);
        }
    }
    // I 1
    // I 2
    // I 3
    // Q 4
    // D 2 2
    // Q 2
    // root=NULL;
    // insert(MIN_K);
    // insert(MAX_K);
    //
    // insert(1);
    // insert(2);
    // insert(3);
    // insert(5);
    // insert(4);
    // print(root);
    // printf("\n");
    // myDelete(1);
    // print(root);
    // printf("\n");
    // myDelete(5);
    // print(root);
    // printf("\n");
    // printf("%d\n",query(root,4));
    // quit=false;
    // deleteInterval(2,2);
    // printf("%d\n",query(root,2));
    // quit=false;
}

int main() {
    solve();
    return 0;
}
