#include <iostream>
#include <memory>
#include <stack>
#include <cstring>
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
int ans[SIZE];
Node *head = NULL;
Node *columnHead[SIZE];
Node *node[SIZE * SIZE];


void init()
{
    head = NULL;
    memset(board, 0, SIZE * SIZE);
    memset(id, 0, SIZE * SIZE);
    for(auto x : columnHead)
        x = NULL;
    for(auto x : node)
        x = NULL;
}

void build()
{
    if(head == NULL)
    {
        //使用两步进行构建
        head = new Node();
        *head = Node(head, head, head, head, 0, 0);
    }
    auto pre = head;
    for(int i = 1; i <= m; ++i)
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
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m; ++j)
        {
            if(board[i][j] == 1)
            {
                count++;
                id[i][j] = count;
                node[count] = new Node();
                *node[count] = Node(node[count], node[count], node[count], node[count], i, j);
            }
        }
    }
    for(int j = 1; j <= m; ++j)
    {
        auto pre = columnHead[j];
        for(int i = 1; i <= n; ++i)
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

    for(int i = 1; i <=n; ++i)
    {
        pre = NULL;
        for(int j = 1; j <= m; ++j)
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

void remove(int col)
{
    auto p = columnHead[col];
    p->right->left = p->left;
    p->left->right = p->right;
    auto p2 = p->down;
    while(p2 != p)
    {
        auto p3 = p2->right;
        while(p3 != p2)
        {
            p3->down->up = p3->up;
            p3->up->down = p3->down;
            p3 = p3->right;
        }
        p2 = p2->down;
    }
}

void resume(int col)
{
    auto p = columnHead[col];
    p->right->left = p;
    p->left->right = p;
    auto p2 = p->down;
    while(p2 != p)
    {
        auto p3 = p2->right;
        while(p3 != p2)
        {
            p3->down->up = p3;
            p3->up->down = p3;
            p3 = p3->right;
        }
        p2 = p2->down;
    }
}

bool dance(int depth)
{
    auto p = head->right;
    if(p == head)
        return true;

    auto p2 = p->down;
    if(p2 == p)
        return false;

    remove(p->y);

    while(p2 != p)
    {
        ans[depth] = p2->x;

        auto p3 = p2->right;
        while(p3 != p2)
        {
            remove(p3->y);
            p3 = p3->right;
        }

        if(dance(depth + 1))
            return true;

        p3 = p2->left;
        while(p3 != p2)
        {
            resume(p3->y);
            p3 = p3->left;
        }

        p2 = p2->down;
    }
    resume(p->y);
    return false;
}

int main()
{
    int num;
    cin >> num;
    while(num--)
    {
        init();
        cin >> n >> m;
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= m; ++j)
            {
                cin >> board[i][j];
            }
        }
        build();
        if(dance(0))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
