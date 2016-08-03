#include <iostream>
#include <map>
#define N 100010
using namespace std;
int n, len;
map<int, int> query;

typedef struct node
{
    int val;
    int index;
    node *father, *lchild, *rchild;
    node(int val_) : val(val_)
    {
        index = -1;
        father = lchild = rchild = NULL;
    }
}*Node;

typedef struct snode
{
    int left, right, value, lazy;
    snode *father, *lchild, *rchild;
    snode(int left_, int right_) : left(left_), right(right_)
    {
        value = 0;
        lazy = -1;
        father = lchild = rchild = NULL;
    }
}*Snode;


Node root = NULL;
Snode sroot = NULL;
int index = 0;
int num[2 * N];
Node res[2 * N];

void insert(Node p, int n)
{
    if(root == NULL)
    {
        root = new node(n);
        return;
    }
    else
    {
        if(n < p->val)
        {
            if(p->lchild == NULL)
            {
                p->lchild = new node(n);
                p->lchild->father = p;
            }
            else
                insert(p->lchild, n);
        }
        else
        {
            if(p->rchild == NULL)
            {
                p->rchild = new node(n);
                p->rchild->father = p;
            }
            else
                insert(p->rchild, n);
        }
    }
}

void midOrder(Node p)
{
    if(p)
    {
        midOrder(p->lchild);
        num[index++] = p->val;
        midOrder(p->rchild);
    }
}

void build(Snode p)
{
    if(p->left == p->right)
    {
        res[p->left] = p;
        p->value = 0;
        return;
    }
    else
    {
        int mid = (p->left + p->right) / 2;
        p->lchild = new snode(p->left, mid);
        p->rchild = new snode(mid+1, p->right);

        build(p->lchild);
        build(p->rchild);
    }
}

void modify(Snode p, int l, int r, int delta)
{
    int mid = (p->left + p->right) / 2;
    if(l <= p->left && r >= p->right)
    {
        p->lazy = delta;
        p->val = delta;
    }
    else
    {
        if(p->lazy != -1)
        {
            p->lchild->lazy = p->lazy;
            p->lchild->val = p->lazy;

            p->rchild->lazy = p->lazy;
            p->rchild->val = p->lazy;

            p->lazy = -1;
        }
        if(r <= mid)
            modify(p->lchild, l, r, delta);
        else if(l > mid)
            modify(p->rchild, l, r, delta);
        else
        {
            modify(p->lchild, l, mid, delta);
            modify(p->rchild, mid+1, r, delta);
        }
    }
}

int main()
{
    int left, right;
    cin >> n >> len;
    for(int i = 0; i < n; ++i)
    {
        cin >> left >> right;
        query.insert(make_pair(left, right));
        insert(root, left);
        insert(root, right);
    }

    midOrder(root);

    return 0;
}

