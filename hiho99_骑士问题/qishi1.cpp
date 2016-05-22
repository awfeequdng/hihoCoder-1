#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct point
{
    int x;
    int y;
    point() { }
    point(int x, int y) { this->x = x; this->y = y; }
    void set_xy(int x, int y) { this->x = x; this->y = y;}
};

//存储状态值，未遍历位置置为false
int step[3][8][8];


point move(point p, int i)
{
    point next;
    switch(i)
    {
        case 0:
            next.set_xy(p.x - 2, p.y + 1);
            break;
        case 1:
            next.set_xy(p.x - 1, p.y + 2);
            break;
        case 2:
            next.set_xy(p.x + 1, p.y + 2);
            break;
        case 3:
            next.set_xy(p.x + 2, p.y + 1);
            break;
        case 4:
            next.set_xy(p.x - 2, p.y - 1);
            break;
        case 5:
            next.set_xy(p.x - 1, p.y - 2);
            break;
        case 6:
            next.set_xy(p.x + 1, p.y - 2);
            break;
        case 7:
            next.set_xy(p.x + 2, p.y - 1);
    }
    return next;
}

bool isInChessBoard(point p)
{
    if(p.x < 0 || p.y > 7 || p.x > 7 || p.y < 0)
        return false;
    else
        return true;
}

void bfs_solve(int f[8][8], int x, int y)
{
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            f[i][j] = false;
        }
    }

    stack<point> queue;
    point p(x, y);
    queue.push(p);
    while(!queue.empty())
    {
        point p1 = queue.top();
        queue.pop();

        for(int i = 0; i < 8; ++i)
        {
            point next = move(p1, i);
            if(isInChessBoard(next) && f[next.x][next.y])
            {
                f[next.x][next.y] = f[p1.x][p1.y] + 1;
                queue.push(next);
            }
        }
    }
}

int get_x(char a)
{
    return a - 'A';
}
int get_y(char a)
{
    return a - '0';
}

int res(int x, int y)
{
    int result = 0;
    for(int i = 0; i < 3; ++i)
    {
        result += step[i][x][y];
    }
    return result;
}


int main()
{
    int n;
    cin >> n;
    while(n--)
    {
        string a, b, c;
        cin >> a >> b >> c;
        bfs_solve(step[0], get_x(a[0]), get_y(a[1]));
        bfs_solve(step[1], get_x(b[0]), get_y(b[1]));
        bfs_solve(step[2], get_x(c[0]), get_y(c[1]));

        int ans = 65535;
        for(int i = 0; i < 8; ++i)
        {
            for(int j = 0; j < 8; ++j)
            {
                if(ans > res(i, j))
                    ans = res(i, j);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
