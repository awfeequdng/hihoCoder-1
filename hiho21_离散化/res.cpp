#include <iostream>
#include <map>
#include <set>
#include <limits.h>

using namespace std;

int main()
{
    int n, p, a, b;
    map<int, int> m;
    map<int, int>::iterator l, r, iter, i;
    m[INT_MIN] = -1;
    m[INT_MAX] = -1;
    cin >> n >> p;
    while(n--)
    {
        cin >> a >> b;
        l = m.lower_bound(a);
        r = m.upper_bound(b);
        iter = r;
        iter--;
        int temp = iter->second;
        for(i = l; i != r;)
            i = m.erase(i);
        m[a] = n;
        m[b] = temp;
    }
    set<int> s;
    for(i = m.begin(); i != m.end(); ++i)
        s.insert(i->second);
    cout << s.size() - 1 << endl;
    return 0;
}
