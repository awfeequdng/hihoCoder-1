#include <iostream>
#define MIN_K -1
#define MAX_K 1000000001

using namespace std;

typedef struct node
{
    int key;
    node *father, *left, *right;
    node(int key_) : key(key_)
    {
        this->father = NULL;
        this->left = NULL;
        this->right = NULL;
    }
}*Node;

Node root = NULL;

void right_rotate(Node x)
{
    Node p = x->father;
    x->father = p->father;
    if(p->father)
    {
        if(p->father->left == p)
            p->father->left = x;
        else
            p->father->right = x;
    }
    else
        root = x;
    p->left = x->right;
    if(x->right)
        x->right->father = p;
    x->right = p;
    p->father = x;
}

void left_rotate(Node x)
{
    Node p = x->father;
    x->father = p->father;
    if(p->father)
    {
        if(p->father->left == p)
            p->father->left = x;
        else
            p->father->right = x;
    }
    else
        root = x;
    p->right = x->left;
    if(x->left)
        x->left->father = p;
    x->left = p;
    p->father = x;
}

void splay(Node x, Node y)
{
    if(x == NULL)
        return;
    while(x->father != NULL)
    {
        Node p = x->father;
        if(p->father == y)
        {
            if(p->left == x)
                right_rotate(x);
            else
                left_rotate(x);
        }
        else
        {
            Node g = p->father;
            if(g->left == p)
            {
                if(p->left == x)
                {
                    right_rotate(p);
                    right_rotate(x);
                }
                else
                {
                    left_rotate(x);
                    left_rotate(x);
                }
            }
            else
            {
                if(p->right == x)
                {
                    left_rotate(p);
                    left_rotate(x);
                }
                else
                {
                    right_rotate(x);
                    left_rotate(x);
                }
            }
        }
    }
}

Node bst_find(Node n, int k)
{
    if(n->key == k)
        return n;
    if(n->key > k)
    {
        if(n->left == NULL)
            return NULL;
        else
            return bst_find(n->left, k);
    }
    else
    {
        if(n->right == NULL)
            return NULL;
        else
            return bst_find(n->right, k);
    }
}

Node find(int key)
{
    Node n = bst_find(root, key);
    splay(n, NULL);
    return n;
}

Node bst_insert(Node n, int k)
{
    if(k < n->key)
    {
        if(n->left == NULL)
        {
            n->left == new node(k);
            n->left->father = n;
            return n->left;
        }
        else
            return bst_insert(n->left, k);
    }
    else
    {
        if(n->right == NULL)
        {
            n->right = new node(k);
            n->right->father = n;
            return n->right;
        }
        else
            return bst_insert(n->right, k);
    }
}

void insert(int k)
{
    if(root == NULL)
    {
        root = new node(k);
    }
    else
    {
        Node n = bst_insert(root, k);
        splay(n, NULL);
    }
}

Node findPrev(int k)
{
    find(k);
    Node n = root->left;
    while(n->right)
        n = n->right;
    return n;
}

Node findNext(int k)
{
    find(k);
    Node n = root->right;
    while(n->left)
        n = n->left;
    return n;
}

/*Node findPrev(int k)
{
    Node n = find(k);
    if(n)
    {
        Node l = n->left;
        while(l->key == k)
            l = l->left;
        while(l->right && l->right->key < k)
            l = l->right;
        return l;
    }
    else
    {
        cout << "Find prev error!" << endl;
        return NULL;
    }
}

Node findNext(int k)
{
    Node n = find(k);
    if(n)
    {
        Node r = n->right;
        while(r->key == k)
            r = r->right;
        while(r->left && r->left->key > k)
            r = r->left;
        return r;
    }
    else
    {
        cout << "Find next error!" << endl;
        return NULL;
    }
}*/

void del(int k)
{
    Node prev = findPrev(k);
    Node next = findNext(k);
    splay(prev, NULL);
    splay(next, prev);
    next->left = NULL;
}

void deleteInterval(int a, int b)
{
    if(a <= MIN_K)
        a = MIN_K + 1;
    if(b >= MAX_K)
        b = MAX_K - 1;
    Node aa = bst_find(root, a);
    if(aa == NULL)
        insert(a);
    Node prev = findPrev(a);

    Node bb = bst_find(root, b);
    if(bb == NULL)
        insert(b);
    Node next = findNext(b);

    splay(prev, NULL);
    splay(next, prev);
    if(next != NULL)
        next->left = NULL;
}

void query(int k)
{
    Node p = root;
    int res = 0;
    while(p)
    {
        if(p->key <= k)
        {
            res = p->key;
            p = p->right;
        }
        else
            p = p->left;
    }
    if(res == 0)
        cout << k << endl;
    else
        cout << res << endl;
}

/*int res = 0;
int query(Node n, int k)
{
    if(n->key == k)
        return k;
    if(n->key > k)
    {
        if(n->left == NULL)
            return res;
        else
            return query(n->left, k);
    }
    if(n->right == NULL)
        return n->key;
    else
    {
        res = n->key;
        return query(n-right, k);
    }
}*/


int main()
{
    int n, num, num1;
    char ch;
    insert(MIN_K);
    insert(MAX_K);
    cin >> n;
    while(n--)
    {
        cin >> ch >> num;
        if(ch == 'I')
            insert(num);
        else if(ch == 'Q')
            query(num);
        else if(ch == 'D')
        {
            cin >> num1;
            deleteInterval(num, num1);
        }
    }
    return 0;
}
