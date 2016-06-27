#include <iostream>

using namespace std;

typedef struct node
{
    int key;
    struct node *left, *right, *father;
    node() {}
    node(int key_) : key(key_)
    {
        this->left = NULL;
        this->right = NULL;
        this->father = NULL;
    }
}*Node;

//根节点root
Node root = NULL;

//右旋函数
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
    x->right->father = p;
    x->right = p;
    p->father = x;
}

//左旋函数
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
    x->left->father = p;
    x->left = p;
    p->father = x;
}

//Splay函数
void splay(Node x, Node y)
{
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
                    left_rotate(p);
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


