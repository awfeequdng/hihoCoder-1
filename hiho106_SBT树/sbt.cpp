#include <iostream>
using namespace std;

typedef struct node
{
    int key;
    int num;
    node *father, *left, *right;
    node()
    {
        num = 1;
        father = NULL;
        left = NULL;
        right = NULL;
    }
    node(int key_) : key(key_)
    {
        num = 1;
        father = NULL;
        left = NULL;
        right = NULL;
    }
}*Node;

Node root = NULL;

void right_rotate(Node &t)
{
    Node k = t->left;
    t->left = k->right;
    k->right = t;
    k->num = t->num;
    t->num = t->left->num + t->right->num + 1;
    t = k;
}

void left_rotate(Node &t)
{
    Node k = t->right;
    t->right = k->left;
    k->left = t;
    k->num =t->num;
    t->num = t->left->num + t->right->num + 1;
    t = k;
}

Node maintain(Node t, bool flag)
{
    if(!flag)
    {
        if(t->left->left->num > t->right->num)
            right_rotate(t);
        else if(t->left->right->num > t->right->num)
        {
            left_rotate(t->left);
            right_rotate(t);
        }
        else
            return t;
    }
    else
    {
        if(t->right->right->num > t->left->num)
            left_rotate(t);
        else if(t->right->left->num > t->left->num)
        {
            right_rotate(t->right->num);
            left_rotate(t);
        }
        else
            return;
    }
    maintain(t->left, false);
    maintain(t->right, true);
    maintain(t, false);
    maintain(t, true);
}

Node insert(Node t, int key)
{
    if(t == NULL)
        t = new node(key);
    else
    {
        t->num += 1;
        if(key < t->key)
            t->left = insert(t->left, key);
        else
            t->right = insert(t->right, key);
        maintain(t, key >= t->key);
    }
    return t;
}

int delete(Node t, int key)
{
    t->num -= 1;
    if(key == t->key || (key < t->key && t->left == NULL) || (key > t->key && t->right == NULL))
    {
        int ret = t->key;
        if(t->left == NULL || t->right == NULL)
        {
            if(t->left)
                t = t->left;
            else
                t = t->right;
        }
        else
            t->key = delete(t->left, t->key + 1);
    }
    else
    {
        if(key < t->key)
            return delete(t->left, key);
        else
            return delete(t->right, key);
    }
    return ret;
}

