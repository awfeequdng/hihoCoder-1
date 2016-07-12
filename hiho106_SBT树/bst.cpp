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

Node insert(Node n, int key)
{
    if(root == NULL)
    {
        root = new node(key);
        return root;
    }
    else
    {
        n->num++;
        if(key < n->key)
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
    }
}

void query(Node n, int cnt)
{
    if(n->num < cnt || cnt <= 0)
        cout < "Error" << endl;
    if(n->left)
    {
        if(n->left->num == cnt - 1)
            cout << n->key <<  endl;
        else
        {
            if(n->left->num > cnt - 1)
                query(n->left, cnt);
            else
                if(n->right)
                    query(n->right, (cnt - n->left->num - 1));
        }
    }
    else if(cnt == 1)
        cout << n->key << endl;
    else
        if(n->right)
            query(n->right, cnt - 1);
}

/*void MidOrder(Node n)
{
    if(n)
    {
        MidOrder(n->left);
        cout << n->key << "-" << n->num <<  " ";
        MidOrder(n->right);
    }
}*/

int main()
{
    int n, num;
    char ch;
    cin >> n;
    while(n--)
    {
        cin >> ch >> num;
        if(ch == 'I')
            insert(root, num);
        else if(ch == 'Q')
            query(root, num);
    }
    return 0;
}
