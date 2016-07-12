#include <iostream>
using namespace std;

typedef struct node
{
    int id;
    int val;
    int totalVal;
    int num;
    int lazy;
    node *father, *left, *right;
    node(int id_, int val_) : id(id_), val(val_)
    {
        totalVal = val;
        num = 1;
        lazy = 0;
        father = NULL;
        left = NULL;
        right = NULL;
    }
}*Node;

Node root = NULL;

void update(Node n)
{
    n->num = 1;
    n->totalVal = n->val;

    if(n->left)
    {
        n->num += n->left->num;
        n->totalVal += n->left->totalVal;
    }

    if(n->right)
    {
        n->num += n->right->num;
        n->totalVal += n->right->totalVal;
    }
}

void marking(Node n, int delta)
{
    n->lazy = n->lazy + delta;

    n->totalVal = n->totalVal + n->num * delta;
    n->val = n->val + delta;
}

void send(Node n)
{
    if(n->left)
        marking(n->left, n->lazy);
    if(n->right)
        marking(n->right, n->lazy);

    n->lazy = 0;
    update(n);
}

void right_rotate(Node n)
{
    if(n == NULL)
        return;

    Node p = n->father;
    send(p);
    send(n);
    if(p)
    {
        if(p->father)
        {
            n->father = p->father;
            if(p->father->left = p)
                p->father->left = n;
            else
                p->father->right = n;
        }
        else
            root = n;

        p->left = n->right;
        if(n->right)
            n->right->father = p;

        n->right = p;
        p->father = n;

        update(p);
        update(n);
    }
}

void left_rotate(Node n)
{
    if(n == NULL)
        return;
    Node p = n->father;
    send(p);
    send(n);
    if(p)
    {
        if(p->father)
        {
            n->father = p->father;
            if(p->father->left == p)
                p->father->left = n;
            else
                p->father->right = n;
        }
        else
            n = root;

        p->right = n->left;
        if(n->left)
            n->left->father = p;

        p->father = n;
        n->left = p;
        update(p);
        update(n);
    }
}

Node bst_insert(Node n, int id, int val)
{
    send(n);
    if(id < n->id)
    {
        if(n->left == NULL)
        {
            n->left = new node(id, val);
            n->left->father = n;
            update(n);
            return n->left;
        }
        else
        {
            Node res = bst_insert(n->left, id, val);
            update(n->left);
            return res;
        }
    }
    else
    {
        if(n->right == NULL)
        {
            n->right = new node(id, val);
            n->right->father = n;
            update(n);
            return n->right;
        }
        else
        {
            Node res = bst_insert(n->right, id, val);
            update(n->right);
            return res;
        }
    }
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
                if(g->left == x)
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

void insert(int id, int val)
{
    if(root == NULL)
        root = new node(id, val);
    else
    {
        Node p = bst_insert(root, id, val);
        splay(p, NULL);
    }
}

void MidOrder(Node n)
{
    if(n)
    {
        MidOrder(n->left);
        cout << n->id << "-" << n->val << "\t";
        MidOrder(n->right);
    }
}

int main()
{
    int id, val;
    while(cin >> id >> val)
    {
        insert(id, val);
        MidOrder(root);
        cout << endl;
    }
    return 0;
}
