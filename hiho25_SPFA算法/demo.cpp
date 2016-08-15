#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#define N 100010
using namespace std;
vector<pair<int, int> > len[N];
bool source[N] = {false};
unsigned state[N];
queue<int> que;
int main()
{
    memset(state, -1, sizeof(state));
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    int from, to, length;
    while(m--)
    {
        cin >> from >> to >> length;
        len[from].push_back(make_pair(to, length));
    }
    state[s] = 0;
    que.push(s);
    while(!que.empty())
    {
        for(const auto x : len[que.front()])
        {
            if(state[que.front()] != -1)
            {
                if(state[que.front()] + x.second < state[x.first])
                {
                    state[x.first] = state[que.front()] + x.second;
                    que.push(que.front());
                }
            }
        }
        que.pop();
    }
    return 0;
}
