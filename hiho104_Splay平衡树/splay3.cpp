#include <iostream>
using namespace std;
#define MIN_K 0
#define MAX_K 1000000001

typedef class node
{
    public:
        int key;
        node *father, *left, *right;
        node(int key_) : key(key_)
        {
            father = NULL;
            left = NULL;
            right = NULL;
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
    while(x->father != y)
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
                    right_rotate(x);
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

Node bst_find(Node node, int key)
{
    if(key == node->key)
        return node;
    if(key < node->key)
    {
        if(node->left == NULL)
            return NULL;
        else
            return bst_find(node->left, key);
    }
    else
    {
        if(node->right == NULL)
            return NULL;
        else
            return bst_find(node->right, key);
    }
}

void find(int key)
{
    Node node = bst_find(root, key);
    splay(node, NULL);
}

Node bst_insert(Node n, int key)
{
    if(key < n->key)
    {
        if(n->left == NULL)
        {
            n->left = new node(key);
            n->left->father = n;
            return n->left;
        }
        else
            return bst_insert(n->left, key);
    }
    else
    {
        if(n->right == NULL)
        {
            n->right = new node(key);
            n->right->father = n;
            return n->right;
        }
        else
            return bst_insert(n->right, key);
    }
}

void insert(int key)
{
    if(root == NULL)
        root = new node(key);
    else
    {
        Node node = bst_insert(root, key);
        splay(node, NULL);
    }
}

Node findPrev(int key)
{
    find(key);
    Node node = root->left;
    while(node->right)
        node = node->right;
    return node;
}

Node findNext(int key)
{
    find(key);
    Node node = root->right;
    while(node->left)
        node = node->left;
    return node;
}

void del(int key)
{
    Node prev = findPrev(key);
    Node next = findNext(key);
    splay(prev, NULL);
    splay(next, prev);
    next->left = NULL;
}

void deleteInterval(int a, int b)
{
    if(a < MIN_K)
        a = MIN_K + 1;
    if(b > MAX_K)
        b = MAX_K - 1;

    Node aa =  bst_find(root, a);
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

/*void query(int key)
{
    Node p = root;
    int res = 0;
    while(p)
    {
        if(p->key <= key)
        {
            res = p->key;
            p = p->right;
        }
        else
            p = p->left;
    }
    cout << res << endl;
}*/
int res;
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
        return query(n->right, k);
    }
}

int main()
{
    int num;
    char ch;
    int n;
    cin >> n;
    insert(MIN_K);
    insert(MAX_K);
    while(n--)
    {
        cin >> ch >> num;
        if(ch == 'I')
            insert(num);
        else if(ch == 'Q')
            cout << query(root, num) << endl;
        else if(ch == 'D')
        {
            int num2;
            cin >> num2;
            deleteInterval(num, num2);
        }
    }
    return 0;
}
