#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main()
{
    int n, p;
    cin >> n;
    string fa, son, s1, s2;
    map<string, string> m;
    map<string, string>::iterator it;
    map<string, int> vec;
    for(int i = 0; i < n; ++i)
    {
        cin >> fa >> son;
        m.insert(make_pair(son, fa));
    }
    cin >> p;
    while(p--)
    {
        vec.clear();
        cin >> s1 >> s2;
        vec.insert(make_pair(s1, 0));
        it = m.find(s1);
        while(it != m.end())
        {
            vec.insert(make_pair((*it).second, 0));
            it = m.find((*it).second);
        }
        if(vec.find(s2) != vec.end())
        {
            cout << s2 << endl;
            continue;
        }
        it = m.find(s2);
        while(it != m.end())
        {
            if(vec.find((*it).second) != vec.end())
            {
                cout << (*it).second << endl;
                break;
            }
            else
                it = m.find((*it).second);
        }
        if(it == m.end())
            cout << -1 << endl;
    }
    return 0;
}
