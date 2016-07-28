//二分线段树
#include <iostream>
#define N 10010
using namespace std;

typedef struct node
{
    int left, right, value;
    node *father, *lchild, *rchild;
    node()
    {
        left = right = value = 0;
        father = lchild = rchild = NULL;
    }
    node(int left_, int right_) : left(left_), right(right_)
    {
        value = 0;
        father = NULL;
        lchild = NULL;
        rchild = NULL;
    }
}*Node;

int n, m;
int weight[N];
Node root;

void build(Node p)
{
    if(p->left == p->right)
        return;
    int mid = (p->left + p->right) / 2;
    p->lchild = new node(p->left, mid);
    p->lchild->father = p;
    p->rchild = new node(mid+1, p->right);
    p->rchild->father = p;
    build(p->lchild);
    build(p->rchild);
}

void dfs(Node p)
{
    if(p->left == p->right)
    {
        p->value = weight[p->left];
        return;
    }
    dfs(p->lchild);
    dfs(p->rchild);
    p->value = min(p->lchild->value, p->rchild->value);
}

int query(Node p, int l, int r)
{
    if(l < p->left || r > p->right)
        return -1;
    int mid = p->lchild->right;
    if(l == r)
        return weight[l];
    if(l == p->left)
    {
        if(r < mid)
            return query(p->lchild, l, r);
        else if(r == mid)
            return p->lchild->value;
        else if(mid < r < p->right)
            return min(p->lchild->value, query(p->rchild, mid+1, r));
        else if(r == p->right)
            return p->value;
    }
    else if(p->left < l <= mid)
    {
        if(r <= mid)
            return query(p->lchild, l, r);
        else if(mid < r < p->right)
            return min(query(p->lchild, l, mid), query(p->rchild, mid+1, r));
        else if(r == p->right)
            return min(query(p->lchild, l, mid), p->rchild->value);
    }
    else if(l > mid)
    {
        if(l == mid+1 && r == p->right)
            return p->rchild->value;
        else
            return query(p->rchild, l, r);
    }
    return -1;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> weight[i];

    root = new node(1, n);
    build(root);
    dfs(root);

    int a, b;
    cin >> m;
    while(m--)
    {
        cin >> a >> b;
        cout << query(root, a, b) << endl;
    }
    return 0;
}
