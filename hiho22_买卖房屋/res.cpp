#include <iostream>
#define N 100010
using namespace std;
int price[N];

typedef struct node
{
    int left, right, value, set, add;
    node *lchild, *rchild;
    node(int left_, int right_) : left(left_), right(right_)
    {
        set = -1;
        add = 0;
        lchild = rchild = NULL;
    }
}*Node;

void build(Node p)
{
    if(p->left == p->right)
    {
        p->value = price[p->left];
    }
    else
    {
        int mid = (p->right + p->left) / 2;
        p->lchild = new node(p->left, mid);
        p->rchild = new node(mid+1, p->right);
        build(p->lchild);
        build(p->rchild);
        p->value = p->lchild->value + p->rchild->value;
    }
}

Node root = NULL;

void pushDown(Node p)
{
    if(p->set != -1)
    {
        if(p->lchild)
        {
            p->lchild->set = p->set;
            p->lchild->add = 0;
            p->lchild->value = (p->lchild->right - p->lchild->left + 1) * p->set;

            p->rchild->set = p->set;
            p->rchild->add = 0;
            p->rchild->value = (p->rchild->right - p->rchild->left + 1) * p->set;
        }
        p->set = -1;
    }
    if(p->add != 0)
    {
        if(p->lchild)
        {
            p->lchild->add += p->add;
            p->lchild->value += p->add * (p->lchild->right - p->lchild->left + 1);
            p->rchild->add += p->add;
            p->rchild->value += p->add * (p->rchild->right - p->rchild->left + 1);
        }
        p->add = 0;
    }
}

void modify(Node p, int oper, int l, int r, int d)
{
    if(l == p->left && r == p->right)
    {
        if(oper == 0)
        {
            p->add += d;
            p->value += (p->right - p->left + 1) * d;
        }
        else
        {
            p->set = d;
            p->add = 0;
            p->value = (p->right - p->left + 1) * d;
        }
        return;
    }

    int mid = (p->right + p->left) / 2;
    pushDown(p);
    if(r <= mid)
    {
        modify(p->lchild, oper, l, r, d);
    }
    else if(l > mid)
    {
        modify(p->rchild, oper, l, r, d);
    }
    else
    {
        modify(p->lchild, oper, l, mid, d);
        modify(p->rchild, oper, mid+1, r, d);
    }
    p->value = p->lchild->value + p->rchild->value;
}

int main()
{
    int m, n;
    cin >> n >> m;
    for(int i = 0; i <= n; ++i)
    {
        cin >> price[i];
    }

    root = new node(0, n);
    build(root);

    int oper, l, r, d;
    while(m--)
    {
        cin >> oper >> l >> r >> d;
        modify(root, oper, l, r, d);
        cout << root->value << endl;
    }
    return 0;
}
