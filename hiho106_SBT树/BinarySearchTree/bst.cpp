#include <iostream>
#include <stack>
using namespace std;

typedef struct node
{
    int data;
    node *left, *right, *father;
    node(int data_) : data(data_)
    {
        left = NULL;
        right = NULL;
        father = NULL;
    }
}*Node;

Node root = NULL;

Node insert(Node n, int data)
{
    if(root == NULL)
    {
        root = new node(data);
        return root;
    }
    else if(data < n->data)
    {
        if(n->left == NULL)
        {
            n->left = new node(data);
            n->left->father = n;
            return n->left;
        }
        else
            return insert(n->left, data);
    }
    else
    {
        if(n->right == NULL)
        {
            n->right = new node(data);
            n->right->father = n;
            return n->right;
        }
        else
            return insert(n->right, data);
    }
}

void PreOrder(Node n)
{
    if(n)
    {
        cout << n->data << " ";
        PreOrder(n->left);
        PreOrder(n->right);
    }
}

void MidOrder(Node n)
{
    if(n)
    {
        MidOrder(n->left);
        cout << n->data << " ";
        MidOrder(n->right);
    }
}

void PosrOrder(Node n)
{
    if(n)
    {
        PosrOrder(n->left);
        PosrOrder(n->right);
        cout << n->data << " ";
    }
}

int main()
{
    int num;
    while(cin >> num)
    {
        insert(root, num);
    }
    cout << "前序遍历：";
    PreOrder(root);
    cout << endl;
    cout << "中续遍历：";
    MidOrder(root);
    cout << endl;
    cout << "后续遍历：";
    PosrOrder(root);
    cout << endl;
    return 0;
}
