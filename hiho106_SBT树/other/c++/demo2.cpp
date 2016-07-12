#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

//平衡树size balanced tree

struct node
{
    node(int k,node* n)
    {
        father = n;
        left = right = NULL;
        key = k;
        sumNodes = 1;//以自己为根所有节点个数，包括自己
    }
    int key, sumNodes;
    node *father, *left, *right;
}*root;
void left_rotate(node* a)
{
    if (a != NULL)
    {
        node* k = a->right;
        if (k != NULL)
        {
            a->right = k->left;
            if (k->left)
                k->left->father = a;

            k->left = a;
            if (a->father == NULL)
                root = k;
            else
            {
                if (a->father->left == a)
                    a->father->left = k;
                else
                    a->father->right = k;
            }
            k->father = a->father;
            a->father = k;
            k->sumNodes = a->sumNodes;

            int sumleft = 0, sumright = 0;
            if (a->left)
                sumleft = a->left->sumNodes;
            if (a->right)
                sumright = a->right->sumNodes;
            a->sumNodes = sumleft + sumright + 1;
        }
    }
}
void right_rotate(node* a)
{
    if (a != NULL)
    {
        node* k = a->left;
        if (k != NULL)
        {
            a->left = k->right;
            if (k->right)
                k->right->father = a;

            k->right = a;
            if (a->father == NULL)
                root = k;
            else
            {
                if (a->father->left == a)
                    a->father->left = k;
                else
                    a->father->right = k;
            }
            k->father = a->father;
            a->father = k;
            k->sumNodes = a->sumNodes;

            int sumleft = 0, sumright = 0;
            if (a->left)
                sumleft = a->left->sumNodes;
            if (a->right)
                sumright = a->right->sumNodes;
            a->sumNodes = sumleft + sumright + 1;
        }
    }
}
void maintain(node* n, bool flag)
{
    if (n == NULL) return;
    if (flag == false)
    {
        if (n->left)
        {
            if (n->left->left && (!(n->right) || n->left->left->sumNodes > n->right->sumNodes))
                right_rotate(n);
            else if (n->left->right && (!(n->right) || n->left->right->sumNodes > n->right->sumNodes))
            {
                left_rotate((n->left));
                right_rotate(n);
            }
            else return;
        }
        else return;
    }
    else
    {
        if (n->right)
        {
            if (n->right->right && (!(n->left) || n->right->right->sumNodes > n->left->sumNodes))
                left_rotate(n);
            else if (n->right->left && (!(n->left) || n->right->left->sumNodes > n->left->sumNodes))
            {
                right_rotate((n->right));
                left_rotate(n);
            }
            else return;
            }
        else return;
    }
    maintain(n->left, false);
    maintain(n->right, true);
    maintain(n, false);
    maintain(n, true);
}

void bst_insert(node* n, int key)
{
    n->sumNodes = n->sumNodes + 1;
    if (key < n->key)
    {
        if (n->left == NULL)
            n->left = new node(key, n);
        else
            bst_insert(n->left, key);
    }
    else
    {
        if (n->right == NULL)
            n->right = new node(key, n);
        else
            bst_insert(n->right, key);
    }
    maintain(n, key >= n->key);
}
void insert(int key)
{
    if (root == NULL)
        root = new node(key, NULL);
    else
        bst_insert(root, key);
}

int Q(node* n, int k)
{
    if (k > n->sumNodes)
        return -1;//不会出现
    if (n->left != NULL)
    {
        int num = n->left->sumNodes + 1;
        if (k == num)
            return n->key;
        else if (k < num)
            return Q(n->left, k);
        else if (k > num)
            return Q(n->right, k - num);
    }
    else if (n->right != NULL)
    {
        if (k == 1)
            return n->key;
        else
            return Q(n->right, k - 1);
    }
    else
        return n->key;
}
void print(node* r) {
    if (r == NULL) {
        printf("null\n");
        return;
    }
    printf("%d\n", r->key);
    printf("left ");
    print(r->left);
    printf("right ");
    print(r->right);
}

int main()
{
    int n, k;
    char c;
    cin >> n;
    while (n--)
    {
        cin >> c >> k;
        if (c == 'I')
            insert(k);//, print(root);
        else if (c == 'Q')
            cout << Q(root, k) << endl;
    }
    return 0;
}