#include <iostream>
#include <math.h>

using namespace std;

typedef struct node
{
    int key;
    int weight;
    struct node *father, *left, *right;
    node() {}
    node(int key_, int weight_) : key(key_), weight(weight_) {this->left = NULL; this->right = NULL;}
}*Node;


//左旋函数
void left_rotate(Node a)
{
    Node b = a->right;
    b->father = a->father;
    if(a->father->left == a)
        a->father->left = b;
    else
        a->father->right = b;
    b->left->father = a;
    a->right = b->left;
    a->father = b;
    b->left = a;
}

//右旋函数
void right_rotate(Node a)
{
    Node b = a->left;
    b->father = a->father;
    if(a->father->left == a)
        a->father->left = b;
    else
        a->father->right = b;
    b->right->father = a;
    a->left = b->right;
    a->father = b;
    b->right = a;
}

//插入结点
Node insert(Node n, int key)
{
    if(key < n->key)
    {
        if(n->left == NULL)
        {
            n->left = new node(key, random() % 1000);
            return n->left;
        }
        else
            return insert(n->left, key);
    }
    else
    {
        if(n->right == NULL)
        {
            n->right = new node(key, random() % 1000);
            return n->right;
        }
        else
            return insert(n->right, key);
    }
}

//旋转结点
void rotate(Node node)
{
    while(node->father)
    {
        Node fa = node->father;
        if(node->weight < fa->weight)
        {
            if(node == fa->left)
                right_rotate(node);
            else
                left_rotate(node);
        }
        else
            break;
    }
}


int main()
{
    Node root = NULL;
    int n;
    int num;
    char ch;
    cin >> num;
    while(n--)
    {
        cin >> ch;
        cin >> num;
        if(ch == 'I')
        {
            if(root == NULL)
                root = new node(num, random() % 1000);
            else
                rotate(insert(root, num));
        }
        else if(ch == 'Q')
        {
            query(num);
        }
    }
    return 0;
}
