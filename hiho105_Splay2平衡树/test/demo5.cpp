#include <iostream>
#include <map>

using namespace std;

int main()
{
    map<int, int> m;
    map<int, int>::iterator it;
    int a, b, d;
    char ch;
    int n;
    cin >> n;
    while(n--)
    {
        long long res = 0;
        cin >> ch >> a >> b;
        if(ch == 'I')
        {
            m.insert(pair<int, int>(a, b));
        }
        else if(ch == 'Q')
        {
            for(it = m.begin(); it != m.end(); it++)
            {
                if((*it).first >= a && (*it).first <= b)
                    res += (*it).second;
            }
            cout << res << endl;
        }
        else if(ch == 'M')
        {
            cin >> d;
            for(it = m.begin(); it != m.end(); it++)
            {
                if((*it).first >= a && (*it).first <= b)
                {
                    (*it).second += d;
                }
            }
        }
        else if(ch == 'D')
        {
            for(it = m.begin(); it != m.end(); it++)
            {
                if((*it).first >= a && (*it).first <= b)
                {
                    auto p = it;
                    m.erase(p);
                }
            }
        }
    }
    return 0;
}
