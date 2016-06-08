#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int n, m;//全局变量，表示矩阵的行和列

struct node//node结构
{
    node *left;
    node *right;
    node *up;
    node *down;
    int x;
    int y;
    node(node *left_, node *right_, node *up_, node *down_, int x_, int y_) : left(left_), right(right_), up(up_), down(down_), x(x_), y(y_) {}
};

void build(vector<pair<int, int>> s)
{
    node *head;
    *head = node(head, head, head, head, 0, 0);
    node *columnHead[m];
    auto pre = head;
    for(int i = 0; i < m; ++i)
    {
        auto p = columnHead[i];

        p->up = p;
        p->down = p;

        p->x = 0;
        p->y = i;

        p->right = pre->right;
        p->left = pre;
        pre->right->left = p;
        pre->right = p;
        pre = p;
    }
}

int main()
{
    int t;
    int temp;
    cin >> t;
    while(t--)
    {
        vector<pair<int, int>> state;
        cin >> n >> m;
        int num[n][m];
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                cin >> temp;
                num[i][j] = temp;
            }
        }
    }
    return 0;
}
