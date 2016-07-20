//这段代码很不错，树归的经典！！
#include <iostream>
#include <vector>
using namespace std;
int value[102] = {0};
int df[102][102] = {0};
int num[102] = {0};
vector<vector<int>> tree(102);
int n, p;

int dfs(int cur, int fa)
{
    num[cur] = 1;
    int len = tree[cur].size();
    for(int i = 0; i < len; ++i)
    {
        if(tree[cur][i] == fa)
            continue;
        num[cur] += dfs(tree[cur][i], cur);
    }
    for(int i = 0; i < len; ++i)
    {
        if(tree[cur][i] == fa)
            continue;
        for(int j = p; j > 1; --j)
        {
            for(int k = 1; k < j && k <= num[tree[cur][i]]; ++k)
            {
                df[cur][j] = max(df[cur][j], df[cur][j-k] + df[tree[cur][i]][k]);
            }
        }
    }
    return num[cur];
}

int main()
{
    int a, b;
    cin >> n >> p;
    for(int i = 1; i <= n; ++i)
    {
        cin >> value[i];
    }
    for(int i = 1; i <= n; ++i)
    {
        df[i][1] = value[i];
    }
    for(int i = 1; i < n; ++i)
    {
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    dfs(1, -1);
    /*for(int i = 0; i <= n; ++i)
    {
        for(int j = 0; j <= n; ++j)
        {
            cout << df[i][j] << " ";
        }
        cout << endl;
    }*/
    cout << df[1][p] << endl;
    return 0;
}
