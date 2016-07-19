#include <iostream>
using namespace std;
int n;
int score[55] = {0};//分数
int root[55][55] = {0};//根节点
int m[55][55] = {0};//最大点;

void show()
{
    for(int i = 0; i <= n; ++i)
    {
        for(int j = 0; j <= n; ++j)
        {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}
void solve()
{
    for(int i = 1; i <= n; ++i)
    {
        m[i][i] = score[i];
        root[i][i] = i;
    }
    for(int i = 1; i < n; i++)
    {
        m[i][i+1] = score[i] + score[i+1];
        root[i][i+1] = i;
    }
    for(int d = 2; d < n; ++d)
    {
        for(int i = 1; i <= n-d; ++i)
        {
            int temp;
            m[i][i+d] = m[i][i] + m[i+1][i+d];
            root[i][i+d] = i;
            for(int j = i+1; j <= i+d; ++j)
            {
                temp = m[i][j-1] * m[j+1][i+d] + m[j][j];
                if(temp > m[i][i+d])
                {
                    m[i][i+d] = temp;
                    root[i][i+d] = j;
                }
            }
            if(m[i+d][i+d] + m[i][i+d-1] > m[i][i+d])
            {
                m[i][i+d] = m[i][i+d-1] + m[i+d][i+d];
                root[i][i+d] = i+d;
            }
        }
    }
}

//前序遍历
void preOrder(int x, int y)
{
    if(x <= y)
    {
        cout << root[x][y] << " ";
        preOrder(x, root[x][y] - 1);
        preOrder(root[x][y] + 1, y);
    }
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> score[i];
    }
    solve();
    cout << m[1][n] << endl;
    preOrder(1, n);
    cout << endl;
    return 0;
}
