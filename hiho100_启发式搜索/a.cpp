#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <queue>
#include <math.h>
using namespace std;
int board[3][3] = {0};
int value = 0;
const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void get_board(int val) //生成board矩阵
{
    int temp = val;
    for(int i = 2; i >= 0; --i)
    {
        for(int j = 2; j >= 0; --j)
        {
            board[i][j] = temp % 10;
            temp /= 10;
        }
    }
}

int un_board(int p[3][3]) //解board获取状态值val
{
    int temp = 0;
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            temp = temp * 10 + p[i][j];
        }
    }
    return temp;
}

int fact(int val) //阶乘函数
{
    int temp = 1;
    for(int i = 1; i <= val; ++i)
        temp *= i;
    return temp;
}

struct state
{
    int val;//状态数值
    int g, h, f;
    state(int val_ = 123456789, int g_ = 0, int h_ = 0) : val(val_), g(g_), h(h_) {f = g + h;}
    friend bool operator < (const state &left, const state &right)
    {
        return left.f > right.f;
    }
};

int contor(int val)
{
    int n[9];
    int temp = val;
    for(int i = 8; i >= 0; --i)
    {
        n[i] = temp % 10;
        temp /= 10;
    }

    int a[9] = {0};
    int X = 0;
    for(int i = 0; i < 9; ++i)
    {
        for(int j = i + 1; j < 9; ++j)
            if(n[i] > n[j])
                a[i]++;
        X += a[i] * fact(8 - i);
    }
    return X;
}

int uncontor(int X)//逆康托展开
{
    int a[9] = {0};
    int temp = X;
    for(int i = 0; i < 9; ++i)
    {
        a[i] = temp / fact(8 - i);
        temp %= fact(8 - i);
    }

    int val = 0;
    list<int> q{1, 2, 3, 4, 5, 6, 7, 8, 9};
    for(int i = 0; i < 9; ++i)
    {
        auto p = q.begin();
        while(a[i]-- > 0)
        {
            p++;
        }
        val = val * 10 + *p;
        q.erase(p);
    }

    return val;
}

int dis(int p[3][3])//曼哈顿距离
{
    int ans = 0;
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(p[i][j] == 9)
                continue;
            int x = (p[i][j] - 1) / 3;
            int y = (p[i][j] - 1) % 3;

            ans += abs(x - i) + abs(y - i);
        }
    }
    return ans;
}

int bfs(int start)//宽度优先搜索算法
{
    get_board(start);
    priority_queue<state> open;
    vector<int> close(fact(9), -1);

    open.push(state(start, 0, dis(board)));

    while(!open.empty() && close[0] == -1)
    {
        state s = open.top();
        open.pop();

        int k = contor(s.val);
        if(close[k] != -1)
            continue;
        close[k] = s.g;

        int temp = s.val;
        get_board(temp);

        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                if(board[i][j] == 9)
                {
                    for(int k = 0; k < 4; ++k)
                    {
                        int x = i + dir[k][0];
                        int y = j + dir[k][1];
                        if(x >= 0 && x < 3 && y >= 0 && y < 3)
                        {
                            swap(board[i][j], board[x][y]);
                            int v = un_board(board);
                            open.push(state(v, s.g + 1, dis(board)));

                            swap(board[i][j], board[x][y]);
                        }
                    }
                }
            }
        }
    }
    return close[0];
}

int main()
{
    int num[9];
    int temp = 0;
    int n;
    cin >> n;
    while(n--)
    {
        int val = 0;
        for(int i = 0; i < 9; ++i)
        {
            cin >> temp;
            if(temp == 0)
                temp = 9;
            num[i] = temp;
            val = val * 10 + temp;
        }
        auto res = bfs(val);
        if(res == -1)
            cout << "No Solution!" << endl;
        else
            cout << res << endl;
    }
    return 0;
}
