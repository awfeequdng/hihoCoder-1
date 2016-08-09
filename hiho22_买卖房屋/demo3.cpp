#include <iostream>
#define N 100010
using namespace std;

int price[N];

typedef struct node
{
    int left, right, value;
    int set, add;
    node *lchild, *rchild;
    node(int left_, int right_) : left(left_), right(right_)
    {
        set = -1;
        add = 0;
        lchild = rchild = NULL;
    }
}*Node;

Node root = NULL;

void build(Node p)
{
    if(p->left == p->right)
    {
        p->value = price[p->left];
    }
    else
    {
        int mid = (p->left + p->right) / 2;
        p->lchild = new node(p->left, mid);
        p->rchild = new node(mid+1, p->right);
        build(p->lchild);
        build(p->rchild);
        p->value = p->lchild->value + p->rchild->value;
    }
}

void pushDown(Node p)
{
    if(p->set != -1)
    {
        if(p->lchild)
        {
            p->lchild->set = p->set;
            p->lchild->add = 0;
            p->lchild->value = p->set * (p->lchild->right - p->lchild->left + 1);

            p->rchild->set = p->set;
            p->rchild->add = 0;
            p->rchild->value = p->set * (p->rchild->right - p->rchild->left + 1);
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

void modify(Node p, int l, int r, int d, int type)
{
    if(l == p->left && r == p->right)
    {
        if(type == 0)
        {
            p->add += d;
            p->value += d * (r - l + 1);
        }
        else
        {
            p->set = d;
            p->value = d * (r - l + 1);
            p->add = 0;
        }
        return;
    }

    int mid = (p->left + p->right) / 2;
    pushDown(p);
    if(l > mid)
    {
        modify(p->rchild, l, r, d, type);
    }
    else if(r <= mid)
    {
        modify(p->lchild, l, r, d, type);
    }
    else
    {
        modify(p->lchild, l, mid, d, type);
        modify(p->rchild, mid+1, r, d, type);
    }
    p->value = p->lchild->value + p->rchild->value;
}

int main()
{
    int n, m;
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
        modify(root, l, r, d, oper);
        cout << root->value << endl;
    }
    return 0;
}
