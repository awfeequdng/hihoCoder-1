#include <iostream>
#include <vector>
using namespace std;
int n, q;
vector<vector<pair<int, int>>> tree(101);
int res[101][101] = {0};
int tot[101] = {0};

int dfs(int cur, int fa)
{
    tot[cur] = 1;
    for(int i = 0; i < tree[cur].size(); ++i)
    {
        int Child = tree[cur][i].first;
        if(Child ==  fa)
            continue;
        tot[cur] += dfs(Child, cur);
    }
    return tot[cur];
}

int main()
{
    cin >> n >> q;
    int a, b, v;
    for(int i = 1; i < n; ++i)
    {
        cin >> a >> b >> v;
        tree[a].push_back(make_pair(b, v));
        tree[b].push_back(make_pair(a, v));
    }
    dfs(1, -1);
    for(int i = 1; i <= n; ++i)
        cout << tot[i] << " ";
    cout << endl;
    return 0;
}
