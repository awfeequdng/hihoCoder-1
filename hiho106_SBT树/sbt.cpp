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
            right_rotate(t->right);
            left_rotate(t);
        }
        else
            return t;
    }
    maintain(t->left, false);
    maintain(t->right, true);
    maintain(t, false);
    maintain(t, true);
}

Node bst_insert(Node n, int key)
{
    if(key < n->key)
    {
        if(n->left == NULL)
        {
            n->left = new node(key);
            n->left->father = n;
        }
        else
            return bst_insert(n->left, key);
    }
    else
    {
        if(n->right == NULL)
        {
            n->right = new node(key);
            return n->right;
        }
        else
            return bst_insert(n->right, key);
    }
}
void insert(int key)
{
    if(root == NULL)
        root = new node(key);
    else
    {
        Node node = bst_insert(root, key);
        maintain(root, key >= root->key);
    }
}

int del(Node t, int key)
{
    int ret = 0;
    t->num -= 1;
    if(key == t->key || (key < t->key && t->left == NULL) || (key > t->key && t->right == NULL))
    {
        ret = t->key;
        if(t->left == NULL || t->right == NULL)
        {
            if(t->left)
                t = t->left;
            else
                t = t->right;
        }
        else
            t->key = del(t->left, t->key + 1);
    }
    else
    {
        if(key < t->key)
            return del(t->left, key);
        else
            return del(t->right, key);
    }
    return ret;
}

Node bst_find(Node node, int key)
{
    if(key == node->key)
        return node;
    if(key < node->key)
    {
        if(node->left == NULL)
            return NULL;
        else
            return bst_find(node->left, key);
    }
    else
    {
        if(node->right == NULL)
            return NULL;
        else
            return bst_find(node->right, key);
    }
}

void query(int key)
{
    Node node = bst_find(root, key);
    cout << node->num << endl;
}

int main()
{
    int n, num;
    char ch;
    cin >> n;
    while(n--)
    {
        cin >> ch >> num;
        if(ch == 'I')
        {
            insert(num);
            if(!root)
                cout << "Root is NULL" << endl;
        }
        else if(ch == 'Q')
            query(num);
    }
    return 0;
}
