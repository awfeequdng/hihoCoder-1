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

void right_rotatt(Node n)
{
    if(n == NULL)
        return;

    Node p = n->father;
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

int main()
{
    return 0;
}
