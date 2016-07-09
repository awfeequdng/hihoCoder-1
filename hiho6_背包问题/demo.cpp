#include <iostream>
#include <vector>
#define MAX 100001
using namespace std;
int res[MAX];

int max(int x, int y)
{
    if(x > y)
        return x;
    else
        return y;
}

int main()
{
    vector<pair<int, int>> vec;
    int need, value, self;
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
    {
        cin >> need >> value;
        vec.push_back(make_pair(need, value));
    }
    for(int i = 0; i < MAX; ++i)
        res[i] = 0;
    for(int i = 0; i < n; ++i)
    {
        for(int j = m; j >= vec[i].first; --j)
        {
            self = res[j];
            res[j] = max(self, res[j - vec[i].first] + vec[i].second);
        }
    }
    cout << res[m] << endl;
    return 0;
}
