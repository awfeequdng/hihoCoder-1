#include <iostream>
#include <map>
#define N 100010
using namespace std;
int n, len;
map<int, int> query;

typedef struct node
{
    int val;
    node *father, *lchild, *rchild;
    node(int val_) : val(val_)
    {
        father = lchild = rchild = NULL;
    }
}*Node;

Node root = NULL;
int index = 0;
int num[2 * N];

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
        cout << p->val << " ";
        num[index++] = p->val;
        midOrder(p->rchild);
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
    cout << endl;
    for(int i = 0; i < 2 * n; ++i)
    {
        cout << num[i] << " ";
    }
    cout << endl;
    return 0;
}

