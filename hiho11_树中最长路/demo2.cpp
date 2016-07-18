#include <iostream>
#include <vector>
using namespace std;
#define MAXL 1e5+1
int n;
int longest = 0;
vector<int> first, second;
vector<vector<int>> node(MAXL);

void dfs(int cur, int fa)
{
    int len = node[cur].size();
    for(int i = 0; i < len; ++i)
    {
        if(node[cur][i] != fa)
        {
            dfs(node[cur][i], cur);
            if(first[node[cur][i]]+1 > first[cur])
            {
                second[cur] = first[cur];
                first[cur] = first[node[cur][i]] + 1;
            }
            else if(first[node[cur][i]]+1 > second[cur])
            {
                second[cur] = first[node[cur][i]] + 1;
            }
            cout << first[node[cur][i]] << endl;
        }
    }
    if(first[cur] + second[cur] > longest)
        longest = first[cur] + second[cur];
}

void init()
{
    first.assign(n+1, 0);
    second.assign(n+1, 0);
}

int main()
{
    cin >> n;
    int a, b;
    for(int i = 1; i < n; ++i)
    {
        cin >> a >> b;
        node[a].push_back(b);
        node[b].push_back(a);
    }
    init();
    dfs(1, -1);
    cout << longest << endl;
    return 0;
}
