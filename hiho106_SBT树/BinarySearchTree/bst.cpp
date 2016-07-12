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

void PreOrder2()
{
    stack<Node> s;
    Node p = root;
    while(p || !s.empty())
    {
        while(p)
        {
            cout << p->data << " ";
            s.push(p);
            p = p->left;
        }
        if(!s.empty())
        {
            p = s.top();
            s.pop();
            p = p->right;
        }
    }
}

void MidOrder2()
{
    stack<Node> s;
    Node p = root;
    while(p || !s.empty())
    {
        while(p)
        {
            s.push(p);
            p = p->left;
        }
        if(!s.empty())
        {
            p = s.top();
            s.pop();
            cout << p->data << " ";
            p = p->right;
        }
    }
}

void PosrOrder2()
{
    stack<Node> s;
    Node pre, cur;
    s.push(root);
    while(!s.empty())
    {
        cur = s.top();
        if((cur->left == NULL && cur->right == NULL) || (pre && (pre == cur->left || pre == cur->right)))
        {
            cout << cur->data << " ";
            s.pop();
            pre = cur;
        }
        else
        {
            if(cur->right)
                s.push(cur->right);
            if(cur->left)
                s.push(cur->left);
        }
    }
}

int main()
{
    int num;
    while(cin >> num)
    {
        insert(root, num);
    }
    cout << "前序遍历：" <<  endl;
    PreOrder(root);
    cout << endl;
    PreOrder2();
    cout << endl;

    cout << "中续遍历：" << endl;
    MidOrder(root);
    cout << endl;
    MidOrder2();
    cout << endl;

    cout << "后续遍历：" << endl;
    PosrOrder(root);
    cout << endl;
    PosrOrder2();
    cout << endl;

    return 0;
}
