#include <iostream>
#include <memory>
#include <stack>
#define SIZE 105
using namespace std;

struct Node
{
    Node *left;
    Node *right;
    Node *up;
    Node *down;
    int x, y;
    Node(){ }
    Node(Node *left_, Node *right_, Node *up_, Node *down_, int x_, int y_) : left(left_), right(right_), up(up_), down(down_), x(x_), y(y_) { }
};

int n, m;
int board[SIZE][SIZE];
int id[SIZE][SIZE];
Node *head = NULL;
Node *columnHead[SIZE];
Node *node[SIZE];

void build()
{
    if(head == NULL)
    {
        head = new Node(head, head, head, head, 0, 0);
    }
    auto pre = head;
    for(int i = 0; i < m; ++i)
    {
        columnHead[i] = new Node();
        auto p = columnHead[i];
        p->up = p->down = p;
        p->x = 0;
        p->y = i;
        p->right = pre->right;
        p->left = pre;
        pre->right->left = p;
        pre->right = p;
        pre = p;
    }
    int count = 0;
    for(int i = 1; i < n; ++i)
    {
        for(int j = 1; j < m; ++j)
        {
            if(board[i][j] == 1)
            {
                count++;
                id[i][j] = count;
                node[count] = new Node(node[count], node[count], node[count], node[count], i, j);
            }
        }
    }
    for(int j = 1; j < m; ++j)
    {
        auto pre = columnHead[j];
        for(int i = 1; i < n; ++i)
        {
            if(board[i][j] == 1)
            {
                auto p = node[id[i][j]];
                p->down = pre->down;
                p->up = pre;
                pre->down->up = p;
                pre->down = p;
                pre = p;
            }
        }
    }

    for(int i = 1; i < n; ++i)
    {
        pre = NULL;
        for(int j = 1; j < m; ++j)
        {
            if(board[i][j] == 1)
            {
                if(pre == NULL)
                    pre = node[id[i][j]];
                else
                {
                    auto p = node[id[i][j]];
                    p->right = pre->right;
                    p->left = pre;
                    pre->right->left = p;
                    pre->right = p;
                    pre = p;
                }
            }
        }
    }
}

int main()
{
    build();
    for(const auto x : columnHead)
        cout << x->y << endl;
    return 0;
}
