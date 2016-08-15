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
                    if(source[x.first])
                    {
                        continue;
                    }
                    else
                    {
                        que.push(x.first);
                        source[x.first] = true;
                    }
                }
            }
        }
        source[que.front()] = false;
        que.pop();
    }
    cout << state[t] << endl;
    return 0;
}
