#include <iostream>
using namespace std;
int res[100001];
int main()
{
    for(auto x : res)
        x = 0;
    int n, m;
    int need_, value_;
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
    {
        cin >> need_ >> value_;
        for(int j = need_; j < m; ++j)
            res[j] = (res[j] > (res[j - need_] + value_) ? res[j] : (res[j - need_] + value_));
    }
    cout << res[m - 1] << endl;
    return 0;
}
