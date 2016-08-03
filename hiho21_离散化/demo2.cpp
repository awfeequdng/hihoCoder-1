#include <iostream>
#include <map>
#include <set>
#include <limits.h>
using namespace std;

int main()
{
    map<int, int> num;
    map<int, int>::iterator iter, l, r, i;
    num[INT_MIN] = -1;
    num[INT_MAX] = -1;
    int n, m, a, b;
    cin >> n >> m;
    while(n--)
    {
        cin >> a >> b;
        l = num.lower_bound(a);
        r = num.upper_bound(b);
        iter = r;
        iter--;
        int p = iter->second;
        cout << endl;
        cout << "n " << n << endl;
        for(i = l; i != r;)
        {
            cout << i->first << " ";
            num.erase(i++);
        }
        num[a] = n;
        num[b] = p;
    }
    set<int> s;
    for(i = num.begin(); i != num.end(); ++i)
    {
        s.insert(i->second);
    }
    cout << s.size() - 1 << endl;
    return 0;
}
