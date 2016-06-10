#include <iostream>
#include <stack>
#include <vector>
#include <memory>
using namespace std;

int n, m;//全局变量，n表示矩阵的行，m表示矩阵的列
vector<pair<int, int>> state;

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
    for(const auto x : s)
        cout << "(" << x.first << "," << " " << x.second << ")" << " ";
    cout << endl;
    shared_ptr<node> head;
    head = make_shared<node>(node(head, head, head, head, 0, 0));
    int board[n][m];
    int id[n][m];
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
        {
            board[i][j] = 0;
            id[i][j] = -1;
        }
    for(const auto x : s)
        board[x.first][x.second] = 1;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int t;
    int temp;
    cin >> t;
    while(t--)
    {
        state.clear();
        cin >> n >> m;
        int num[n][m];
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                cin >> temp;
                num[i][j] = temp;
                if(temp == 1)
                    state.push_back(make_pair(i, j));
            }
        }
        build(state);
    }
    return 0;
}
