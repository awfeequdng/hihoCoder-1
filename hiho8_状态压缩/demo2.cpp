/**
 *求取best(i, j)，则状态j对应的前驱状态只有可能为：
 *当前状态[jjjjjjjjjj]
 *前驱状态[0jjjjjjjjj]
 *前驱状态[1jjjjjjjjj]
 *则当前状态best(i, j)必然是由前驱状态best(i-1, j>>1)（对应前置位为0）和
 *best(i-1, (j>>1) + 2^(m-2))（对应前置位为1）转变而来，两者取最大之后进行相关计算即可
 */
/*
 *本次代码有以下几点感受：
 *1.必要参数提前以数组给出能够大大提高效率；
 *2.充分利用已有计算结果，提高效率，比如计算cnt数组时；
 *3.使用位运算进行状态压缩和状态转移，特别好用，经典案例！
 */
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
