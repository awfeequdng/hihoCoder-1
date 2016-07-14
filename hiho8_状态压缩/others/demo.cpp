#include <iostream>
#include <cmath>
#include <memory.h>

using namespace std;

const int b[11]={1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

int f[2][1024];
int w[1001];
int cnt[1024];

int main()
{
    int m, n, q;
    cin >> n >> m >> q;
    for (int i=1; i<=n; ++i) cin >> w[i];
    memset(f, 0, sizeof f);
    cnt[0]=0;cnt[1]=1;
    for (int i=2; i<b[m]; ++i) cnt[i]=cnt[i>>1]+cnt[i&1];
    for (int i=1; i<=n; ++i)
        for (int j=0; j<b[m]; ++j) if (cnt[j]<=q)
            f[i&1][j]=max(f[(i&1)^1][j>>1], f[(i&1)^1][(j>>1)+b[m-1]])+(j&1)*w[i];
    int ans=0;
    for (int j=0; j<b[m]; ++j)
        ans=max(ans, f[n&1][j]);
    cout << ans << endl;
}
