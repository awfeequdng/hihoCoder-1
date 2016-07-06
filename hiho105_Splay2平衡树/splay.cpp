#include <iostream>
using namespace std;

typedef class node
{
    public:
        int id;
        int val;
        int totalVal;
        int num;
        int lazy;
        node *father, *left, *right;
        node()
        {
            id = val = totalVal = num = lazy = 0;
            this->father = this->left = this->right = NULL;
        }
        node(int id_, int val_) : id(id_), val(val_)
        {
            totalVal = this->val;
            num = 1;
            lazy = 0;
            this->father = this->left = this->right = NULL;
        }
}*Node;

Node root = NULL;

void marking(Node node, int delta)
{
    node->lazy = node->lazy + delta;
    node->totalVal = node->totalVal + node->num * delta;
    node->val = node->val + delta;
}

void update(Node x)
{
    x->num = 1;
    x->totalVal = x->val;

    if(x->left)
    {
        x->num = x->num + x->left->num;
        x->totalVal = x->totalVal + x->left->totalVal;
    }

    if(x->right)
    {
        x->num = x->num + x->right->num;
        x->totalVal = x->totalVal + x->right->totalVal;
    }
}

void send(Node node)
{
    if(node->left)
        marking(node->left, node->lazy);
    if(node->right)
        marking(node->right, node->lazy);

    node->lazy = 0;
    update(node);
}

void right_rotate(Node x)
{
    Node p = x->father;
    send(p);
    send(x);
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
    update(p);
    update(x);
}

void left_rotate(Node x)
{
    Node p = x->father;
    send(p);
    send(x);
    x->father = p->father;
    if(p->father)
    {
        if(p->father->left = p)
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
    update(p);
    update(x);
}

void splay(Node x, Node y)
{
    if(x == NULL)
        return;
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
                if(p->left == p)
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
                    left_rotate(x);
                }
                else
                {
                    right_rotate(x);
                    right_rotate(x);
                }
            }
        }
    }
}

Node bst_find(Node node, int id)
{
    if(id == node->id)
        return node;
    if(id < node->id)
    {
        if(node->left == NULL)
            return NULL;
        else
            return bst_find(node->left, id);
    }
    else
    {
        if(node->right == NULL)
            return NULL;
        else
            return bst_find(node->right, id);
    }
}

void find(int id)
{
    Node node = bst_find(root, id);
    splay(node, NULL);
}

Node bst_insert(Node n, int id, int val)
{
    send(root);
    if(id < n->id)
    {
        if(n->left == NULL)
        {
            n->left = new node(id, val);
            n->left->father = n;
            return n->left;
        }
        else
            return bst_insert(n->left, id, val);
    }
    else
    {
        if(n->right == NULL)
        {
            n->right = new node(id, val);
            n->right->father = n;
            return n->right;
        }
        else
            return bst_insert(n->right, id, val);
    }
    update(n);
}

void insert(int id, int val)
{
    if(root == NULL)
        root = new node(id, val);
    else
    {
        Node node = bst_insert(root, id, val);
        splay(node, NULL);
    }
}

/*Node findPrev(int id)
{
    find(id);
    Node n = root;
    if(n)
    {
        Node l = n->left;
        while(l->id == id)
            l = l->left;
        while(l->right && l->right->id < id)
            l = l->right;
        return l;
    }
    else
    {
        cout << "Find prev error!" << endl;
        return NULL;
    }
}

Node findNext(int id)
{
    find(id);
    Node n = root;
    if(n)
    {
        Node r = n->right;
        while(r->id == id)
            r = r->right;
        while(r->left && r->left->id > id)
            r = r->left;
        return r;
    }
    else
    {
        cout << "Find next error!" << endl;
        return NULL;
    }
}*/

Node findPrev(int id)
{
    find(id);
    Node node = root->left;
    while(node->right)
        node = node->right;
    return node;
}

Node findNext(int id)
{
    find(id);
    Node node = root->right;
    while(node->left)
        node = node->right;
    return node;
}

void del(int id)
{
    Node prev = findPrev(id);
    Node next = findNext(id);
    splay(prev, NULL);
    splay(next, prev);
    next->left = NULL;
}

void deleteInterval(int a, int b)
{
    Node prev = findPrev(a);
    Node next = findNext(b);

    splay(prev, NULL);
    splay(next, prev);
    if(next != NULL)
        next->left = NULL;
    update(next);
    update(prev);
}

void query(int a, int b)
{
    Node prev = findPrev(a);
    cout << prev->id << endl;
    Node next = findNext(b);
    cout << next->id << endl;
    splay(prev, NULL);
    splay(next, prev);
    if(next->left)
        cout << next->left->totalVal << endl;
}

void modefy(int a, int b, int d)
{
    Node prev = findPrev(a);
    Node next = findNext(b);
    splay(prev, NULL);
    splay(next, prev);
    marking(next->left, d);
}

int main()
{
    int a, b, d;
    char ch;
    int n;
    cin >> n;
    while(n--)
    {
        cin >> ch >> a >> b;
        if(ch == 'I')
            insert(a, b);
        else if(ch == 'Q')
            query(a, b);
        else if(ch == 'M')
        {
            cin >> d;
            modefy(a, b, d);
        }
        else if(ch == 'D')
            deleteInterval(a, b);
    }
    return 0;
}
