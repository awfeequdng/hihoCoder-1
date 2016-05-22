#include <iostream>
#include <stack>
#include <string>
define INT_MAX 2147483647
using namespace std;
struct point
{
	int x;
	int y;
	point(){}
	point(int x, int y) { this->x = x; this->y = y; }
	void setXY(int x,int y) { this->x = x; this->y = y; }
};

int step[3][8][8];
point move(point current, int i)
{
	point next;
	switch (i)
	{
		case 0:
			next.setXY(current.x - 1, current.y + 2);
			break;
		case 1:
			next.setXY(current.x + 1, current.y + 2);
			break;
		case 2:
			next.setXY(current.x + 2, current.y + 1);
			break;
		case 3:
			next.setXY(current.x + 2, current.y-1);
			break;
		case 4:
			next.setXY(current.x + 1, current.y - 2);
			break;
		case 5:
			next.setXY(current.x-1, current.y - 2);
			break;
		case 6:
			next.setXY(current.x - 2, current.y - 1);
			break;
		case 7:
			next.setXY(current.x - 2, current.y+1);
			break;
	}
	return next;
}
bool isInChessBoard(point p)
{
	if (p.x<0 || p.x>7 || p.y<0 || p.y>7)
		return false;
	else
		return true;
}

void bfs_solve(int f[8][8], int x, int y)
{
 	for (int i = 0; i < 8; i++)
 	{
 		 for (int j = 0; j < 8; j++)
 		 {
 		 	f[i][j] = -1;
 		 }
 	}

	f[x][y] = 0;
	stack<point> queue;
	point p(x, y);
	queue.push(p);
	while (!queue.empty())
	{
    	point p1 = queue.top();
    	queue.pop();
    	for (int i = 0; i < 8; i++)
    	{
        	point next = move(p1, i);
        	if (isInChessBoard(next) && f[next.x][next.y] == -1)
        	{
            	f[next.x][next.y] = f[p1.x][p1.y] + 1;
            	queue.push(next);
        	}
    	}

	}
}
int getX(char a)
{
	return a - 'A';
}

int getY(char b)
{
    return b - '0';
}
int sigma(int x, int y)
{
    int result = 0;
    for (int i = 0; i < 3; i++)
    {
        result += step[i][x][y];
    }
    return result;
}
int main()
{
	int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string a,b,c;
        cin >> a>>b>>c ;
        bfs_solve(step[0], getX(a[0]), getY(a[1]));
        bfs_solve(step[1], getX(b[0]), getY(b[1]));
        bfs_solve(step[2], getX(c[0]), getY(c[1]));
        int ans = INT_MAX;
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                if (ans > sigma(j, k))
                    ans = sigma(j, k);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
