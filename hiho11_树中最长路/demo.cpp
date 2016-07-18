#include <iostream>
#include <vector>
#define MAXL 1e5 + 1
using namespace std;
int node1;
int longest;
vector<vector<int>> node(MAXL);

void dfs(int cur, int depth, int father)
{
    if(longest < depth)
    {
        longest = depth;
        node1 = cur;
    }
    for(int i = 0; i < node[cur].size(); ++i)
    {
        if(node[cur][i] != father)
            dfs(node[cur][i], depth+1, cur);
    }
}

int main()
{
    int n, f, s;
    cin >> n;
    for(int i = 1; i < n; ++i)
    {
        cin >> f >> s;
        node[f].push_back(s);
        node[s].push_back(f);
    }
    longest = 0;
    dfs(1, 0, -1);
    longest = 0;
    dfs(node1, 0, -1);
    cout << longest << endl;
    return 0;
}
