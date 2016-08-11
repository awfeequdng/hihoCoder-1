#include <iostream>
#include <memory.h>
#define N 10010
using namespace std;

int len[N][N];

int main()
{
    int n, m, s, t;
    int from, to, length;
    memset(len, -1, sizeof(len));
    cin >> n >> m >> s >> t;
    while(m--)
    {
        cin >> from >> to >> length;
        if(len[from][to] != -1)
        {
            len[from][to] = len[to][from] = min(len[from][to], length);
        }
    }
}
