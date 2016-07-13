#include <iostream>
#define MIN 0
#define MAX 100000001
using namespace std;

typedef struct node
{
    int id;
    int val;
    long int totalVal;
    int num;
    int lazy;
    node *father, *left, *right;
    node(int id_, int val_) : id(id_), val(val_)
    {
        totalVal = val;
        num = 1;
        lazy = 0;
        father = NULL;
        left = NULL;
        right = NULL;
    }
}*Node;

Node root = NULL;

void update(Node n)
{
    if(n == NULL)
        return;
    n->num = 1;
    n->totalVal = n->val;

    if(n->left)
    {
        n->num += n->left->num;
        n->totalVal += n->left->totalVal;
    }

    if(n->right)
    {
        n->num += n->right->num;
        n->totalVal += n->right->totalVal;
    }
}

void marking(Node n, int delta)
{
    if(n == NULL)
        return;
    n->lazy = n->lazy + delta;
    n->totalVal = n->totalVal + n->num * delta;
    n->val = n->val + delta;
}

void send(Node n)
{
    if(n->left)
        marking(n->left, n->lazy);
    if(n->right)
        marking(n->right, n->lazy);

    n->lazy = 0;
    update(n);
}

void right_rotate(Node n)
{
    if(n == NULL)
        return;

    Node p = n->father;
    send(p);
    send(n);
    if(p)
    {
        if(p->father)
        {
            n->father = p->father;
            if(p->father->left = p)
                p->father->left = n;
            else
                p->father->right = n;
        }
        else
        {
            root = n;
            //n->father = NULL; //这里非常重要 将root头结点father置为NULL
        }

        p->left = n->right;
        if(n->right)
            n->right->father = p;

        n->right = p;
        p->father = n;

        update(p);
        update(n);
        //cout << "right_rotate" << endl;
    }
}

void left_rotate(Node n)
{
    if(n == NULL)
        return;
    Node p = n->father;
    send(p);
    send(n);
    if(p)
    {
        if(p->father)
        {
            n->father = p->father;
            if(p->father->left == p)
                p->father->left = n;
            else
                p->father->right = n;
        }
        else
        {
            root = n;
            //n->father = NULL; //将root的father置为NULL
        }

        p->right = n->left;
        if(n->left)
            n->left->father = p;

        n->left = p;
        p->father = n;
        update(p);
        update(n);
    }
}

Node bst_insert(Node n, int id, int val)
{
    send(n);
    if(id < n->id)
    {
        if(n->left == NULL)
        {
            n->left = new node(id, val);
            n->left->father = n;
            update(n);
            return n->left;
        }
        else
        {
            Node res = bst_insert(n->left, id, val);
            update(n);
            return res;
        }
    }
    else
    {
        if(n->right == NULL)
        {
            n->right = new node(id, val);
            n->right->father = n;
            update(n);
            return n->right;
        }
        else
        {
            Node res = bst_insert(n->right, id, val);
            update(n);
            return res;
        }
    }
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
                    left_rotate(x);
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

void insert(int id, int val)
{
    if(root == NULL)
        root = new node(id, val);
    else
    {
        Node p = bst_insert(root, id, val);
        splay(p, NULL);
    }
}

Node bst_find(Node n, int id)
{
    if(n->id == id)
        return n;
    else
    {
        if(n->id > id)
        {
            if(n->left == NULL)
                return NULL;
            else
                return bst_find(n->left, id);
        }
        else
        {
            if(n->right == NULL)
                return NULL;
            else
                return bst_find(n->right, id);
        }
    }
}

void find(int id)
{
    Node p = bst_find(root, id);
    splay(p, NULL);
}

Node findPrev(int id)
{
    find(id);
    Node p = root->left;
    while(p->right)
        p = p->right;
    cout << p->id << endl;
    return p;
}

Node findNext(int id)
{
    find(id);
    Node p = root->right;
    while(p->left)
        p = p->left;
    cout << p->id << endl;
    return p;
}

void modify(int a, int b, int d)
{
    Node p = findPrev(a);
    Node n = findNext(b);
    splay(p, NULL);
    splay(n, p);
    if(n->left)
    {
        marking(n->left, d);
        update(n);
        update(p);
    }
}

void del(int a, int b)
{
    Node p = findPrev(a);
    Node n = findNext(b);
    splay(p, NULL);
    splay(n, p);
    if(n)
        n->left = NULL;
    update(n);
    update(p);
}

void query(int a, int b)
{
    Node p = findPrev(a);
    Node n = findNext(b);
    splay(p, NULL);
    splay(n, p);
    if(n->left)
    {
        cout << n->left->totalVal << endl;
    }
    else
        cout << 0 << endl;
}

void MidOrder(Node n)
{
    if(n)
    {
        cout << "Go" << endl;
        MidOrder(n->left);
        cout << n->id << "-" << n->val << "  ";
        MidOrder(n->right);
    }
}

void print(Node r)
{
    if (r == NULL)
    {
        printf("null\n");
        return;
    }
    printf("%d\n",r->id);
    printf("left ");
    print(r->left);
    printf("right ");
    print(r->right);
}

/*int main()
{
    int a, b;
    while(cin >> a >> b)
    {
        insert(a, b);
        print(root);
    }
}*/

int main()
{
    int a, b, d;
    char ch;
    insert(MIN, 0);
    insert(MAX, 0);
    int n;
    cin >> n;
    while(n--)
    {
        print(root);
        cin >> ch >> a >> b;
        if(ch == 'I')
        {
            insert(a, b);
        }
        else if(ch == 'Q')
        {
            query(a, b);
        }
        else if(ch == 'D')
        {
            del(a, b);
        }
        else
        {
            cin >> d;
            modify(a, b, d);
        }
        //MidOrder(root);
        //cout << endl;
    }
    return 0;
}
