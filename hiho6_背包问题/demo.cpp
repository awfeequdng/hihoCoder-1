#include <iostream>
#include <vector>
#define MAX 100001
using namespace std;
int res[MAX];
int main()
{
    vector<pair<int, int>> vec;
    int need, value, self;
    int n, m;
    cin >> n >> m;
    while(n--)
    {
        cin >> need >> value;
        vec.push_back(make_pair(need, value));
    }
    for(const auto x : vec)
    {
        cout << x.first << " " << x.second << endl;
    }
    for(int i = 0; i < MAX; ++i)
        res[i] = 0;
    for(int i = 1; i < n; ++i)
    {
        for(int j = m; j <= vec[i].first; --j)
        {
            self = res[j];
            res[j] = max(self, res[j - vec[i].first] + vec[i].second);
        }
    }
    for(int i = 0; i < m; ++i)
        cout << res[i] << " ";
    cout << endl;
    return 0;
}
