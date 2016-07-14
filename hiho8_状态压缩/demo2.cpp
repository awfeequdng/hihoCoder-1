#include <iostream>
#include <memory.h>
using namespace std;
int b[]= {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

int w[1001];
int cnt[1024];
int res[2][1024];

int main()
{
    memset(res, 0, sizeof(res));
    int n, m, q;
    cin >> n >> m >> q;
    for(int i = 1; i <= n; ++i)
        cin >> w[i];
    cnt[0] = 0;
    cnt[1] = 1;
    for(int i = 2; i < b[m]; ++i)
        cnt[i] = cnt[i>>1] + cnt[i&1];
    for(int i = 1; i <= n; ++i)
        for(int j = 0; j < b[m]; ++j)
            if(cnt[j] <= q)
                res[i&1][j] = max(res[(i&1)^1][j>>1], res[(i&1)^1][(j>>1) + b[m-1]]) + (j&1) * w[i];
    int ans = 0;
    for(auto x : res[n&1])
        if(ans < x)
            ans = x;
    cout << ans << endl;
    return 0;
}
