#include <iostream>
using namespace std;

typedef struct node
{
    int key;
    int num;
    node *father, *left, *right;
    node(int key_) : key(key_)
    {
        num = 1;
        father = NULL;
        left = NULL;
        right = NULL;
    }
}*Node;

Node root = NULL;

void right_rotate(Node &n)
{
    if(n == NULL)
        return;
    Node k = n->left;
    if(k)
    {
        Node p = n->father;
        k->father = n->father;
        if(p)
        {
            if(p->left == n)
                p->left = k;
            else
                p->right = k;
        }
        else
            k = root;

        n->left = k->right;
        if(k->right)
            k->right->father = n;

        k->right = n;
        n->father = k;

        k->num = n->num;

        if(n->right && n->left)
            n->num = n->right->num + n->left->num + 1;
        else if(n->right)
            n->num = n->right->num + 1;
        else if(n->left)
            n->num = n->left->num + 1;
        else
            n->num = 1;

        n = k;
    }
}

void left_rotate(Node &n)
{
    if(n == NULL)
        return;
    Node k = n->right;
    if(k)
    {
        Node p = n->father;
        if(p)
        {
            if(p->left == n)
                p->left = k;
            else
                p->right = k;
        }
        else
            root = k;

        n->right = k->left;
        if(k->left)
            k->left->father = n;

        k->left = n;
        n->father = k;

        k->num = n->num;

        if(n->left && n->right)
            n->num = n->left->num + n->right->num + 1;
        else if(n->left)
            n->num = n->left->num + 1;
        else if(n->right)
            n->num = n->right->num + 1;
        else
            n->num = 1;

        n = k;
    }
}

void maintain(Node n, bool flag)
{
    if(n == NULL)
        return;
    if(!flag)
    {
        if(n->left)
        {
            if(n->left->left && (!n->right || n->left->left->num > n->right->num))
                right_rotate(n);
            else if(n->left->right && (!n->right || n->left->right->num > n->right->num))
            {
                left_rotate(n->left);
                right_rotate(n);
            }
        }
        else
            return;
    }
    else
    {
        if(n->right)
        {
            if(n->right->right && (!n->left || n->right->right->num > n->left->num))
                left_rotate(n);
            else if(n->right->left && (!n->left || n->right->left->num > n->left->num))
            {
                right_rotate(n->right);
                left_rotate(n);
            }
        }
        else
            return;
    }
    maintain(n->left, false);
    maintain(n->right, true);
    maintain(n, false);
    maintain(n, true);
}

Node insert(Node n, int key)
{
    if(root == NULL)
    {
        root = new node(key);
        return root;
    }
    else
    {
        n->num += 1;
        if(n->key > key)
        {
            if(n->left == NULL)
            {
                n->left = new node(key);
                n->left->father = n;
                return n->left;
            }
            else
                return insert(n->left, key);
        }
        else
        {
            if(n->right == NULL)
            {
                n->right = new node(key);
                n->right->father = n;
                return n->right;
            }
            else
                return insert(n->right, key);
        }
        maintain(n, key >= n->key);
    }
}

void query(Node p, int key)
{
    if(p->num < key)
        return;
    if(p->left)
    {
        if(p->left->num == key - 1)
            cout << p->key << endl;
        else if(p->left->num < key - 1)
            query(p->right, key - p->left->num - 1);
        else
            query(p->left, key);
    }
    else
    {
        if(key == 1)
            cout << p->key << endl;
        else
            query(p->right, key - 1);
    }
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
            insert(root, num);
        }
        else if(ch == 'Q')
            query(root, num);
    }
    return 0;
}
