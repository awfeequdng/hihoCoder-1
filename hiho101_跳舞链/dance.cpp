#include <iostream>
#include <stack>
using namespace std;

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

void build()
{
    node *head;
    *head = node(head, head, head, head, 0, 0);
}

int main()
{
    int t;
    int temp;
    int n, m;
    cin >> t;
    while(t--)
    {
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
        build();
    }
    return 0;
}
