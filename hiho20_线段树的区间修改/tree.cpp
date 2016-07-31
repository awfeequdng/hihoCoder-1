#include <iostream>
#define N 100010
using namespace std;
int weight[N];

typedef struct node
{
    int left, right, num, sum, lazy;
    node *lchild, *rchild, *father;
    node(int left_, int right_) : left(left_), right(right_)
    {
        num = 1;
        lazy = -1;
        sum = 0;
        lchild = rchild = father = NULL;
    }
}*Node;

Node leaves[N];

void build(Node p)
{
    if(p->left == p->right)
    {
        leaves[p->left] = p;
        p->sum = weight[p->left];
        p->num = 1;
        return;
    }
    else
    {
        int mid = (p->left + p->right) / 2;
        p->lchild = new node(p->left, mid);
        p->rchild = new node(mid+1, p->right);

        build(p->lchild);
        build(p->rchild);
    }

    p->num = p->lchild->num + p->rchild->num;
    p->sum = p->lchild->sum + p->rchild->sum;
}

int query(Node p, int l, int r)
{
    int mid = (p->left + p->right) / 2;
    if(l <= p->left && p->right <= r)
        return p->sum;
    else
    {
        if(p->lazy != -1)
        {
            p->lchild->lazy = p->lazy;
            p->lchild->sum = p->lchild->lazy * p->lchild->num;

            p->rchild->lazy = p->lazy;
            p->rchild->sum = p->rchild->lazy * p->rchild->num;

            p->lazy = -1;
        }
        if(r <= mid)
            return query(p->lchild, l, r);
        else if(l > mid)
            return query(p->rchild, l, r);
        else
            return query(p->lchild, l, mid) + query(p->rchild, mid+1, r);
    }
}

void modify(Node p, int l, int r, int delta)
{
    int mid = (p->left + p->right) / 2;

    if(l <= p->left && r >= p->right)
    {
        p->lazy = delta;
        p->sum = p->num * p->lazy;
    }
    else
    {
        if(p->lazy != -1)
        {
            p->lchild->lazy = p->lazy;
            p->lchild->sum = p->lazy * p->lchild->num;

            p->rchild->lazy = p->lazy;
            p->rchild->sum = p->lazy * p->rchild->num;

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
        p->sum = p->lchild->sum + p->rchild->sum;
    }
}

int main()
{
    int n, m;
    cin >> n;
    Node root = new node(1, n);
    for(int i = 1; i <= n; ++i)
    {
        cin >> weight[i];
    }
    build(root);

    cin >> m;
    int oper, l, r, d;
    while(m--)
    {
        cin >> oper >> l >> r;
        if(oper == 0)
        {
            cout << query(root, l, r) << endl;
        }
        else
        {
            cin >> d;
            modify(root, l, r, d);
        }
    }
    return 0;
}
