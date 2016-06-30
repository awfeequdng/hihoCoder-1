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
    if(x->right)
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
    if(x->left)
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

//插入函数
Node bst_insert(Node n, int key)
{
    Node p = n;
    //初始化root结点
    if(root == NULL)
    {
        root = new node(key);
        return root;
    }
    else
    {
        if(p->key > key)
        {
            if(p->left == NULL)
            {
                p->left = new node(key);
                p->left->father = p;
                return p->left;
            }
            else
                return bst_insert(p->left, key);
        }
        else
        {
            if(p->right == NULL)
            {
                p->right = new node(key);
                p->right->father = p;
                return p->right;
            }
            else
                return bst_insert(p->right, key);
        }
    }
}

void insert(int key)
{
    Node node = bst_insert(root, key);
    if(node)
    {
        splay(node, NULL);
        root = node;
    }
    else
        cout << "Insert error!" << endl;
}

//查找函数
/*
Node bst_find(Node n, int key)
{
    Node p = n;
    if(p->key == key)
        return p;
    else if(p->key < key)
        return bst_find(p->left, key);
    else
        return bst_find(p->right, key);
}*/

Node bst_find(int key)
{
    Node p = root;
    while(p)
    {
        if(p->key == key)
            return p;
        else if(p->key < key)
            p = p->right;
        else
            p = p->left;
    }
    return NULL;
}

Node find(int key)
{
    Node node = bst_find(key);
    if(node)
    {
        splay(node, NULL);
        root = node;
        return node;
    }
    else
    {
        cout << "Find error!" << endl;
        return NULL;
    }
}

//查找前置结点
Node find_prev(int key)
{
    Node node = find(key);
    if(node)
    {
        Node p = node->left;
        while(p->key ==  key)
            p = p->left;
        while(p->right && p->right->key < key)
            p = p->right;
        return p;
    }
    else
    {
        cout << "Find prev error!" << endl;
        return NULL;
    }
}

//查找后置结点
Node find_next(int key)
{
    Node node = find(key);
    if(node)
    {
        Node p = node->right;
        while(p->key == key)
            p = p->right;
        while(p->left && p->left->key > key)
            p = p->left;
        return p;
    }
    else
    {
        cout << "Find next error!" << endl;
        return NULL;
    }
}

//删除结点
void del(int key)
{
    Node prev = find_prev(key);
    Node next = find_next(key);
    splay(prev, NULL);
    splay(next, NULL);
    next->left = NULL;
}

void delete_interval(int a, int b)
{
    Node prev = find_prev(a);
    Node next = find_next(b);
    splay(prev, NULL);
    splay(next, prev);
    next->left = NULL;
}

void query(int key)
{
    Node p = root;
    int res = 0;
    while(p)
    {
        if(p->key <= key)
        {
            res = p->key;
            p = p->right;
        }
        else
            p = p->left;
    }
    cout << res << endl;
}

int main()
{
    int num;
    char ch;
    insert(-999);
    insert(999);
    int n;
    cin >> n;
    while(n--)
    {
        cin >> ch >> num;
        if(ch == 'I')
            insert(num);
        else if(ch == 'Q')
        {
            query(num);
        }
        else if(ch == 'D')
        {
            int num2;
            cin >> num2;
            insert(num);
            insert(num2);
            delete_interval(num, num2);
        }
    }
    return 0;
}
