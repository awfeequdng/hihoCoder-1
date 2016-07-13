#include <iostream>
#define MIN 0
#define MAX 100000001
using namespace std;

typedef struct node
{
    int id, val, num, lazy;
    long int totalVal;
    node *father, *left, *right;
    node(int id_, int val_) : id(id_), val(val_)
    {
        num = 1;
        totalVal = val;
        lazy = 0;
        father = NULL;
        left = NULL;
        right = NULL;
    }
}*Node;

Node root = NULL;

void update(Node x)
{
    if(x == NULL)
        return;
    x->num = 1;
    x->totalVal = x->num;

    if(x->left)
    {
        x->num = x->num + x->left->num;
        x->totalVal = x->totalVal + x->left->totalVal;
    }

    if(x->right)
    {
        x->num = x->num + x->right->num;
        x->totalVal = x->totalVal + x->right->totalVal;
    }
}

void marking(Node node, int delta)
{
    if(node == NULL)
        return;
    node->lazy = node->lazy + delta;
    node->totalVal = node->totalVal + node->num * delta;
    node->val = node->val + delta;
}

void send(Node node)
{
    if(node->left)
        marking(node->left, node->lazy);
    if(node->right)
        marking(node->right, node->lazy);
    node->lazy = 0;
    update(node);
}

void leftRotate(Node b)
{
    Node a = b->father;
    send(a);
    send(b);
    b->father = a->father;
    if(a->father)
    {
        if(a->father->left == a)
            a->father->left = b;
        else
            a->father->right = b;
    }
    else
    {
        root = b;
    }
    a->right = b->left;
    if(b->left)
        b->left->father = a;
    b->left = a;
    a->father = b;
    update(a);
    update(b);
}

void rightRotate(Node b)
{
    Node a = b->father;
    send(a);
    send(b);
    b->father = a->father;
    if(a->father)
    {
        if(a->father->left == a)
            a->father->left = b;
        else
            a->father->right = b;
    }
    else
        root = b;
    a->left = b->right;
    if(b->right)
        b->right->father = a;
    b->right = a;
    a->father = b;
    update(a);
    update(b);
}

void splay(Node x,Node y) {
    if(x==NULL) return;
    Node p = NULL;
    Node g = NULL;
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

Node bst_find(Node node,int key) 
{
    if (key==node->id) return node;
    if (key < node->id) 
    {
        if (node->left==NULL) 
        {
            return NULL;
        } 
        else 
        {
            return bst_find(node->left, key);
        }
    } 
    else 
    {
        if (node->right==NULL) 
        {
            return NULL;
        } 
        else 
        {
            return bst_find(node->right, key);
        }
    }
}

void find(int key) 
{
    Node node = bst_find(root, key);
    splay(node, NULL);
}

Node bst_insert(Node n,int key,int val) {
    send(n);
    if (key < n->id) {
        if (n->left==NULL) {
            n->left = new node(key,val);
            n->left->father = n;
            update(n);
            return n->left;
        } else {
            Node res = bst_insert(n->left, key,val);
            update(n);
            return res;
        }
    } else {
        if (n->right==NULL) {
            n->right = new node(key,val);
            n->right->father = n;
            update(n);
            return n->right;
        } else {
            Node res = bst_insert(n->right, key,val);
            update(n);
            return res;
        }
    }
}

void insert(int k,int val=0) 
{
    if (root == NULL) { 
        root = new node(k,val);
    } else {
        Node node = bst_insert(root, k,val);
        splay(node, NULL);
    }
}

Node findPrev(int key) {
    find(key);
    Node node = root->left;
    while (node->right) {
        node = node->right;
    }
    return node;
}

Node findNext(int key) {
    find(key);
    Node node = root->right;
    while (node->left) {
        node = node->left;
    }
    return node;
}

void myDelete(int key){
    Node prev = findPrev(key);
    Node next = findNext(key);
    splay(prev,NULL);
    splay(next,prev);
    // delete next->left;
    next->left = NULL;
    update(next);
    update(prev);
}

void deleteInterval(int a,int b) {
    if(a<=MIN) a=MIN+1;
    if(b>=MAX) b=MAX-1;
    if(a>b) return;
    
    Node aa = bst_find(root, a);
    if(aa==NULL) insert(a);
    Node prev = findPrev(a);
    
    Node bb = bst_find(root, b);
    if(bb==NULL) insert(b);
    Node next = findNext(b);
    
    splay(prev, NULL);
    splay(next, prev);
//  delete next->left;
    if (next!=NULL) next->left = NULL;
    
    update(next);
    update(prev);
}

long int query(int a, int b) {
    if(a<=MIN) a=MIN+1;
    if(b>=MAX) b=MAX-1;
    if(a>b) return 0;
    
    Node aa = bst_find(root, a);
    if(aa==NULL) insert(a);
    Node prev = findPrev(a);
    
    Node bb = bst_find(root, b);
    if(bb==NULL) insert(b);
    Node next = findNext(b);
    
    splay(prev,NULL);
    splay(next,prev);
    cout << next->left->totalVal << endl;
    long int ans = next->left->totalVal;
    
    if(aa==NULL) myDelete(a);
    if(bb==NULL) myDelete(b);
    return ans;
}

void modify(int a, int b, int delta) {
    if(a<=MIN) a=MIN+1;
    if(b>=MAX) b=MAX-1;
    if(a>b) return;
    
    Node aa = bst_find(root, a);
    if(aa==NULL) insert(a);
    Node prev = findPrev(a);
    
    Node bb = bst_find(root, b);
    if(bb==NULL) insert(b);
    Node next = findNext(b);
    
    splay(prev,NULL);
    splay(next,prev);
    
    marking(next->left,delta);
    update(next);
    update(prev);
    
    if(aa==NULL) myDelete(a);
    if(bb==NULL) myDelete(b);
}

void print(Node r) {
    if (r == NULL) {
        printf("null\n");
        return;
    }
    printf("%d\n",r->id);
    printf("left ");
    print(r->left);
    printf("right ");
    print(r->right);
}

int main()
{
    insert(MIN);
    insert(MAX);
    int a, b, d;
    char ch;
    int n;
    cin >> n;
    while(n--)
    {
        cin >> ch >> a >> b;
        if(ch == 'I')
        {
            insert(a, b);
            print(root);
        }
        else if(ch == 'Q')
        {
            cout << query(a, b) << endl;
            print(root);
        }
        else if(ch == 'M')
        {
            cin >> d;
            modify(a, b, d);
        }
        else if(ch == 'D')
        {
            deleteInterval(a, b);
        }
    }
    return 0;
}