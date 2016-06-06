#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <math.h>
using namespace std;

const int number[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct state //状态类
{
    int val;
    int f, g, h;
    state(int val_ = 123456789, int g_ = 0, int h_ = 0) : val(val_), g(g_), h(h_)
    {
        f = g + h;
    }

    friend bool operator < (const state &p, const state &q) //设定比较函数
    {
        return p.f > q.f;
    }
};

int distance(int p[3][3]) //计算曼哈顿距离
{
    int res = 0;
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(p[i][j] == 9)
                continue;
            int x = (p[i][j] - 1) / 3;
            int y = (p[i][j] - 1) % 3;

            res += abs(x - i) + abs(y - j);
        }
    }
    return res;
}

int fact(int t) //阶乘函数
{
    int res = 1;
    for(int i = 1; i <= t; ++i)
    {
        res *= i;
    }
    return res;
}
int contor(int val) //康托展开
{
    int n[9];
    int v = val;
    for(int i = 8; i >= 0; ++i)
    {
        n[i] = v % 10;
        v /= 10;
    }

    int X = 0;
    int a[9] = {0};
    for(int j = 0; j < 9; ++j)
    {
        for(int k = j + 1; k < 9; ++k)
        {
            if(n[j] < n[k])
                a[j]++;
        }
        X += a[j] * fact(8 - j);
    }

    return X;
}

int uncontor(int X) //逆康托展开
{
   int a[9];
   int v = X;
   for(int i = 0; i < 9; ++i)
   {
        a[i] = v / fact(8 - i);
        v %= fact(8 - i);
   }

   int val = 0;
   list<int> q(number, number + 9);
   for(int i = 0; i < 9; ++i)
   {
       list<int>::iterator p = q.begin();
       while(a[i]-- > 0)
           p++;
       val = val * 10 + *p;
       q.erase(p);
   }

   return val;
}

int bfs(int start)
{
    int board[3][3];
    int v = start;
    for(int i = 2; i >= 0; --i)
    {
        for(int j = 2; j >= 0; --j)
        {
            board[i][j] = v % 10;
            v /= 10;
        }
    }

    priority_queue<state> open;
    vector<int> close(fact(9), -1);

    open.push(state(start, 0, distance(board)));

    while(!open.empty() && close[0] == -1)
    {
        state s = open.top();
        open.pop();

        int k = contor(s.val);
        if(close[k] != -1)
            continue;
        close[k] = s.g;

        int v = s.val;
        for(int i = 2; i >= 0; --i)
        {
            for(int j = 2; j >= 0; --j)
            {
                board[i][j] = v % 10;
                v /= 10;
            }
        }

        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                if(board[i][j] == 9)
                {
                    for(int t = 0; t < 4; ++t)
                    {
                        int x = i + dir[t][0];
                        int y = j + dir[t][1];
                        if(x >= 0 && x < 3 && y >= 0 && y < 3)
                        {
                            swap(board[i][j], board[x][y]);
                            int u = 0;
                            for(int p = 0; p < 3; ++p)
                            {
                                for(int q = 0; q < 3; ++q)
                                {
                                    u = u * 10 + board[p][q];
                                }
                            }
                            open.push(state(u, s.g + 1, distance(board)));
                            swap(board[i][j], board[x][y]);
                        }
                    }
                    break;
                }
            }
        }
    }
    return close[0];
}

int main()
{
    int temp;
    int num[9];
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
        int c = bfs(val);
        if(c == -1)
            cout << "No Solution!\n";
        else
            cout << c << endl;
    }
    return 0;
}
