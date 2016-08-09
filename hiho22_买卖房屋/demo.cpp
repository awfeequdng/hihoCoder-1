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

/*void update(Node p)
{
    if(p->left != p->right)
    {
        int mid = (p->left + p->right) / 2;
        if(p->set != -1)
        {
            p->lchild->set = p->rchild->set = p->set;
            p->lchild->add = p->rchild->add = 0;

            p->lchild->value = p->set * (p->lchild->right - p->rchild->left + 1);
            p->rchild->value = p->set * (p->rchild->right - p->lchild->left + 1);

            //p->add = 0;
            p->set = -1;
        }

        if(p->add != 0)
        {
            p->lchild->add += p->add;
            p->rchild->add += p->add;

            p->lchild->value += (p->lchild->right - p->lchild->left + 1) * p->add;
            p->rchild->value += (p->rchild->right - p->rchild->left + 1) * p->add;

            p->add = 0;
        }
    }
    else
    {
        if(p->set != -1)
        {
            p->value = p->set;
            p->add = 0;
            p->set = -1;
        }
        if(p->add != 0)
        {
            p->value += p->add;
            p->add = 0;
        }
   }
}*/
void update(Node p)
{
    if(p->left != p->right)
    {
        if(p->set != -1)
        {
            p->value = (p->right - p->left + 1) * p->set;
            p->lchild->set = p->set;
            p->rchild->set = p->set;
            p->lchild->add = 0;
            p->rchild->add = 0;
            p->set = -1;
        }
        if(p->add != 0)
        {
            p->value += p->add * (p->right - p->left + 1);
            p->lchild->add += p->add;
            p->rchild->add += p->add;
            p->add = 0;
        }
    }
}

void makeSet(Node p, int l, int r, int s)
{
    update(p);
    int mid = (p->left + p->right) / 2;
    if(l <= p->left && r >= p->right)
    {
        p->add = 0;
        if(p->left != p->right)
        {
            update(p->lchild);
            update(p->rchild);
            p->lchild->set = s;
            p->rchild->set = s;
        }
        p->value = s * (p->right - p->left + 1);
    }
    else
    {
        if(r <= mid)
        {
            makeSet(p->lchild, l, r, s);
        }
        else if(l > mid)
        {
            makeSet(p->rchild, l, r, s);
        }
        else
        {
            makeSet(p->lchild, l, mid, s);
            makeSet(p->rchild, mid+1, r, s);
        }
        p->value = p->lchild->value + p->rchild->value;
    }
}

void makeAdd(Node p, int l, int r, int d)
{
    update(p);
    int mid = (p->left + p->right) / 2;
    if(l <= p->left && r >= p->right)
    {
        if(p->left != p->right)
        {
            update(p->lchild);
            update(p->rchild);
            p->lchild->add += d;
            p->rchild->add += d;
        }
        p->value += d * (p->right - p->left + 1);
    }
    else
    {
        if(r <= mid)
        {
            makeAdd(p->lchild, l, r, d);
        }
        else if(l > mid)
        {
            makeAdd(p->rchild, l, r, d);
        }
        else
        {
            makeAdd(p->lchild, l, mid, d);
            makeAdd(p->rchild, mid+1, r, d);
        }
        p->value = p->lchild->value + p->rchild->value;
    }
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
        if(oper == 0)
        {
            makeAdd(root, l, r, d);
        }
        else
        {
            makeSet(root, l, r, d);
        }
        cout << root->value << endl;
    }
    return 0;
}
